#!/usr/bin/env python

"""p3-template.py:

This mininet script creates a linear routed multi-hop topology:

2001:638:709:a::/64 2001:638:709:f::/64 2001:638:709:b::/64
.------------------..------------------..------------------.
h1 ------ s1 ------ r1 ------ s0 ------ r2 ------ s2 ------ h2
  eth0     |   eth0   eth1          eth0  eth1    |     eth0
           |                                      |
           '------- r3 ------ s3 ------ r4 -------'
               eth0   eth1          eth0  eth1
                     '------------------'
                      2001:638:709:e::/64

Assign the following IPv6 addresses and prefixes:

h1-eth0  2001:638:709:a::1/64
r1-eth0  2001:638:709:a::f/64
r1-eth1  2001:638:709:f::1/64
r2-eth0  2001:638:709:f::2/64
r2-eth1  2001:638:709:b::f/64
h2-eth0  2001:638:709:b::1/64

r3-eth0  2001:638:709:a::e/64
r3-eth1  2001:638:709:e::1/64
r4-eth0  2001:638:709:e::2/64
r4-eth1  2001:638:709:b::e/64

Debugging hints:

- If you get a 'network unreachable' error, then most likely a
forwarding table entry is missing somewhere or wrong.
- If you get a 'destination unreachable' error, then most likely
neighbor discovery failed somewhere.
- Use the 'ip -6 address', 'ip -6 route', and 'ip -6 neigh'
commands to inspect the forwarding tables and the neighbor
mapping tables.
- If pings from h1 to h2 do not work, try to ping r1 from h1 and
try to ping r1 from h2. (Test whether the links work first.)
- You can print the result of the configuration commands to see
whether any errors occurred.
- You can run tcpdump (or even wireshark) to capture packets in
order to see what is going on.
"""

from mininet.cli import CLI
from mininet.net import Mininet
from mininet.nodelib import LinuxBridge
from mininet.log import setLogLevel

if __name__ == '__main__':
    setLogLevel('info')

    net = Mininet(switch=LinuxBridge, controller=None)

    # topology
    h1 = net.addHost('h1', ip=None)
    s1 = net.addSwitch('s1')
    r1 = net.addHost('r1', ip=None)
    s0 = net.addSwitch('s0')
    r2 = net.addHost('r2', ip=None)
    s2 = net.addSwitch('s2')
    h2 = net.addHost('h2', ip=None)
    r3 = net.addHost('r3', ip=None)
    s3 = net.addSwitch('s3')
    r4 = net.addHost('r4', ip=None)

    # connections
    net.addLink(h1, s1)
    net.addLink(s1, r1)
    net.addLink(r1, s0)
    net.addLink(s0, r2)
    net.addLink(r2, s2)
    net.addLink(s2, h2)
    net.addLink(s1, r3)
    net.addLink(r3, s3)
    net.addLink(s3, r4)
    net.addLink(r4, s2)

    r1.cmd('sysctl -w net.ipv6.conf.all.forwarding=1')
    r2.cmd('sysctl -w net.ipv6.conf.all.forwarding=1')
    r3.cmd('sysctl -w net.ipv6.conf.all.forwarding=1')
    r4.cmd('sysctl -w net.ipv6.conf.all.forwarding=1')

    # addresses
    h1_eth0 = "2001:638:709:a::1/64"
    r1_eth0 = "2001:638:709:a::f/64"
    r1_eth1 = "2001:638:709:f::1/64"
    r2_eth0 = "2001:638:709:f::2/64"
    r2_eth1 = "2001:638:709:b::f/64"
    h2_eth0 = "2001:638:709:b::1/64"
    r3_eth0 = "2001:638:709:a::e/64"
    r3_eth1 = "2001:638:709:e::1/64"
    r4_eth0 = "2001:638:709:e::2/64"
    r4_eth1 = "2001:638:709:b::e/64"

    # Using the 'ip -6 address' and 'ip -6 route' commands to inspect
    # the forwarding tables
    h1.cmd("ip -6 addr add " + h1_eth0 +" dev h1-eth0")
    r1.cmd("ip -6 addr add " + r1_eth0 + " dev r1-eth0")
    r1.cmd("ip -6 addr add " + r1_eth1 + " dev r1-eth1")
    r2.cmd("ip -6 addr add " + r2_eth0 + " dev r2-eth0")
    r2.cmd("ip -6 addr add " + r2_eth1 + " dev r2-eth1")
    h2.cmd("ip -6 addr add " + h2_eth0 + " dev h2-eth0")
    r3.cmd("ip -6 addr add " + r3_eth0 + " dev r3-eth0")
    r3.cmd("ip -6 addr add " + r3_eth1 + " dev r3-eth1")
    r4.cmd("ip -6 addr add " + r4_eth0 + " dev r4-eth0")
    r4.cmd("ip -6 addr add " + r4_eth1 + " dev r4-eth1")

    # add route h1 to r1
    h1.cmd("ip -6 route add 2001:638:709:a::/64 via 2001:638:709:a::f dev h1-eth0")
    # add route r1 to r2
    r1.cmd("ip -6 route add 2001:638:709:f::/64 via 2001:638:709:f::2 dev r1-eth1")
    # add route r2 to h2
    r2.cmd("ip -6 route add 2001:638:709:b::/64 via 2001:638:709:b::1 dev r2-eth1")

    # add route h2 to r4
    h2.cmd("ip -6 route add 2001:638:709:b::/64 via 2001:638:709:b::e dev h2-eth0")
    # add route r4 to r3
    r4.cmd("ip -6 route add 2001:638:709:e::/64 via 2001:638:709:e::1 dev r4-eth0")
    # add route r3 to h1
    r3.cmd("ip -6 route add 2001:638:709:a::/64 via 2001:638:709:a::1 dev r3-eth0")

    net.start()
    CLI(net)
    net.stop()

