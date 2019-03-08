#ifndef NODEFUNCTIONS_H
#define NODEFUNCTIONS_H

#include "Node.h"

class Node;

void onHello(Node* node, json data, Request* request, Socket* socket);
void onGetList(Node* node, json data, Request* request, Socket* socket);
void onAck(Node* node, json data, Request* request, Socket* socket);
void onError(Node* node, json data, Request* request, Socket* socket);

#endif // !NODEFUNCTIONS_H