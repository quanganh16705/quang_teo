#include "header/GameOver.h"
GameOver::GameOver()
{
    quit = false;
    game_over_bg = loadTexture("./img/gameOver.png");
    replay_btn = loadTexture("./img/replay.png");

    SDL_QueryTexture(replay_btn, NULL, NULL, &replay_btn_rect.w, &replay_btn_rect.h);
    replay_btn_rect.x = SCREEN_WIDTH / 2 - replay_btn_rect.w / 2;
    replay_btn_rect.y = SCREEN_HEIGHT / 2 + 64;
    SPEED = DEFAULT_SPEED;
}
bool GameOver::show()
{
    bool isContinue = false;
    SDL_Event event;
    while (!quit&&!isContinue) 
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
            {
                isContinue = true;

                break;
            }
        }
        render();
        SDL_Delay(SPEED);
    }
    return isContinue;
}
void GameOver::render()
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, game_over_bg, NULL, NULL);

    SDL_RenderCopyEx(gRenderer, replay_btn, NULL, &replay_btn_rect, SDL_GetTicks64() % 3600/10, NULL, SDL_FLIP_NONE);

    SDL_RenderPresent(gRenderer);
}
GameOver::~GameOver(){
    SDL_DestroyTexture(game_over_bg);
    SDL_DestroyTexture(replay_btn);
}