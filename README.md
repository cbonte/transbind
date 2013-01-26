transbind
=========

Enable transparent binding on applications that don't allow it natively.

This library is still **experimental**. It is based on LD_PRELOAD to set socket options before any bind() calls.

## How To

> LD_PRELOAD=<installation path>/transbind.so <server application>

## Tested applications (IPv4 only)
* nginx 
* varnish

## Side notes
> iptables -t mangle -N DIVERT
> iptables -t mangle -A PREROUTING -p tcp -m socket -j DIVERT
> iptables -t mangle -A DIVERT -j MARK --set-mark 1
> iptables -t mangle -A DIVERT -j ACCEPT
> 
> ip rule add fwmark 1 lookup 100
> ip route add local 0.0.0.0/0 dev lo table 100
> 
> iptables -t mangle -A PREROUTING -p tcp --dport <port> -j TPROXY --tproxy-mark 0x1/0x1 --on-port <port>
