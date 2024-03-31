#pragma once


#include "Constants.h"

bool initWindow();
void closeWindow();
bool checkCollision( SDL_Rect a, SDL_Rect b );
SDL_Texture* loadTexture(const std::string& path);
