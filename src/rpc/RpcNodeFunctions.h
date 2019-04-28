/**
 * @file RpcNodeFunctions.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef RPCNODEFUNCTIONS_H
#define RPCNODEFUNCTIONS_H

#include <fstream>
#include <iostream>

#include "common/ErrHandle.h"
#include "common/Bencoder.h"
#include "RpcArguments.h"


void onDatabase(RpcArguments* arguments, int argc);
void onNeighbors(RpcArguments* arguments, int argc);
void onConnect(RpcArguments* arguments, int argc);
void onDisconnect(RpcArguments* arguments, int argc);
void onSync(RpcArguments* arguments, int argc);

#endif // !RPCNODEFUNCTIONS_H
