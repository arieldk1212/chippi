#include <iostream>
#include <display.h>
#include <SDL2/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;


int main () {

  SDL_Window *gWindow;
  createWindow(&gWindow, "Chippi", HEIGHT, WIDTH)

  // SDL_Window *window = NULL;
  // SDL_Surface *screenSurface = NULL;
  // SDL_Event e;
  // bool quit = false;

  // if (SDL_Init(SDL_INIT_VIDEO) < 0) {
  //   std::cerr << "SDL Could Not Initialize.\n";
  // } else {
  //   window = SDL_CreateWindow("Chippi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  //   if (window == NULL) {
  //     std::cerr << "Window Could Not Be Created.\n";
  //   } else {
  //     screenSurface = SDL_GetWindowSurface(window);
  //     SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  //     SDL_UpdateWindowSurface(window);
  //     while(quit == false) { 
  //       while(SDL_PollEvent(&e)) {
  //         if (e.type == SDL_QUIT) quit = true;
  //       }
  //     }
  //     SDL_DestroyWindow(window);
  //     SDL_Quit();
  return 0;
}