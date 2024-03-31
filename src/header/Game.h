#pragma once
#include "Util.h"

class Game
{
public:
    Game();
    ~Game();
    void run();
    bool isQuit();
private:
    void update();
    void render();
    void generateFood(SDL_Rect&food);
    std::deque<SnakeSegment> snake;
    SDL_Rect food;
    Direction dir;
    Direction nextDir;
    bool game_over;
    bool quit;
    Mix_Chunk* eat_fx;
};
