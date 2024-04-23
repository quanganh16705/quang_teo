#pragma once

#include "Util.h"

class ModeSelect{
public:
    ModeSelect();
    ~ModeSelect();
    bool show();

private:
    void render();
    bool quit;
    SDL_Rect wallRect;
    SDL_Rect wallessRect;
    SDL_Rect selectRect;

    SDL_Texture * wall;
    SDL_Texture * walless;
    SDL_Texture * select_mode;
};