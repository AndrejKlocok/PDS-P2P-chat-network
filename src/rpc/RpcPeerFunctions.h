#ifndef RPCPEERFUNCTIONS_H
#define RPCPEERFUNCTIONS_H

#include <iostream>

#include "common/ErrHandle.h"
#include "common/json.hpp"
#include "RpcArguments.h"

using json = nlohmann::json;

void onMessage(RpcArguments* arguments, int argc);
void onGetList(RpcArguments* arguments, int argc);
void onPeers(RpcArguments* arguments, int argc);
void onReconnect(RpcArguments* arguments, int argc);

#endif // !RPCPEERFUNCTIONS_H