#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <deque>

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 680;
const int GRID_SIZE = 34;
const int CELL_SIZE = 20;
const int SNAKE_EYE_SIZE = 5;
const int DEFAULT_SPEED = 120;
extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern int SPEED ;
struct SnakeSegment
{
    int x, y;
};

enum class Direction
{
    None,
    Up,
    Down,
    Left,
    Right
};

const SnakeSegment INIT_HEAD = {SCREEN_WIDTH / CELL_SIZE / 2, SCREEN_HEIGHT / CELL_SIZE / 2};