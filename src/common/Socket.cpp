/**
 * @file Socket.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#include "Socket.h"

/**
 * @brief Construct a new Socket:: Socket object
 * 
 * @param IP  ipv4 string
 * @param port  port number
 */
Socket::Socket(std::string IP, unsigned short port){
    benc = new Bencoder();
    request = Socket::createRequest(IP, port);
    
    // create socket 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        throw SocketExc();
    }
}

/**
 * @brief Destroy the Socket:: Socket object
 * 
 */
Socket::~Socket(){
    close(sockfd);
}

/**
 * @brief Bind socket to the port
 * 
 */
void Socket::bindSocket(){
    if ( bind(sockfd, (const struct sockaddr *)& request->addr,  
            sizeof(request->addr)) < 0 ) 
    { 
        throw SocketBindExc();
    } 
}

/**
 * @brief Set flag reuse port
 * 
 */
void Socket::setReusePort(){
    int on = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) <0){
        throw SocketOptionExc();;
    }
}

/**
 * @brief Set 2second timeout on socket
 * 
 */
void Socket::setTimeout2s(){
    //set timeout
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof(timeout)) < 0) {
        throw SocketOptionExc();;
    }
}

/**
 * @brief Send data with stored request
 * 
 * @param data json object
 */
void Socket::sendData(json data){
    return sendData(data, request);
}

/**
 * @brief Send data to given address via request struct
 * 
 * @param data json object
 * @param req struct
 */
void Socket::sendData(json data, Request* req){
    std::string message = benc->encode(data);

    sendto(sockfd, message.c_str(), message.length(),  
        0, (struct sockaddr *) &req->addr, req->addrLen);

}

/**
 * @brief Send data to given address via request struct
 * 
 * @param data json object
 * @param req struct
 */
void Socket::sendDataErr(std::string message, Request* req){
    sendto(sockfd, message.c_str(), message.length(),  
        0, (struct sockaddr *) &req->addr, req->addrLen);

}

/**
 * @brief Receive data from socket
 * 
 * @return json 
 */
json Socket::recvData(){
    return recvData(request);
}

/**
 * @brief Receive data from socket and initialize request structure
 * 
 * @param req structure
 * @return json object
 */
json Socket::recvData(Request* req){
    std::string recvString;
    std::vector<char> buff;
    buff.resize(BUFFER_SIZE);

    int n = 0;
    int nmod = 0;
    do
    {
        n = recvfrom(sockfd, buff.data(), buff.size(),  
            MSG_PEEK, ( struct sockaddr *) &req->addr, 
            &req->addrLen);
        
        nmod = n % BUFFER_SIZE;

        if(n != -1){
            //if buffer is full resize
            if(!nmod)
                buff.resize(n + BUFFER_SIZE);
        }
        else{
            throw SocketDataExc();
        }

    } while(nmod == 0);
    
    //read all data
    n = recvfrom(sockfd, buff.data(), buff.size(),  
            0, ( struct sockaddr *) &req->addr, 
            &req->addrLen);
    //check error
    if(n < 0){
        throw SocketDataExc();
    }
    //append string
    recvString.append(buff.cbegin(), buff.cend());

    return benc->decode(recvString);
}

/**
 * @brief Return request structure
 * 
 * @return Request* 
 */
Request* Socket::getRequest(){
    return request;
}

/**
 * @brief Create Request structure
 * 
 * @param IP string
 * @param port number
 * @return Request* structure
 */
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