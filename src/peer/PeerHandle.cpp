#include "PeerHandle.h"

PeerHandle::PeerHandle(/* args */){}

PeerHandle::~PeerHandle(){
    unlink(this->pipeName.c_str());
    peer->~Peer();    
}

void PeerHandle::processRequest(int argc){
    if(argc != 13 ){
        ErrHandle::printErrMessage(ErrCodes::WrongArg, "");
        return;
    }
    // --id <identifikátor> --username <user> --chat-ipv4 <IP> --chat-port <port> --reg-ipv4 <IP> --reg-port <port>
    std::cout<<"IP: " << args.chatIpv4<<", Port: "<<args.chatPort<<std::endl; 
    try
    {
        Socket* socket = new Socket(args.chatIpv4, args.chatPort);
        this->pipeName = std::to_string(args.id);
        peerServer = new PeerServer(socket);
        
        peer = new Peer(&args, socket);
        
        std::thread rpcThread(rpcServer, peer, this->pipeName);
        
        peerServer->listen(peer);

        rpcThread.join();
        
    }
    catch(const std::exception& e)
    {
        peer->setExc();
        std::cerr << e.what() << '\n';
    }
    
}

/**
 * @brief 
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
        mkfifo(pipeName.c_str(), 0666);
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
                std::cout<< request.dump()<<std::endl;
                peer->rpcRequest(request);

            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            buff.clear();
            
        } while (!peer->getIsExc());
        
    }
    catch(const std::exception& e)
    {
        peer->setExc();
        std::cerr << e.what() << '\n';
    }
    
}

void PeerHandle::setRegPort(  unsigned short regPort){
    this->args.regPort = regPort;
}

void PeerHandle::setRegIpv4( std::string regIpv4){
    this->args.regIpv4 = regIpv4;
}

void PeerHandle::setId( unsigned short id){
    this->args.id = id;
}

void PeerHandle::setUsername( std::string username){
    this->args.username = username;
}

void PeerHandle::setChatPort(  unsigned short chatPort){
    this->args.chatPort = chatPort;
}

void PeerHandle::setChatIpv4( std::string chatIpv4){
    this->args.chatIpv4 = chatIpv4;
}