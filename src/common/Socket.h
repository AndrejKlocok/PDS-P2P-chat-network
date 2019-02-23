#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 


#include <string>

class Socket
{
private:
    int sockfd;
    struct sockaddr_in addr;

public:
    Socket(std::string IP, short port);
    ~Socket();
};


#endif // !SOCKET_H