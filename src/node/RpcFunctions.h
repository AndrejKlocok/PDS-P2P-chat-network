/**
 * @file RpcFunctions.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef RPCFUNCTIONS_H
#define RPCFUNCTIONS_H

#include "Node.h"

class Node;

void onDatabase(Node* node, json* data);
void onNeighbors(Node* node, json* data);
void onConnect(Node* node, json* data);
void onDisconnect(Node* node, json* data);
void onSync(Node* node, json* data);

#endif // !RPCFUNCTIONS_H