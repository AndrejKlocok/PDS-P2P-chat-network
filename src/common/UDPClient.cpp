#include "UDPClient.h"

UDPClient::UDPClient(std::string IP, short port)
{
    socket = new Socket(IP, port);

}

UDPClient::~UDPClient(){

}

void UDPClient::sendMessage(json data){
    socket->sendData(data);
    
}

json UDPClient::recvMessage(){
    return socket->recvData();
}