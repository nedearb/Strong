//
//  MenuGame.hpp
//  Strong
//
//  Created by Braeden Atlee on 1/19/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#ifndef MenuGame_hpp
#define MenuGame_hpp

#include "Menu.hpp"

class World;
class Unit;

class MenuGame : public Menu{
public:

    MenuGame(Menu* upperMenu);

    virtual ~MenuGame();

    virtual void openMenu();

    virtual void closeMenu();

    virtual bool keyPressed(SDL_Keysym key);

    virtual bool mouseDown(int x, int y, int button);

    virtual bool mouseMove(int x, int y);

    virtual bool mouseUp(int x, int y, int button);

    virtual void update();

    virtual void render();

    int selectInitX = -1;
    int selectInitY = -1;
    int selectX = -1;
    int selectY = -1;

    SDL_Color selectColor = {0, 127, 255, 255};

    vector<Unit*> selectedUnits;

    Menu* upperMenu;
    
};

#endif /* MenuGame_hpp */
