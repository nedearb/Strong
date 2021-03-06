//
//  Network.hpp
//  Strong
//
//  Created by Braeden Atlee on 1/7/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#ifndef Network_hpp
#define Network_hpp

#include "Global.hpp"
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_thread.h>


//To client from server:
#define PACKET_TC_REQUEST_CLIENT_INFO 0x0
#define PACKET_TC_ALL_WORLD_DATA 0x1
#define PACKET_TC_NEW_GENERAL 0x2
#define PACKET_TC_NEW_UNIT 0x3
#define PACKET_TC_UNIT_TARGET_SET 0x4
#define PACKET_TC_UNIT_TARGET_REACHED 0x5
#define PACKET_TC_YOUR_NEW_GENERAL 0x6
#define PACKET_TC_UNIT_REMOVE 0x7
#define PACKET_TC_UNIT_STATS_UPDATE 0x8

//To server from client:
#define PACKET_TS_CLIENT_INFO 0x0
#define PACKET_TS_REQUEST_ALL_WORLD_DATA 0x1

#define PACKET_TS_NEW_UNIT 0x3
#define PACKET_TS_UNIT_TARGET_SET 0x4
#define PACKET_TS_UNIT_TARGET_REACHED 0x5

#define PACKET_TS_UNIT_REMOVE 0x7
#define PACKET_TS_UNIT_STATS_UPDATE 0x8



typedef unsigned short PacketSize_t;

namespace Network{

    struct CanPreProcessPacket{
        virtual void preProcessPacket(int r, unsigned char code, unsigned char* data);
    };

    void init();
    void cleanup();

    bool initHost(int port, TCPsocket* socket, IPaddress* ip);
    bool acceptGuest(TCPsocket* host, TCPsocket* client);

    bool connectToHost(string address, int port, TCPsocket* socket, IPaddress* ip);

    bool sendData(TCPsocket* socket, vector<unsigned char>& data);

    void initPacket(vector<unsigned char>& data, unsigned char code);
    void finishPacket(vector<unsigned char>& data);

    int reciveData(TCPsocket* socket, unsigned char* data, PacketSize_t dataSize);
    void recivePacket(TCPsocket* socket, CanPreProcessPacket* process);


    template<typename T>
    void addDataNumber(vector<unsigned char>& data, T n){
        union {
            T n;
            unsigned char b[sizeof(T)];
        } uBytes;

        uBytes.n = n;
        for (size_t i = 0; i < sizeof(T); i++) {
            data.push_back((unsigned char) (uBytes.b[i] & 0xFF));
        }
    }
    void addDataUChar(vector<unsigned char>& data, unsigned char n);
    void addDataShortString(vector<unsigned char>& data, string n);


    template<typename T>
    void readDataNumber(unsigned char* data, size_t& position, T& n){
        union {
            T n;
            unsigned char b[sizeof(T)];
        } uBytes;

        for (size_t i = 0; i<sizeof(T); i++) {
            uBytes.b[i] = data[position];
            position++;
        }
        n = uBytes.n;
    }
    void readDataUChar(unsigned char* data, size_t& position, unsigned char& n);
    void readDataShortString(unsigned char* data, size_t& position, string& n);

}

#endif
