/**
 * @file RpcNodeFunctions.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#include "RpcNodeFunctions.h"

/**
 * @brief Send request to pipe,  on which peer listens
 * 
 * @param id        name of the pipe
 * @param request   json
 */
void sendPipeNodeRequest(unsigned short id, json request){
    try
    {
        std::ofstream file{"/tmp/"+std::to_string(id)};
        file << request.dump();
        file.close();
    
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}


/**
 * @brief Displays the current database of peers and their mapping
 * 
 * @param arguments 
 * @param argc 
 */
void onDatabase(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 6 || arguments->client != Client::node){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json
    json request = {
        {"type", "database"}
    };

    sendPipeNodeRequest(arguments->id, request);
}

/**
 * @brief Displays the list of current neighbors of the registration node
 * 
 * @param arguments 
 * @param argc 
 */
void onNeighbors(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 6 || arguments->client != Client::node){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json
    json request = {
        {"type", "neighbors"}
    };

    sendPipeNodeRequest(arguments->id, request);    
}

/**
 * @brief Tries to establish a neighborhood with a new registration node
 * 
 * @param arguments 
 * @param argc 
 */
void onConnect(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 10 || arguments->client != Client::node || arguments->regIpv4.empty() || arguments->regPort.empty()){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json
    json request = {
        {"type", "connect"},
        {"ipv4", arguments->regIpv4},
        {"port", std::stoi(arguments->regPort)}
    };

    sendPipeNodeRequest(arguments->id, request);
}

/**
 * @brief Cancels the neighborhood with all nodes and disconnects the node from the network
 * 
 * @param arguments 
 * @param argc 
 */
void onDisconnect(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 6 || arguments->client != Client::node){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json
    json request = {
        {"type", "disconnect"}
    };

    sendPipeNodeRequest(arguments->id, request);
}

/**
 * @brief Forces DB synchronization with nodes that are currently adjacent to the node
 * 
 * @param arguments 
 * @param argc 
 */
void onSync(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 6 || arguments->client != Client::node){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json
    json request = {
        {"type", "sync"}
    };

    sendPipeNodeRequest(arguments->id, request);
}
