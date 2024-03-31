#pragma once
#include "MainMenu.h"
class GameOver{
public:
    GameOver();
    ~GameOver();
    bool show();

private:
    void render();
    bool quit;
    SDL_Texture * game_over_bg ;
    SDL_Texture * replay_btn ;
    SDL_Rect replay_btn_rect;
    
};