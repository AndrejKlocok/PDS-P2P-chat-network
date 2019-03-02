#ifndef RPCPEERFUNCTIONS_H
#define RPCPEERFUNCTIONS_H

#include <vector>

#include <fstream>
#include <iostream>

#include "common/ErrHandle.h"
#include "common/Bencoder.h"
#include "RpcArguments.h"

void onMessage(RpcArguments* arguments, int argc);
void onGetList(RpcArguments* arguments, int argc);
void onPeers(RpcArguments* arguments, int argc);
void onReconnect(RpcArguments* arguments, int argc);

#endif // !RPCPEERFUNCTIONS_H