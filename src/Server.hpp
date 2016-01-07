#ifndef Strong_Server_hpp
#define Strong_Server_hpp

#include "Network.hpp"
#include "ClientConnection.hpp"

class Server{
public:

    bool running = true;
    bool serverIsStarted = false;

    int port;

    TCPsocket* socket = new TCPsocket();
    IPaddress* ip = new IPaddress();

    vector<ClientConnection*> clientList;
    vector<ClientConnection*> clientRemoveList;

    Server();

    ~Server(){}

    void update();
    void startServer();
    void setPort(bool setPort);

    void clientDisconnected(ClientConnection* cc, bool intentional);

    void processPacket(ClientConnection* from, unsigned char code, unsigned char* data);
    void sendPacket(ClientConnection* to, unsigned char code);

};

#endif
