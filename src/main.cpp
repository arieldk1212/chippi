#include "display/sdl.h"

// Screen Settings
char *title = "Chippi";
const int WIDTH = 500;
const int HEIGHT = 480;
// Flags for The Screen -> in display.h
extern Uint32 flags;

int main () {

  SDL_Window *window;
  createWindow(&window, title, HEIGHT, WIDTH, flags);





  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}