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
 * @brief --id <ushort> --node --command database, který zobrazí aktuální databázi peerů a jejich mapování
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
 * @brief --id <ushort> --node --command neighbors, který zobrazí seznam aktuálních sousedů registračního uzlu
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
 * @brief --id <ushort> --node --command connect --reg-ipv4 <IP> --reg-port <port>, který se pokusí navázat sousedství s novým registračním uzlem
 *      navázat sousedství s novým registračním uzlem
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
 * @brief --id <ushort> --node --command disconnect, který zruší sousedství se všemi uzly (stáhne z jejich DB své autoritativní záznamy) a odpojí node od sítě
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
 * @brief --id <ushort> --node --command sync, která vynutí synchronizaci DB s uzly, se kterými node aktuálně sousedí
 * 
 * @param arguments 
 * @param argc 
 */
void onSync(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 8 || arguments->client != Client::node || arguments->regIpv4.empty()){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json
    json request = {
        {"type", "sync"}
    };

    sendPipeNodeRequest(arguments->id, request);
}
