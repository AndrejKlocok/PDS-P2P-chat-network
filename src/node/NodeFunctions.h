#ifndef NODEFUNCTIONS_H
#define NODEFUNCTIONS_H

#include "Node.h"

class Node;

void onHello(Node* node, json data, Request* request);
void onGetList(Node* node, json data, Request* request);
void onAck(Node* node, json data, Request* request);
void onError(Node* node, json data, Request* request);
void onUpdate(Node* node, json data, Request* request);
void onDisconnect(Node* node, json data, Request* request);


#endif // !NODEFUNCTIONS_H