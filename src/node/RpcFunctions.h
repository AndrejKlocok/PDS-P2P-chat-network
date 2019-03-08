#ifndef RPCFUNCTIONS_H
#define RPCFUNCTIONS_H

#include "Node.h"

class Node;

using json = nlohmann::json;

void onDatabase(Node* node, json* data, json* response);
void onNeighbors(Node* node, json* data, json* response);
void onConnect(Node* node, json* data, json* response);
void onDisconnect(Node* node, json* data, json* response);
void onSync(Node* node, json* data, json* response);

#endif // !RPCFUNCTIONS_H