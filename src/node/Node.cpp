#include "Node.h"

Node::Node(unsigned short id)
{
    this->id = id;
    this->isExc = false;
}

Node::~Node(){}

unsigned short Node::getId(){
    return this->id;
} 


void Node::setExc(){
    this->isExc = true;
}

bool Node::getIsExc(){
    return this->isExc;
}   