#include "RpcPeerFunctions.h"

/**
 * @brief --id <ushort> --peer --command message --from <username1> --to <username2> --message <message>
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
    Bencoder* benc = new Bencoder();
    //build json 
    json request = {
        {"type", "message"},
        {"txid", arguments->id},
        {"from", arguments->from},
        {"to", arguments->to},
        {"message", arguments->message}
    };
    
    std::string bencoded = benc->encode(request);
    json decoded;
    try
    {
        decoded = benc->decode(bencoded);
        std::cout << decoded.dump() << std::endl;
    }
    catch(const BencodeExc& e)
    {
        ErrHandle::printErrMessage(ErrCodes::ParseBencodedStringErr, bencoded);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief --id <ushort> --peer --command getlist, který vynutí aktualizaci seznamu v síti známých peerů
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
        {"type", "getlist"},
        {"txid", arguments->id}
    };
}

/**
 * @brief --id <ushort>  --peer --command peers, který zobrazí aktuální seznam peerů v síti
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
        {"type", "peerlist"},
        {"txid", arguments->id}
    };
}

/**
 * @brief --id <ushort> --peer --command reconnect --reg-ipv4 <IP> --reg-port <port>, který se odpojí od současného registračního
 *  uzlu (nulové HELLO) a připojí se k uzlu specifikovaném v parametrech
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
        {"txid", arguments->id},
        {"ipv4", arguments->regIpv4},
        {"port", arguments->regPort}
    };
}