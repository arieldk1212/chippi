#include "display/display.h"

// Screen Settings
char *title = "Chippi";
const int WIDTH = 640;
const int HEIGHT = 480;

// Flags for The Screen -> in display.h
extern Uint32 flags;

int main () {

  SDL_Window *window;
  createWindow(&window, title, HEIGHT, WIDTH, flags);

  return 0;
}