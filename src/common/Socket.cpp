#include "Socket.h"

Socket::Socket(std::string IP, short port){
    memset(&addr, 0, sizeof(addr)); 

    addr.sin_family    = AF_INET; // IPv4 
    addr.sin_port = htons(port); 
    //ip not provided
    if(IP.empty()){
        addr.sin_addr.s_addr = INADDR_ANY; 
    }
    else{
        addr.sin_addr.s_addr = (char) IP.c_str();
    }
    
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
}

Socket::~Socket(){}