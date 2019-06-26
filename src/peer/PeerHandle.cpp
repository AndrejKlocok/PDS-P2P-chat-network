/**
 * @file PeerHandle.cpp
 * @author Andrej Klocok (xkloco00@vutbr.cz)
 * @version 1.0
 * @date 2019-04-28
 * 
 */
#include "PeerHandle.h"

PeerHandle::PeerHandle(/* args */){}

PeerHandle::~PeerHandle(){
    unlink(this->pipeName.c_str());
    peer->~Peer();    
}
/**
 * @brief Initialize peer object
 * 
 * @param argc number of arguments
 */
void PeerHandle::processRequest(int argc){
    if(argc != 13 ){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    try
    {
        int threadsNumb = 0;
        std::map<std::string, std::string> config = readConfig("config");
        
        auto iter = config.find("ThreadPoolClient");

        if(iter != config.end()){
            threadsNumb = stoi(iter->second);
        }
        else{
            std::cerr << "Threadpool size not configured from config file, using default: 2" << '\n';
            threadsNumb = 2;
        }

        peer = new Peer(&args);
        peer->registerRpcRequest("sda", onGetList);
        peer->registerRpcRequest("getlist", onGetList);
        peer->registerRpcRequest("message", onMessage);
        peer->registerRpcRequest("peers", onPeers);
        peer->registerRpcRequest("reconnect", onReconnect);

        peer->registerBaseRequest("list", onList);
        peer->registerBaseRequest("error", onError);
        peer->registerBaseRequest("ack", onAck);
        peer->registerBaseRequest("message", onMessage);

        Socket* socket = new Socket(args.chatIpv4, args.chatPort);
        peer->setSocket(socket);

        this->pipeName = "/tmp/"+std::to_string(args.id);
        peerServer = new PeerServer(socket);

        if(mkfifo(pipeName.c_str(), 0666) == -1){
            throw LocalException("Pipe errno: %s", strerror(errno));
        }

        peer->runCommunicator();
        std::thread rpcThread(rpcServer, peer, this->pipeName);
        
        peerServer->listen(peer, threadsNumb);

        rpcThread.join();
        
    }
    catch(const std::exception& e)
    {
        peer->getStorage()->setExc();
        std::cerr << e.what() << '\n';
    }
    
}

/**
 * @brief RPC thread worker function 
 * 
 * @param peer 
 * @param pipeName 
 */
void PeerHandle::rpcServer(Peer* peer, std::string pipeName){
    int fd;             //descriptor
    char c;             //char 
    std::string buff;   //buffer
    json request;       //request to peer
    try
    {
        do
        {
           fd = open(pipeName.c_str(), O_RDONLY);
            
            //read
            while ( read(fd, &c, sizeof(c)) > 0 ){
                buff += c;
            }
            close(fd);
            try
            {
                request = json::parse(buff);
                peer->rpcRequest(request);

            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            buff.clear();
            
        } while (!peer->getStorage()->getIsExc());
        
    }
    catch(const std::exception& e)
    {
        peer->getStorage()->setExc(); 
        std::cerr << e.what() << '\n';
    }
    
}
/**
 * @brief Setter
 * 
 * @param regPort 
 */
void PeerHandle::setRegPort(  unsigned short regPort){
    this->args.regPort = regPort;
}
/**
 * @brief Setter
 * 
 * @param regIpv4 
 */
void PeerHandle::setRegIpv4( std::string regIpv4){
    this->args.regIpv4 = regIpv4;
}

/**
 * @brief Setter
 * 
 * @param id 
 */
void PeerHandle::setId( unsigned short id){
    this->args.id = id;
}
/**
 * @brief Setter
 * 
 * @param username 
 */
void PeerHandle::setUsername( std::string username){
    this->args.username = username;
}
/**
 * @brief Setter
 * 
 * @param chatPort 
 */
void PeerHandle::setChatPort(  unsigned short chatPort){
    this->args.chatPort = chatPort;
}
/**
 * @brief Setter
 * 
 * @param chatIpv4 
 */
void PeerHandle::setChatIpv4( std::string chatIpv4){
    this->args.chatIpv4 = chatIpv4;
}