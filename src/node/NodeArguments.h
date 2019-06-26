/**
 * @file NodeArguments.h
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#ifndef NODEARGUMENTS_H
#define NODEARGUMENTS_H

#include <string>

struct NodeArguments
{
    unsigned short regPort;
    std::string regIpv4;
    unsigned short id;
};


#endif // !NODEARGUMENTS_H  