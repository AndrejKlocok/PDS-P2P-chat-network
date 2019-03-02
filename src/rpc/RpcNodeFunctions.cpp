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
        {"type", "database"},
        {"txid", arguments->id}
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
        {"type", "neighbors"},
        {"txid", arguments->id}
    };

    sendPipeNodeRequest(arguments->id, request);    
}

/**
 * @brief --id <ushort> --node --command connect --reg-ipv4 <IP> --reg-port <port>, který se pokusí 
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
        {"txid", arguments->id},
        {"ipv4", arguments->regIpv4},
        {"port", arguments->regPort}
    };

    sendPipeNodeRequest(arguments->id, request);
}

/**
 * @brief --id <ushort> --node --command disconnect --reg-ipv4 <IP>, který zruší sousedství s daným uzlem
 * 
 * @param arguments 
 * @param argc 
 */
void onDisconnect(RpcArguments* arguments, int argc){
    //last check of valid given args
    if(argc != 8 || arguments->client != Client::node || arguments->regIpv4.empty()){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    //build json
    json request = {
        {"type", "disconnect"},
        {"txid", arguments->id},
        {"ipv4", arguments->regIpv4}
    };

    sendPipeNodeRequest(arguments->id, request);
}

/**
 * @brief --id <ushort> --node --command sync --reg-ipv4 <IP>, která vynutí synchronizaci s daným sousedícím uzlem
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
        {"type", "sync"},
        {"txid", arguments->id},
        {"ipv4", arguments->regIpv4}
    };

    sendPipeNodeRequest(arguments->id, request);
}
