#include "Socket.h"

Socket::Socket(std::string IP, unsigned short port){
    benc = new Bencoder();
    request = Socket::createRequest(IP, port);
    
    // create socket 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        throw SocketExc();
    }
}

Socket::~Socket(){
    close(sockfd);
}

void Socket::bindSocket(){
    if ( bind(sockfd, (const struct sockaddr *)& request->addr,  
            sizeof(request->addr)) < 0 ) 
    { 
        throw SocketBindExc();
    } 
}

void Socket::setReusePort(){
    int on = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) <0){
        throw SocketOptionExc();;
    }
}

void Socket::setTimeout2s(){
    //set timeout
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof(timeout)) < 0) {
        throw SocketOptionExc();;
    }
}

void Socket::sendData(json data){
    return sendData(data, request);
}

void Socket::sendData(json data, Request* req){
    std::string message = benc->encode(data);

    sendto(sockfd, message.c_str(), message.length(),  
        MSG_CONFIRM, (struct sockaddr *) &req->addr, req->addrLen);

}

json Socket::recvData(){
    return recvData(request);
}

json Socket::recvData(Request* req){
    std::string recvString;
    std::vector<char> buff(BUFFER_SIZE);
    int n;

    do
    {
        n = recvfrom(sockfd, &buff[0], BUFFER_SIZE,  
            0, ( struct sockaddr *) &req->addr, 
            &req->addrLen);
        
        if(n == -1){
            throw SocketDataExc();
        }
        else{
            recvString.append(buff.cbegin(), buff.cend());
        }

    } while(n == BUFFER_SIZE);
    
    return benc->decode(recvString);
}

Request* Socket::getRequest(){
    return request;
}

Request* Socket::createRequest(std::string IP, unsigned short port){
    Request* req = new Request();

    memset(&req->addr, 0, sizeof(req->addr)); 

    req->addr.sin_family = AF_INET; 
    req->addr.sin_port   = htons(port);

    // ip not provided -> 0.0.0.0
    if(IP.empty()){
        req->addr.sin_addr.s_addr = INADDR_ANY; 
    }
    // given ip
    else{
        inet_pton(AF_INET, IP.c_str(), &req->addr.sin_addr.s_addr);
    }
    req->addrLen = sizeof(req->addr);

    return req;
}