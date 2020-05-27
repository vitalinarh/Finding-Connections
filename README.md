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

# Input
The first line of each test case gives the amount of network equipment (n ≤ 1000) at the
communication network. Note that some nodes of this network may be servers, but you
do not know which ones. Then, the next lines provide information about the network
infrastructure. Each line contains a pair of positive integers that correspond to the
internal id of the network equipment that is directly connected with the existing cable,
followed by the length of this cable, as a positive integer value.
Each test case terminates with number 0. Then, other test cases may follow.

Example input:
3
1 2 3
1 3 4
2 3 5
0
4
1 2 20
1 3 1
2 3 2
3 4 1
0
10
1 2 1
1 3 3
1 4 4
1 10 2
4 5 6
4 6 7
4 7 8
5 6 9
7 8 10
7 9 11
7 10 3
8 9 12
0

# Output
For each test case, print the number of servers, the total amount of cable for the case of
a fully connected network and the total amount of cable for a tree topology, as required
by the IT department. If there is no server, report "no server".

Example output:
no server
1 0 0
3 17 9
