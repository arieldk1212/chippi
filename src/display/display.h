#pragma once
#include <SDL2/SDL.h>

void createWindow(SDL_WINDOW **window, char title[10], H, W) {
  *gWindow = SDL_CreateWindow("Chippi-8",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              H, W,
                              SDL_WINDOW_SHOWN);
}
