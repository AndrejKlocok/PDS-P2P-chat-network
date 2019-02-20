/**
 * @file pds18-rpc.cpp
 * @author Andrej Klocok, xkloco00@vutbr.cz
 * @brief 
 * @version 0.1
 * @date 2019-02-20
 * 
 * 
 */
#include <getopt.h>
#include <stdlib.h>
#include <limits.h>

#include "src/rpc/RpcHandle.h"
#include "src/common/ErrHandle.h"

int main(int argc, char** argv)
{
    RpcHandle* rpchandle = new RpcHandle();

    int opt;
    int option_index;
    const char* shortOptions = "d:nrc:f::t::i::p::m::";
    unsigned long id;

    const option longOptions[] = {
        {"id", required_argument, nullptr, 'd'},
        {"node", optional_argument, nullptr, 'n'},
        {"peer", optional_argument, nullptr, 'r'},
        {"command", required_argument, nullptr, 'c'},
        {"from", optional_argument, nullptr, 'f'},
        {"to", optional_argument, nullptr, 't'},
        {"reg-ipv4", optional_argument, nullptr, 'i'},
        {"reg-port", optional_argument, nullptr, 'p'},
        {"message", optional_argument, nullptr, 'm'},
        {0, 0, 0, 0 }
    };

    while ((opt = getopt_long(argc, argv, shortOptions, longOptions, &option_index)) != -1) {
        
        switch (opt) {
            case 'd':
                //cast identifier as unisgned short
                id = strtoul(optarg, NULL, 0);
                //check boundaries
                if(id < USHRT_MAX)
                    rpchandle->setId( (unsigned short) id);
                else
                    ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
                
            break;
            
            case 'n':
                rpchandle->setClient(Client::node);
            break;

            case 'r':
                rpchandle->setClient(Client::peer);
            break;

            case 'c':
                rpchandle->setCommand(std::string(optarg));
            break;

            case 'f':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] )
                    rpchandle->setFrom(std::string(argv[optind++]));    
            break;

            case 't':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] )
                    rpchandle->setTo(std::string(argv[optind++]));   
            break;

            case 'i':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] )
                    rpchandle->setRegIpv4(std::string(argv[optind++])); 
            break;

            case 'p':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] )
                    rpchandle->setRegPort(std::string(argv[optind++])); 
            break;

            case 'm':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] )
                    rpchandle->setMessage(std::string(argv[optind++]));
            break;

            default:
                return 0;
        }
    }

    rpchandle->processRequest(argc);

    return 0;
}
