//
//  Unit.hpp
//  Strong
//
//  Created by Braeden Atlee on 1/19/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#ifndef Unit_hpp
#define Unit_hpp

#include "General.hpp"
#include "Graphics.hpp"
#include "Math.hpp"
#include "Orientation.hpp"

typedef unsigned char Formation;
const Formation formationDefault = 0;
const Formation formationUnformed = 1;

class Unit{
public:

    Unit(General* general);
    ~Unit();

    void writeAllData(vector<unsigned char>& data);
    void readAllData(unsigned char* data, size_t& position);
    Unit(General* general, unsigned char* data, size_t& position);

    void writeUid(vector<unsigned char>& data);
    void readUid(unsigned char* data, size_t& position);

    void writeStatsData(vector<unsigned char>& data);
    void readStatsData(unsigned char* data, size_t& position);

    void writeTargetData(vector<unsigned char>& data);
    void readTargetData(unsigned char* data, size_t& position);

    void writePosData(vector<unsigned char>& data);
    void readPosData(unsigned char* data, size_t& position);

    void update();
    void render();
    void setTargetPos(float nx, float ny);
    void setTargetAngle(float nAngle);
    void teleport(float x, float y);

    float speedMod();


	//Local Only
    General* general;

    Image* image = Graphics::imageGame;

    SDL_Rect clip = Graphics::rect(0, 0, 12, 12);

    bool statsChanged = false;
    bool movingOutOfTheWay = false;



    //Changes Frequently:
    Orientation orientNow = Orientation(0, 0, 0);
    Orientation orientSubTarget = Orientation(0, 0, 0);
    Orientation orientTarget = Orientation(0, 0, 0);

    //Changes Infrequently:
    Formation formation = formationDefault;
    int count = 500; // 0-inf
    float morale = 1; // 0-1
    float attackPotential = 1; // 0-1

    //Mostly constant:
    float baseSpeedMove = 1;
    float baseSpeedRot = TAU/90;
    float width = 12;
    float height = 12;
    float collisionRadius = 6;
    int maxCount = 500;

    UID uid = 0;


    
};

#endif /* Unit_hpp */
