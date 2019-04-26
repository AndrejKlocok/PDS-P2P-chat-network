#include "RpcFunctions.h"
/**
 * @brief Send getlist message
 * 
 * @param peer 
 * @param data 
 */
void onGetList(Peer* peer, json* data){
    unsigned short transactionNumber = peer->getStorage()->getTransactionNumber();
    json request = {
            {"type", "getlist"},
            {"txid", transactionNumber},
        };
    peer->sendSocketWait(request);
}

/**
 * @brief Sent getlist and set peerdisp flag
 * 
 * @param peer 
 * @param data 
 */
void onPeers(Peer* peer, json* data){

    peer->getStorage()->setPeerDisp(true);
    onGetList(peer, data);
}
/**
 * @brief Store msg to queue and send getlist message
 * 
 * @param peer 
 * @param data 
 */
void onMessage(Peer* peer, json* data){
    peer->getStorage()->insertMessage(*data);
    onGetList(peer, data);
}
/**
 * @brief Connect to other node descibed in data
 * 
 * @param peer 
 * @param data 
 */
void onReconnect(Peer* peer, json* data){
    peer->reconect((*data)["ipv4"], (*data)["port"]);
}