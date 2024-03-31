#pragma once

#include "Util.h"

class MainMenu{
public:
    MainMenu();
    ~MainMenu();
    bool show();

private:
    void render();
    bool quit;
    SDL_Texture * back_ground ;
    SDL_Texture * waiter_text ;
    SDL_Rect waiter_text_rect ;
};