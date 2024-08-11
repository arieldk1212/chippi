#include "imgui.h"
#include "display/sdl.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"

// Screen Settings
const int WIDTH = 500;
const int HEIGHT = 480;

// Flags for The Screen -> in display.h
extern Uint32 flags;

int main(){

  // SDL Basic Setup 
  SDL_Window *window;
  createWindow(&window, WIDTH, HEIGHT, flags);
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1); //vsync - on

  // // ImGui Basic Setup
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL2_Init();

  // Main Loop
  bool done = false;
  while(!done) {

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      ImGui_ImplSDL2_ProcessEvent(&e);
      if (e.type == SDL_QUIT)
        done = true;
      if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE && 
          e.window.windowID == SDL_GetWindowID(window))
        done = true;
    }
    

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
  }

  // ImGui Cleaning
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  // SDL Cleaning
  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}