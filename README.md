# PDS-P2P-chat-network
Project consists of 3 cli applications: pds18-node, pds18-peer, pds18-rpc. Peer and node has limited thread pool, which value can be changed in configuration file "config" in root dir. Each request for node/peer is delivered to one thread in the pool.

## Configuration
Config file structure:

        ThreadPoolServer 20
        ThreadPoolClient 4
## Build
In referenced VM use:

	make all

For faster compilation use parallel execution, n is number of task:

    make all -jn

## Protocol
Protocol structure:

                       
HELLO := {"type":"hello", "txid":ushort, "username":"string", "ipv4":"dotted_decimal_IP", "port": ushort}                       
                       
GETLIST := {"type":"getlist", "txid":ushort}                       
                       
LIST := {"type":"list", "txid":ushort, "peers": {<PEER_RECORD*>}}                       
PEER_RECORD := {"ushort":{"username":"string", "ipv4":"dotted_decimal_IP", "port": ushort}}                       
                       
MESSAGE := {"type":"message", "txid":ushort, "from":"string", "to":"string", "message":"string"}                       
                       
UPDATE := {"type":"update", "txid":ushort, "db": {<DB_RECORD*>}}                       
DB_RECORD := {"dotted_decimal_IP,ushort_port":{<PEER_RECORD*>}}                       
                       
DISCONNECT := {"type":"disconnect", "txid":ushort}                       
                       
ACK := {"type":"ack", "txid":ushort}                       
                       
ERROR := {"type":"error", "txid":ushort, "verbose": "string"}

Every message is [bencoded](https://en.wikipedia.org/wiki/Bencode) and encoded on the other site.

# Node
## Execution

    ./pds18-node --id <identification> --reg-ipv4 <IP> --reg-port <port>

*   --id unique identification for nodes, where there is a need to distinguish between them within a single guest (operating system) on which it runs
*   --reg-ipv4 and --reg-port is the IP address and port on which it accepts peer registration and database synchronization from neighboring nodes (peer and node messages);;

Example of execution

    ./pds18-node --id 42 --reg-ipv4 147.229.176.19 --reg-port 42060

# Peer
## Execution

    ./pds18-peer --id <identification> --username <user> --chat-ipv4 <IP> --chat-port <port> --reg-ipv4 <IP> --reg-port <port>
    
*   --id unique identification for peers, where there is a need to distinguish between them within a single guest (operating system) on which it runs

*   --username is a unique username identifying peer within the chat

*   --chat-ipv4 a --chat-port is the IP address and port on which the peer listens and receives messages from other peers or nodes

*   --reg-ipv4 a --reg-port is the IP address and port of the registration node to which the peer will: 

    * regularly send HELLO messages
    * send GETLIST queries to determine the current mapping.

Example of execution

    ./pds18-peer --id 1 --username xlogin00 --chat-ipv4 147.229.176.19 --chat-port 42069 --reg-ipv4 147.229.176.19 --reg-port 42060

# RPC

    ./pds18-rpc --id <identification> <"--peer"|"--node"> --command <cmd> --<parameter1> <parameter_value1> ...

*   --id contains the peer or node instance identifier to which the RPC command is to be sent

*   --peer or --node determines whether it is a command for a peer or registration node instance

*   --command and the parameter list determine the command and parameters related to the RPC call

List of peers commands:

    --peer --command message --from <username1> --to <username2> --message <msg>
CMD Tries to send chat message

    --peer --command getlist
Updating the peer database in a known peers network, ie sending a GETLIST message and having it confirmed

    --peer --command peers

Displays the current list of peers in the network, ie the peer exchanges GETLIST and LIST messages with the node, printing the contents of the LIST message

    --peer --command reconnect --reg-ipv4 <IP> --reg-port <port>

Disconnects from the current registration node (zero HELLO) and connects to the node specified in the parameters

List of nodes commands:

    --node --command database

Displays the current database of peers and their mapping

    --node --command neighbors
Displays the list of current neighbors of the registration node

    --node --command connect --reg-ipv4 <IP> --reg-port <port>
Tries to establish a neighborhood with a new registration node

    --node --command disconnect
Cancels the neighborhood with all nodes and disconnects the node from the network

    --node --command sync
Forces DB synchronization with nodes that are currently adjacent to the node

# Other libraries
In this project these libraries are used:
*   [JSON for Modern C++ ](https://github.com/nlohmann/json)
*   [Modern and efficient C++ Thread Pool Library](https://github.com/vit-vit/CTPL)
