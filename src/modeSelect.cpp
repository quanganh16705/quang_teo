#include "header/modeSelect.h"
ModeSelect::ModeSelect()
{
    quit = false;
    wall = IMG_LoadTexture(gRenderer, "./img/wall.png");
    walless = IMG_LoadTexture(gRenderer, "./img/walless.png");
    select_mode = IMG_LoadTexture(gRenderer, "./img/select_mode.png");

    SDL_QueryTexture(wall, NULL, NULL, &wallRect.w, &wallRect.h);
    SDL_QueryTexture(walless, NULL, NULL, &wallessRect.w, &wallessRect.h);
    SDL_QueryTexture(select_mode, NULL, NULL, &selectRect.w, &selectRect.h);
    // center x
    wallRect.x = SCREEN_WIDTH / 2 - wallRect.w / 2;
    wallRect.y = 280;

    wallessRect.x = SCREEN_WIDTH / 2 - wallessRect.w / 2;
    wallessRect.y = 400;

    selectRect.x = SCREEN_WIDTH / 2 - selectRect.w / 2;
    selectRect.y = 100;
}
bool ModeSelect::show()
{
    bool play = true;

    SDL_Event event;
    bool startGame = false;
    while (play && !startGame)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                play = false;
                break;
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_UP)
                {
                    wallMode = true;
                }
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    wallMode = false;
                }
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    startGame = true;
                }
            }
        }
        render();
        SDL_Delay(SPEED);
    }
    return play;
}
void ModeSelect::render()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);
    if(wallMode){
        SDL_SetTextureAlphaMod(wall, 255);
        SDL_RenderCopy(gRenderer, wall, NULL, &wallRect);
        SDL_SetTextureAlphaMod(walless, 100);
        SDL_RenderCopy(gRenderer, walless, NULL, &wallessRect);
    }else {
        SDL_SetTextureAlphaMod(wall, 100);
        SDL_RenderCopy(gRenderer, wall, NULL, &wallRect);
        SDL_SetTextureAlphaMod(walless, 255);
        SDL_RenderCopy(gRenderer, walless, NULL, &wallessRect);
    }
    if (SDL_GetTicks() % 1000 > 300)
    {
        SDL_RenderCopy(gRenderer, select_mode, NULL, &selectRect);
    }
    SDL_RenderPresent(gRenderer);
}
ModeSelect::~ModeSelect()
{
    SDL_DestroyTexture(wall);
    SDL_DestroyTexture(walless);
    SDL_DestroyTexture(select_mode);
}