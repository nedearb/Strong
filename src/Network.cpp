//
//  Network.cpp
//  Strong
//
//  Created by Braeden Atlee on 1/7/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#include "Network.hpp"

namespace Network{

    void init(){
        if (SDLNet_Init() < 0) {
    		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
    		exit(EXIT_FAILURE);
    	}
    }

    void cleanup(){
    	SDLNet_Quit();
    }

    bool initHost(int port, TCPsocket* socket, IPaddress* ip){
        if (SDLNet_ResolveHost(ip, NULL, port) < 0) {
    		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
            return false;
    	}
        if (!(*socket = SDLNet_TCP_Open(ip))) {
    		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
            return false;
    	}
        return true;
    }

    bool acceptGuest(TCPsocket* host, TCPsocket* client){
        *client = SDLNet_TCP_Accept(*host);
        if(*client){
            return true;
        }else{
            return false;
        }
        return true;
    }

    bool connectToHost(string address, int port, TCPsocket* socket, IPaddress* ip){
        if (SDLNet_ResolveHost(ip, address.c_str(), port) < 0) {
    		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
    		return false;
    	}
    	if (!(*socket = SDLNet_TCP_Open(ip))) {
    		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
    		return false;
    	}
        return true;
    }

    bool sendData(TCPsocket* socket, vector<unsigned char>& data){
        if (SDLNet_TCP_Send(*socket, &data[0], (int)data.size()) < (int)data.size()) {
			fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            return false;
		}
        return true;
    }



    void initPacket(vector<unsigned char>& data, unsigned char code){
        data.push_back(code);
        addDataNumber<PacketSize_t>(data, 0);
    }

    void finishPacket(vector<unsigned char>& data){

        union {
            PacketSize_t n;
            unsigned char b[sizeof(PacketSize_t)];
        } uBytes;

        uBytes.n = (PacketSize_t)(data.size() - sizeof(PacketSize_t) - sizeof(unsigned char));

        for (size_t i = 0; i < sizeof(PacketSize_t); i++) {
            data[sizeof(unsigned char)+i] = uBytes.b[i];
        }
    }

    int reciveData(TCPsocket* socket, unsigned char* data, PacketSize_t dataSize){
        int t = 0;
        bool b;

        do{
            b = false;
            int result = SDLNet_TCP_Recv(*socket, data+t, dataSize-t);
            switch(result){
                case 0:{
                    return 0;
                }
                case -1:{
                    return -1;
                }
                default:{
                    if(result < dataSize){
                        b = true;
                        t += result;
                    }else{
                        return dataSize;
                    }
                    break;
                }
            }
        }while(b);
        return 0;
    }

    void recivePacket(TCPsocket* socket, function<void(int, unsigned char, unsigned char*)> process){

        PacketSize_t s = 1+sizeof(PacketSize_t);
        unsigned char data1[s];
        int r = Network::reciveData(socket, data1, s);
        if(r == 0){
            process(0, 0, nullptr);
        }else if(r == -1){
            process(-1, 0, nullptr);
        }else{
            s = 0;

            for(size_t i = 0; i<sizeof(PacketSize_t); i++){
                s |= data1[i+1] << (8*i);
            }

            if(s > 0){
                unsigned char data2[s];
                int r = Network::reciveData(socket, data2, s);
                if(r == 0){
                    process(0, 0, nullptr);
                }else if(r == -1){
                    process(-1, 0, nullptr);
                }else{
                    process(r, data1[0], data2);
                }
            }else{
                process(r, data1[0], nullptr);
            }
        }
    }





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

    void addDataUChar(vector<unsigned char>& data, unsigned char n){
        data.push_back(n);
    }

    void addDataShortString(vector<unsigned char>& data, string n){

        addDataNumber(data, (unsigned short)n.size());

        for(size_t i=0;i<n.size();i++){
            data.push_back((unsigned char)n[i]);
        }
    }





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


    void readDataUChar(unsigned char* data, size_t& position, unsigned char& n){
        n = data[position];
        position++;
    }

    void readDataShortString(unsigned char* data, size_t& position, string& n){
        n = "";
        unsigned short ss;
        readDataNumber(data, position, ss);
        for(size_t i = 0; i < ss; i++){
            char c = (char)data[position];
            position++;
            n += c;
        }
    }


}
