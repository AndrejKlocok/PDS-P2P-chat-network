/**
 * @file Socket.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
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

/**
 * @brief Structure that holds sockaddr_in
 * 
 */
struct Request
{
    struct sockaddr_in addr;
    socklen_t addrLen;
};

/**
 * @brief Socket abstraction class
 * 
 */
class Socket
{
protected:
    struct timeval timeout;
    int sockfd;
    Request* request;
    Bencoder* benc;
public:
    Socket(std::string IP, unsigned short port);
    ~Socket();
    void setReusePort();
    void setTimeout2s();
    void bindSocket();
    void sendData(json data);
    void sendData(json data, Request* addr);
    json recvData();
    json recvData(Request* addr);
    Request* getRequest();
    static Request* createRequest(std::string IP, unsigned short port);
    void sendDataErr(std::string message, Request* req);
};


#endif // !SOCKET_H