#include "header/MainMenu.h"
MainMenu::MainMenu()
{
    quit = false;
    back_ground = loadTexture("./img/bg.png");
    waiter_text = loadTexture("./img/WaitText.png");
    waiter_text_rect.x = 44;
    waiter_text_rect.y = SCREEN_HEIGHT / 2 + 64;
    SDL_QueryTexture(waiter_text, NULL, NULL, &waiter_text_rect.w, &waiter_text_rect.h);
    SPEED= DEFAULT_SPEED;
}
bool MainMenu::show()
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
                startGame = true;
                break;
            }
        }
        render();
        SDL_Delay(SPEED);
    }
    return play;
}
void MainMenu::render()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, back_ground, NULL, NULL);
    //nhấp nháy
    if (SDL_GetTicks() % 1000 > 300)
    {
        SDL_RenderCopy(gRenderer, waiter_text, NULL, &waiter_text_rect);
    }
    SDL_RenderPresent(gRenderer);
}
MainMenu::~MainMenu(){
    SDL_DestroyTexture(back_ground);
    SDL_DestroyTexture(waiter_text);
}