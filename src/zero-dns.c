/*
  This file is part of nss-zerodns.

  nss-zerodns is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  nss-zerodns is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with nss-zerodns; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <zmq.h>

#include "zero-dns.h"
#include "util.h"

struct zmq_ctx_sock {
    void *ctx;
    void *socket;
};

#define ENDPOINT_LEN 100

static void release_context_and_socket (struct zmq_ctx_sock *data) {
    if (data->socket != NULL) {
        zmq_close (data->socket);
    }

    if (data->ctx != NULL) {
        zmq_ctx_term (data->ctx);
    }
}

static int prepare_context_and_socket (struct zmq_ctx_sock *data) {
    char endpoint[ENDPOINT_LEN];
    char *iface;
    int success = 0;

    memset (data, 0, sizeof (struct zmq_ctx_sock));
    data->ctx = zmq_init (1);
    if (data->ctx == NULL) {
        goto done;
    }

    data->socket = zmq_socket (data->ctx, ZMQ_REQ);
    if (data->socket == NULL) {
        goto done;
    }

    int linger = 0;
    if (zmq_setsockopt (data->socket, ZMQ_LINGER, &linger, sizeof (linger)) != 0) {
        goto done;
    }

    iface = getenv ("ZDNS_IFACE");
    if (iface == NULL) {
        goto done;
    }

    snprintf (endpoint, ENDPOINT_LEN, "ipc://%s/%s", ZDNS_SOCKET_DIRECTORY, iface);
    if (zmq_connect (data->socket, endpoint) != 0) {
        goto done;
    }

    success = 1;

done:
    if (!success) {
        release_context_and_socket (data);
    }

    return success;
}

static zdns_resolve_result_t
zdns_resolve_name_with_socket(void *socket, int af, const char* name,
                              query_address_result_t* result) {
    zmq_pollitem_t poll_item = {socket, 0, ZMQ_POLLIN, 0};
    char msg_buf[256];
    int len;

    snprintf (msg_buf, sizeof(msg_buf), "!%s", name);
    if (zmq_send (socket, msg_buf, strlen (msg_buf), 0) == -1) {
        return ZDNS_RESOLVE_RESULT_UNAVAIL;
    }

    if (zmq_poll (&poll_item, 1, 300) == -1) {
        return ZDNS_RESOLVE_RESULT_UNAVAIL;
    }

    if (!(poll_item.revents & ZMQ_POLLIN)) {
        return ZDNS_RESOLVE_RESULT_UNAVAIL;
    }

    len = zmq_recv (socket, msg_buf, sizeof(msg_buf)-1, 0);
    if (len > 0) {
        msg_buf[len] = '\0';
        if (inet_pton (af, msg_buf, &result->address) == 1) {
            result->af = af;
            return ZDNS_RESOLVE_RESULT_SUCCESS;
        } else {
            return ZDNS_RESOLVE_RESULT_UNAVAIL;
        }
    }

    return ZDNS_RESOLVE_RESULT_HOST_NOT_FOUND;
}

zdns_resolve_result_t zdns_resolve_name(int af, const char* name,
                                        query_address_result_t* result) {
    struct zmq_ctx_sock env;
    zdns_resolve_result_t ret;

    if (af != AF_INET /*&& af != AF_INET6 */) {
        return ZDNS_RESOLVE_RESULT_HOST_NOT_FOUND;
    }

    if (!prepare_context_and_socket (&env)) {
        return ZDNS_RESOLVE_RESULT_UNAVAIL;
    }

    ret = zdns_resolve_name_with_socket(env.socket, af, name, result);
    release_context_and_socket (&env);
    return ret;
}

static zdns_resolve_result_t
zdns_resolve_address_with_socket(void *socket, int af, const void* data, char* name,
                                 size_t name_len) {
    zmq_pollitem_t poll_item = {socket, 0, ZMQ_POLLIN, 0};
    char msg_buf[256];
    char a[256];
    int len;

    snprintf (msg_buf, sizeof (msg_buf),
              "~%s", inet_ntop (af, data, a, sizeof (a)));
    if (zmq_send (socket, msg_buf, strlen (msg_buf), 0) == -1) {
        return ZDNS_RESOLVE_RESULT_UNAVAIL;
    }

    if (zmq_poll (&poll_item, 1, 300) == -1) {
        return ZDNS_RESOLVE_RESULT_UNAVAIL;
    }

    if (!(poll_item.revents & ZMQ_POLLIN)) {
        return ZDNS_RESOLVE_RESULT_UNAVAIL;
    }

    len = zmq_recv (socket, msg_buf, sizeof(msg_buf)-1, 0);
    if (len > 0) {
        msg_buf[len] = '\0';
        strlcpy (name, msg_buf, name_len);
        return ZDNS_RESOLVE_RESULT_SUCCESS;
    }

    return ZDNS_RESOLVE_RESULT_HOST_NOT_FOUND;
}

zdns_resolve_result_t zdns_resolve_address(int af, const void* data,
                                           char* name, size_t name_len) {
    struct zmq_ctx_sock env;
    zdns_resolve_result_t ret;

    if (af != AF_INET /*&& af != AF_INET6 */) {
        return ZDNS_RESOLVE_RESULT_HOST_NOT_FOUND;
    }

    if (!prepare_context_and_socket (&env)) {
        return ZDNS_RESOLVE_RESULT_UNAVAIL;
    }

    ret = zdns_resolve_address_with_socket(env.socket, af, data, name, name_len);
    release_context_and_socket (&env);
    return ret;
}
