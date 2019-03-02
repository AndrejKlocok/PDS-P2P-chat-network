#include "Node.h"

Node::Node()
{
    this->isExc = false;
    funcMap["database"]     = onDatabase;
    funcMap["neighbors"]    = onNeighbors;
    funcMap["connect"]      = onConnect;
    funcMap["disconnect"]   = onDisconnect;
    funcMap["sync"]         = onSync;
    funcMap["hello"]        = onHello;
    funcMap["getlist"]      = onGetList;
}

Node::~Node(){}


void Node::nodeRequest(json request){

    /*if(request["txid"] != this->id){
        throw NodeWrongId();
    }*/
    //find desired action in map of actions
    auto iter = funcMap.find(request["type"]);

    //call function
    if(iter != funcMap.end()){
        iter->second(this, &request);
    }
    else{
        throw UnknownType();
    }
}

void Node::setExc(){
    this->isExc = true;
}

bool Node::getIsExc(){
    return this->isExc;
}