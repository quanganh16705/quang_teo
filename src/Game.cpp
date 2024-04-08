#include "header/Game.h"

Game::Game()
{
    game_over = false;
    quit = false;
    dir = Direction::None;
    nextDir = Direction::None;
    snake.push_front({INIT_HEAD.x+1, INIT_HEAD.y});
    snake.push_front({INIT_HEAD.x,INIT_HEAD.y});
    generateFood(food);
    food.w = CELL_SIZE;
    food.h = CELL_SIZE;
    eat_fx = Mix_LoadWAV("./audio/eat.wav");
    SPEED = DEFAULT_SPEED;
}
bool Game::isQuit()
{
    return quit;
}
void Game::generateFood(SDL_Rect &food)
{
    bool notDuplicated = true;
    while (true)
    {
        food.x = (rand() % GRID_SIZE);
        food.y = (rand() % GRID_SIZE);
        for (auto &seg : snake)
        {
            if (seg.x == food.x && seg.y == food.y)
            {
                notDuplicated = false;
                break;
            }
        }
        if (notDuplicated)
            break;
    }
    food.x *= CELL_SIZE;
    food.y *= CELL_SIZE;
}
void Game::run()
{
    Uint32 frameStart;
    int frameTime;
    SDL_Event event;
    while (!game_over && !quit)
    {
        frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;

                break;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    if (dir != Direction::Down)
                        nextDir = Direction::Up;
                    break;
                case SDLK_DOWN:
                    if (dir != Direction::Up)
                        nextDir = Direction::Down;
                    break;
                case SDLK_LEFT:
                    if (dir != Direction::Right)
                        nextDir = Direction::Left;
                    break;
                case SDLK_RIGHT:
                    if (dir != Direction::Left)
                        nextDir = Direction::Right;
                    break;
                default:
                    break;
                }
            }
        }
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < SPEED)
        {
            SDL_Delay(SPEED - frameTime);
        }
    }
}

void Game::update()
{
    // enhance snake movespeed
    SPEED = DEFAULT_SPEED - snake.size() / 3;
    dir = nextDir;
    // Move the snake
    SnakeSegment newHead = snake.front();
    switch (dir)
    {
    case Direction::Up:
        newHead.y -= 1;
        break;
    case Direction::Down:
        newHead.y += 1;
        break;
    case Direction::Left:
        newHead.x -= 1;
        break;
    case Direction::Right:
        newHead.x += 1;
        break;
    default:
        return;
        break;
    }

    // Check collision with food
    SDL_Rect head = {
        newHead.x * CELL_SIZE,
        newHead.y * CELL_SIZE,
        CELL_SIZE,
        CELL_SIZE
    };
    if (checkCollision(head, food))
    {
        Mix_PlayChannel( -1, eat_fx, 0 );
        generateFood(food);
    }
    else
    {
        snake.pop_back();
    }

    // Check collision with wall
if (newHead.x < 0)
    newHead.x = GRID_SIZE- 1;
else if (newHead.x >= SCREEN_WIDTH)
    newHead.x = 0;

if (newHead.y < 0)
    newHead.y = GRID_SIZE - 1;
else if (newHead.y >= SCREEN_HEIGHT)
    newHead.y = 0;

    // Check collision with self
    for (auto &seg : snake)
    {
        if (seg.x == newHead.x && seg.y == newHead.y)
        {
            game_over = true;
            return;
        }
    }
    snake.push_front(newHead);
}

void Game::render()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);
    // draw grid
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 20);
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    for (int i = 1; i <= GRID_SIZE; i++)
    {
        SDL_RenderDrawLine(gRenderer, i * CELL_SIZE, 0, i * CELL_SIZE + 1, SCREEN_HEIGHT);
    }
    for (int i = 1; i <= GRID_SIZE; i++)
    {
        SDL_RenderDrawLine(gRenderer, 0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE + 1);
    }

    // Draw snake
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 170);
    for (auto &seg : snake)
    {
        SDL_Rect segment = {seg.x * CELL_SIZE, seg.y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
        SDL_RenderFillRect(gRenderer, &segment);
    }
    // head
    SDL_Rect head = {snake.front().x * CELL_SIZE, snake.front().y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
    SDL_RenderFillRect(gRenderer, &head);
    // eye
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    if (dir == Direction::Down || dir == Direction::Up)
    {
        SDL_Rect eye_h_left = {head.x + head.w / 3 - SNAKE_EYE_SIZE, head.y + head.h / 2, SNAKE_EYE_SIZE, SNAKE_EYE_SIZE};
        SDL_Rect eye_h_right = {head.x + head.w * 2 / 3, head.y + head.h / 2, SNAKE_EYE_SIZE, SNAKE_EYE_SIZE};
        SDL_RenderFillRect(gRenderer, &eye_h_left);
        SDL_RenderFillRect(gRenderer, &eye_h_right);
    }
    else
    {
        SDL_Rect eye_v_up = {head.x + head.w / 2, head.y + head.h / 3 - SNAKE_EYE_SIZE, SNAKE_EYE_SIZE, SNAKE_EYE_SIZE};
        SDL_Rect eye_h_below = {head.x + head.w / 2, head.y + head.h * 2 / 3, SNAKE_EYE_SIZE, SNAKE_EYE_SIZE};
        SDL_RenderFillRect(gRenderer, &eye_v_up);
        SDL_RenderFillRect(gRenderer, &eye_h_below);
    }
    // Draw food
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    if (SDL_GetTicks64() % 1000 > 100)
    {
        SDL_RenderFillRect(gRenderer, &food);
    }

    // Display
    SDL_RenderPresent(gRenderer);
}
Game::~Game()
{
    Mix_FreeChunk(eat_fx);
}