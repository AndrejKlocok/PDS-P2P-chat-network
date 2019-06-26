/**
 * @file RpcHandle.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef RPCHANDLE_H
#define RPCHANDLE_H

#include <string>
#include <map>

#include "../common/ErrHandle.h"
#include "RpcArguments.h"
#include "RpcNodeFunctions.h"
#include "RpcPeerFunctions.h"

class RpcHandle
{
private:
    RpcArguments arguments;

    typedef void (*argFunction) (RpcArguments*, int);
    std::map<std::string, argFunction > funcMap; 
    
public:
    RpcHandle();
    ~RpcHandle();

    void processRequest(int argc);

    void setClient( Client client);
    void setCommand( std::string command);
    void setRegPort( std::string regPort);
    void setRegIpv4( std::string regIpv4);
    void setFrom( std::string from);
    void setTo( std::string to);
    void setMessage( std::string message);
    void setId( unsigned short id);
};


#endif // !RPCHANDLE_H