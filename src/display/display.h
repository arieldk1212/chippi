#pragma once
#include <iostream>
#include <SDL2/SDL.h>

#define EXT_WINDOW_ERROR 0

Uint32 flags = SDL_WINDOW_OPENGL;

void createWindow(SDL_Window **window, char *title, const int HEIGHT, const int WIDTH, Uint32 flags) {

  bool quit = false;
  SDL_Event e;

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_DisplayMode current;
  SDL_GetCurrentDisplayMode(0, &current);  

  *window = SDL_CreateWindow("Chippi-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, SDL_RENDERER_ACCELERATED);
  while (!quit) {
    if (*window == NULL) {
      std::cerr << "Window Could Not Be Created - " << SDL_GetError() << "\n";
      exit(EXT_WINDOW_ERROR); };
      
    while (SDL_PollEvent (&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;}}
  }
  SDL_DestroyWindow(*window);
  SDL_Quit();
}