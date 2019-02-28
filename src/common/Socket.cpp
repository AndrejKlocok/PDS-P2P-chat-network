#include "Socket.h"

Socket::Socket(std::string IP, ushort port){
    benc = new Bencoder();
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET; 
    addr.sin_port   = htons(port);

    // ip not provided -> 0.0.0.0
    if(IP.empty()){
        addr.sin_addr.s_addr = INADDR_ANY; 
    }
    // given ip
    else{
        inet_pton(AF_INET, IP.c_str(), &addr.sin_addr.s_addr);
    }

    // create socket 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        throw SocketExc();
    }

    //set timeout
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    /*if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof(timeout)) < 0) {
        throw SocketOptionExc();;
    }*/
}

Socket::~Socket(){
    close(sockfd);
}

void Socket::bindSocket(){
    if ( bind(sockfd, (const struct sockaddr *)& addr,  
            sizeof(addr)) < 0 ) 
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

void Socket::sendData(json data){
    Request req;
    
    req.addr = this->addr;
    req.addrLen = sizeof(this->addr);

    return sendData(data, &req);
}

void Socket::sendData(json data, Request* req){
    std::string message = benc->encode(data);

    sendto(sockfd, message.c_str(), message.length(),  
        MSG_CONFIRM, (const struct sockaddr *) &req->addr, req->addrLen);

}

json Socket::recvData(){
    Request req;
    
    req.addr = this->addr;
    req.addrLen = sizeof(this->addr);
    return recvData(&req);
}

json Socket::recvData(Request* req){
    std::string recvString;
    std::vector<char> buff(BUFFER_SIZE);
    int n;

    do
    {
        n = recvfrom(sockfd, &buff[0], BUFFER_SIZE,  
            MSG_WAITALL, ( struct sockaddr *) &req->addr, 
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

json Socket::recvDataTimeout(){
    return this->recvData();
}