#ifndef RPCARGUMENTS_H
#define RPCARGUMENTS_H

#include <string>
enum class Client { peer, node};

struct RpcArguments
{
    std::string command;
    std::string regPort;
    std::string regIpv4;
    std::string from;
    std::string to;
    std::string message;
    unsigned short id;
    Client client;
};

#endif // !RPCARGUMENTS_H