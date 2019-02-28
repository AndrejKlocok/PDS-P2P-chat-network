#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "Socket.h"


class UDPClient
{
private:
    Socket* socket;
public:
    UDPClient(std::string IP, short port);
    ~UDPClient();

    void sendMessage(json data);
    json recvMessage();
};


#endif // !UDPCLIENT_H