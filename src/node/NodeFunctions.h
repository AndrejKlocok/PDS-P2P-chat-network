#ifndef NODEFUNCTIONS_H
#define NODEFUNCTIONS_H

#include "Node.h"

class Node;

using json = nlohmann::json;

void onDatabase(Node* node, json* data);
void onNeighbors(Node* node, json* data);
void onConnect(Node* node, json* data);
void onDisconnect(Node* node, json* data);
void onSync(Node* node, json* data);


void onHello(Node* node, json* data);
void onGetList(Node* node, json* data);

#endif // !NODEFUNCTIONS_H