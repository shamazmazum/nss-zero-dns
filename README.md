# ZeroDNS NSS module

This is NSS module for ZeroDNS server which provides DNS functionality on top of
ZeroMQ library and NORM multicast protocol. Tested on FreeBSD only, but may work
on Linux as well. Codebase is forked from
[here](https://github.com/lathiat/nss-mdns). Currently it resolves only IPv4
addresses.

## How to use it?

* Install ZeroMQ.
* Install my [ZeroDNS](https://github.com/shamazmazum/zerodns) server and run it
  on every machine in your LAN.
* Install this library.
* Change `hosts` entry in `/etc/nsswitch.conf` to something like `hosts: files
  dns zerodns`.

That's it. You must be able to resolve names in `.local` zone!
