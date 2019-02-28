#include <getopt.h>
#include <stdlib.h>
#include <limits.h>

#include "src/node/NodeHandle.h"
#include "src/common/ErrHandle.h"

int main(int argc, char** argv)
{
    NodeHandle* nodeHandle = new NodeHandle();

    int opt;
    int option_index;
    const char* shortOptions = "d:::i::p::";
    unsigned long id, port;

    const option longOptions[] = {
        {"id", required_argument, nullptr, 'd'},
        {"reg-ipv4", optional_argument, nullptr, 'i'},
        {"reg-port", optional_argument, nullptr, 'p'},
        {0, 0, 0, 0 }
    };

    while ((opt = getopt_long(argc, argv, shortOptions, longOptions, &option_index)) != -1) {
        
        switch (opt) {
            case 'd':
                //cast identifier as unisgned short
                id = strtoul(optarg, NULL, 0);
                //check boundaries
                if(id < USHRT_MAX)
                    nodeHandle->setId( (unsigned short) id);
                else
                    ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
                
            break;

            case 'i':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] )
                    nodeHandle->setRegIpv4(std::string(argv[optind++])); 
            break;

            case 'p':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] ){
                    port = strtoul(argv[optind++], NULL, 0);
                    //check boundaries
                    if(port < USHRT_MAX)
                        nodeHandle->setRegPort( (unsigned short) port); 
                    else
                        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
                }
                
            break;

            default:
                return 0; 
        }
    }

    nodeHandle->processRequest(argc);

    return 0;
}