"""
b) After running the tracepath from h1 to h2, we get an asymmetric path, as expected.
The specific results were:

        --------------------------------------------------------------
        1?: [LOCALHOST]                        0.018ms pmtu 1500
        1:  2001:638:709:a::f                                     0.068ms 
        1:  2001:638:709:a::f                                     0.057ms 
        2:  2001:638:709:f::2                                     0.029ms 
        3:  2001:638:709:b::1                                     0.037ms reached
            Resume: pmtu 1500 hops 3 back 3
        --------------------------------------------------------------
        1?: [LOCALHOST]                        0.057ms pmtu 1500
        1:  2001:638:709:b::e                                     0.173ms 
        1:  2001:638:709:b::e                                     0.169ms 
        2:  2001:638:709:e::1                                     0.305ms 
        3:  2001:638:709:a::1                                     0.204ms reached
            Resume: pmtu 1500 hops 3 back 3

c) If we configure the link between r1 and r2 to have an MTU of 1400 bytes, after
running the ping command, we observe that the packets don't move from r1 to r2 
because of their size, which is bigger than the MTU on this link. Concerning the other
links, the packets can still move along them since the size is still lower than the 
default MTU size.

d) After running the commands we observe that both obtain the path MTU information,
by finding the largest size that still allows the packets to be sent and then adding
the IP/ICMP headers default size (which is 28). Using tracepath, we obtain the path MTU
information directly, while using ping we should try for many packages with different sizes
till we find the largest. Therefore, for this information, it is easier to use the tracepath
command.

e) Path MTU discovery may fail sometimes. In our case, IPv6 routers do not support fragmentation.
For IPv6, Path MTU Discovery works by initially assuming the path MTU is the same as the MTU on 
the link layer interface where the traffic originates. So, it doesn't specifically "remember" the path.
Then, any device along the path whose MTU is smaller than the packet will drop the packet and send 
back a "Packet Too Big" type of message containing its MTU, allowing the source host to reduce its 
Path MTU appropriately.

"""