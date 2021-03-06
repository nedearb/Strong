//
//  UiTextBox.hpp
//  Strong
//
//  Created by Braeden Atlee on 1/19/16.
//  Copyright © 2016 Braeden Atlee. All rights reserved.
//

#ifndef UiTextBox_hpp
#define UiTextBox_hpp

#include "Menu.hpp"
#include "Image.hpp"

#define ENABLE_LOWERCASE (1 << 0)
#define ENABLE_UPERCASE (1 << 1)
#define ENABLE_NUMEBRS (1 << 2)
#define ENABLE_SPACES (1 << 3)
#define ENABLE_SYMBOLS (1 << 4)

class UiTextBox : public UiObject {
public:

    UiTextBox(int x, int y, string text, function<void(UiTextBox*)> onEnter, function<void(UiTextBox*)> onChange);
    UiTextBox(int x, int y, int w, int h, string text, function<void(UiTextBox*)> onEnter, function<void(UiTextBox*)> onChange);

    virtual ~UiTextBox();

    virtual bool mouseMove(int x, int y);

    virtual bool mouseDown(int x, int y, int button);

    virtual bool keyPressed(SDL_Keysym key);

    virtual bool textInput(string s);

    virtual void render();

    virtual void changeText(string newText, bool force = false);

    virtual void focusChanged();

    unsigned inputMask = ENABLE_LOWERCASE | ENABLE_UPERCASE | ENABLE_NUMEBRS | ENABLE_SPACES | ENABLE_SYMBOLS;

    function<void(UiTextBox*)> onEnter = nullptr;
    function<void(UiTextBox*)> onChange = nullptr;

    bool fitToText = false;
    int padding = 4;
    int widthMin;
    int heightMin;

    bool clickedDown = false;
    bool hover = false;

    string text;
    bool mustUpdateText;
    SDL_Color textColor = {255, 255, 255, 255};
    int textW, textH;

    Image* image = Graphics::imageGui;

    SDL_Rect clipDefault = Graphics::rect(0, 0, 12, 12);
    SDL_Rect clipFocused = Graphics::rect(12, 0, 12, 12);
    SDL_Rect clipDisabled = Graphics::rect(12*2, 0, 12, 12);

    Image* imageText = new Image();
};

#endif /* UiTextBox_hpp */
