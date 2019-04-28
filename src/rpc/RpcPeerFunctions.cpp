/**
 * @file RpcPeerFunctions.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#include "RpcPeerFunctions.h"

/**
 * @brief Send request to pipe,  on which peer listens
 * 
 * @param id        name of the pipe
 * @param request   json
 */
void sendPipePeerRequest(unsigned short id, json request){
    try
    {
        std::ofstream file{std::to_string(id)};
        file << request.dump();
        file.close();
    
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief CMD Tries to send chat message
 * 
 * @param arguments 
 * @param argc 
 */
void onMessage(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 12 || arguments->client != Client::peer || arguments->from.empty() || arguments->to.empty() || arguments->message.empty()){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json 
    json request = {
        {"type", "message"},
        {"from", arguments->from},
        {"to", arguments->to},
        {"message", arguments->message}
    };
    
    sendPipePeerRequest(arguments->id, request);
}

/**
 * @brief Updating the peer database in a known peers network, ie sending a GETLIST 
 * message and having it confirmed
 * 
 * @param arguments 
 * @param argc 
 */
void onGetList(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 6 || arguments->client != Client::peer){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json
    json request = {
        {"type", "getlist"}
    };
    sendPipePeerRequest(arguments->id, request);
}

/**
 * @brief Displays the current list of peers in the network, ie the peer exchanges GETLIST 
 * and LIST messages with the node, printing the contents of the LIST message
 * 
 * @param arguments 
 * @param argc 
 */
void onPeers(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 6 || arguments->client != Client::peer){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json
    json request = {
        {"type", "peers"}
    };
    sendPipePeerRequest(arguments->id, request);
}

/**
 * @brief Disconnects from the current registration node (zero HELLO) and connects to the node specified in the parameters
 * 
 * @param arguments
 * @param argc 
 */
void onReconnect(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 10 || arguments->client != Client::peer || arguments->regIpv4.empty() || arguments->regPort.empty()){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json
    json request = {
        {"type", "reconnect"},
        {"ipv4", arguments->regIpv4},
        {"port", std::stoi(arguments->regPort)}
    };
    sendPipePeerRequest(arguments->id, request);
}