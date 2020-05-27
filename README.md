# Finding-Connections
Algorithm to Find Servers in a Network

# Description of the problem
The communication network at a given bank is composed of several departmental
networks, each of which connects to the remaining networks only through a server. This
network topology was chosen for security reasons. All critical data sent between
departmental networks are stored on the hard disk of these servers in order to be
analysed by automatic filtering tools. In case of a security breach at a given department,
the contents of the server's hard disk are instantaneously moved to another
departmental server and the local network becomes disconnected from the remaining
networks.
Unfortunately, the current network cables do not support fast copies between servers. In
order to improve this situation, the IT department is analysing several possibilities to
add a faster cable that only connects these servers. One option is to directly connect all
pairs of servers by cable, which is extremely fast, but expensive. The other option is to
use a tree topology, which is cheaper but also slower.
This is where you come in. You are doing an intership at the IT department and you have
to implement a program that, given a map of the complete communication network at
the Bank, it locates all departmental servers and computes the amount of cable that is
required for both options. In order to be cost effective, you have to consider the least
amount of cable and use the current infrastruture, that is, the new cable will go through
the buildings side-by-side with the old cable, possibly passing near other network
equipment.
