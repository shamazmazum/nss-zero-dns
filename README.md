# ZeroDNS NSS module

This is NSS module for ZeroDNS server which provides DNS functionality on top of
ZeroMQ library and NORM multicast protocol. Tested on FreeBSD only, but may work
on Linux as well. Codebase is forked from
[here](https://github.com/lathiat/nss-mdns). Currently it resolves only IPv4
addresses.

## How to use it?

* Install ZeroMQ.
* Install my [ZeroDNS](https://github.com/shamazmazum/zero-dns) server and run it
  on every machine in your LAN.
* Install this library.
* Change `hosts` entry in `/etc/nsswitch.conf` to something like `hosts: files
  dns zerodns`.
* Set an environment variable ZDNS_IFACE to the name of interface connected to
  your LAN.

That's it. You must be able to resolve names in `.local` zone!

## Limitations

* Currently you can spawn any number of ZeroDNS daemons each listening to its
  own interface, but NSS module works only with one such daemon.
