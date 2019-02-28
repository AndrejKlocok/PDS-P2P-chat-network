#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <unistd.h>

#include <string>

#include "common/Bencoder.h"
#include "common/MyExceptions.h"

#define BUFFER_SIZE 1024


struct Request
{
    struct sockaddr_in addr;
    socklen_t addrLen;
};

class Socket
{
protected:
    struct timeval timeout;
    int sockfd;
    struct sockaddr_in addr;
    Bencoder* benc;
public:
    Socket(std::string IP, ushort port);
    ~Socket();
    void setReusePort();
    void bindSocket();
    void sendData(json data);
    void sendData(json data, Request* addr);
    json recvData();
    json recvData(Request* addr);
    
    json recvDataTimeout();
};


#endif // !SOCKET_H