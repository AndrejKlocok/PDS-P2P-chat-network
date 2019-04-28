/**
 * @file RpcHandle.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#include "RpcHandle.h"

RpcHandle::RpcHandle(/* args */)
{
    //init funcmap
    funcMap["message"]      =   onMessage;
    funcMap["getlist"]      =   onGetList;
    funcMap["peers"]        =   onPeers;
    funcMap["reconnect"]    =   onReconnect;
    funcMap["database"]     =   onDatabase;
    funcMap["neighbors"]    =   onNeighbors;
    funcMap["connect"]      =   onConnect;
    funcMap["disconnect"]   =   onDisconnect;
    funcMap["sync"]         =   onSync;
}

RpcHandle::~RpcHandle(){}

void RpcHandle::processRequest(int argc){

    //find desired action in map of actions
    auto iter = funcMap.find(arguments.command);

    //call function
    if(iter != funcMap.end()){
        iter->second(&arguments, argc);
    }
    else{
        ErrHandle::printErrMessage(ErrCodes::UnknownCmd, arguments.command);
    }
}

void RpcHandle::setClient( Client client){
    this->arguments.client = client;
}

void RpcHandle::setCommand( std::string command){
    this->arguments.command = command;
}

void RpcHandle::setRegPort( std::string regPort){
    this->arguments.regPort = regPort;
}

void RpcHandle::setRegIpv4( std::string regIpv4){
    this->arguments.regIpv4 = regIpv4;
}

void RpcHandle::setFrom( std::string from){
    this->arguments.from = from;
}

void RpcHandle::setTo( std::string to){
    this->arguments.to = to;
}

void RpcHandle::setMessage( std::string message){
    this->arguments.message = message;
}

void RpcHandle::setId( unsigned short id){
    this->arguments.id = id;
}