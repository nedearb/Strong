//
//  ClientConnection.cpp
//  Strong
//
//  Created by Braeden Atlee on 1/7/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#include "ClientConnection.hpp"
#include "Server.hpp"
#include "Debug.hpp"


ClientConnection::ClientConnection(TCPsocket* hostSocket, TCPsocket* socket, Server* server){
    this->hostSocket = hostSocket;
    this->socket = socket;
    this->server = server;

    if((ip = SDLNet_TCP_GetPeerAddress(*socket))){
        uint32_t n = SDLNet_Read32(&ip->host);
        string address;
        address += to_string((n & 0xFF000000) >> 24);
        address += ".";
        address += to_string((n & 0x00FF0000) >> 16);
        address += ".";
        address += to_string((n & 0x0000FF00) >> 8);
        address += ".";
        address += to_string((n & 0x000000FF));
        debugf("Client connected through address: %s:%d", address.c_str(), SDLNet_Read16(&ip->port));
	}else{
		errorf("SDLNet_TCP_GetPeerAddress: %s", SDLNet_GetError());
    }

    threadRecive = SDL_CreateThread(updateCCThread, NULL, this);

}

void ClientConnection::update(){
    
}

int updateCCThread(void* data){
    ClientConnection* self = (ClientConnection*)data;


    while(self->connected){
        Network::recivePacket(self->socket, self);
    }

    return 0;

}

void ClientConnection::preProcessPacket(int r, unsigned char code, unsigned char* data){
    if(r == 0){
        connected = false;
        server->clientDisconnected(this, true);
    }else if(r == -1){
        connected = false;
        server->clientDisconnected(this, false);
    }else{
        server->processPacket(this, code, data);
    }
}
