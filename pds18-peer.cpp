#include <getopt.h>
#include <stdlib.h>
#include <limits.h>

#include "src/peer/PeerHandle.h"
#include "src/common/ErrHandle.h"

//static variable
static PeerHandle* peerHandle = new PeerHandle();

/**
 * @brief Handler for SIGINT signal. Cleans pipe
 * 
 * @param signum 
 */
void signalHandler( int signum ) {

    peerHandle->~PeerHandle();
    exit(signum);  
}

int main(int argc, char** argv)
{
    
    int opt;
    int option_index;
    const char* shortOptions = "d:::i::p::";
    unsigned long id, port;
    // --id <identifikátor> --username <user> --chat-ipv4 <IP> --chat-port <port> --reg-ipv4 <IP> --reg-port <port>
    const option longOptions[] = {
        {"id", required_argument, nullptr, 'd'},
        {"username", required_argument, nullptr, 'u'},
        {"chat-ipv4", required_argument, nullptr, 'i'},
        {"chat-port", required_argument, nullptr, 'p'},
        {"reg-ipv4", required_argument, nullptr, 'r'},
        {"reg-port", required_argument, nullptr, 's'},
        {0, 0, 0, 0 }
    };

    signal(SIGINT, signalHandler);

    while ((opt = getopt_long(argc, argv, shortOptions, longOptions, &option_index)) != -1) {
        
        switch (opt) {
            case 'd':
                //cast identifier as unisgned short
                id = strtoul(optarg, NULL, 0);
                //check boundaries
                if(id < USHRT_MAX)
                    peerHandle->setId( (unsigned short) id);
                else
                    ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
                
            break;

            case 'i':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] )
                    peerHandle->setChatIpv4(std::string(argv[optind++])); 
            break;

            case 'p':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] ){
                    port = strtoul(argv[optind++], NULL, 0);
                    //check boundaries
                    if(port < USHRT_MAX)
                        peerHandle->setChatPort( (unsigned short) port); 
                    else
                        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
                }
                
            break;

             case 'r':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] )
                    peerHandle->setRegIpv4(std::string(argv[optind++])); 
            break;

            case 's':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] ){
                    port = strtoul(argv[optind++], NULL, 0);
                    //check boundaries
                    if(port < USHRT_MAX)
                        peerHandle->setRegPort( (unsigned short) port); 
                    else
                        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
                }
                
            break;

            case 'u':
                if( !optarg && NULL != argv[optind] && '-' != argv[optind][0] )
                    peerHandle->setUsername(std::string(argv[optind++])); 
            break;

            default:
                return 0; 
        }
    }

    peerHandle->processRequest(argc);

    return 0;
}
