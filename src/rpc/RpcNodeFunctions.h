#ifndef RPCNODEFUNCTIONS_H
#define RPCNODEFUNCTIONS_H

#include "common/ErrHandle.h"
#include "common/json.hpp"

#include "RpcArguments.h"

using json = nlohmann::json;

void onDatabase(RpcArguments* arguments, int argc);
void onNeighbors(RpcArguments* arguments, int argc);
void onConnect(RpcArguments* arguments, int argc);
void onDisconnect(RpcArguments* arguments, int argc);
void onSync(RpcArguments* arguments, int argc);


#endif // !RPCNODEFUNCTIONS_H
