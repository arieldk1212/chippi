#include "imgui.h"
#include "chip8/base.h"
#include "display/sdl.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"

// Screen Settings
const int WIDTH = 500;
const int HEIGHT = 480;

// Flags for The Screen -> in display.h
extern Uint32 flags;

int main(int argc, char *argv[]){

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

  int cycle_delay = std::stoi(argv[2]);
  const char* rom_filename = argv[3];
  Chip8 chip8;
  chip8.load_rom(rom_filename);

  int video_pitch = sizeof(chip8.display) * DISPLAY_WIDTH;

  auto last_cycle_time = std::chrono::high_resolution_clock::now();

  // Main Loop
  bool done = false;
  while(!done) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      ImGui_ImplSDL2_ProcessEvent(&e);
      switch (e.type) {
        case SDL_QUIT: {
          done = true;
        } break;
        case SDL_KEYDOWN: {
          switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
						{
							done = true;
						} break;

						case SDLK_x:
						{
							chip8.key_pad[0] = 1;
						} break;

						case SDLK_1:
						{
							chip8.key_pad[1] = 1;
						} break;

						case SDLK_2:
						{
							chip8.key_pad[2] = 1;
						} break;

						case SDLK_3:
						{
							chip8.key_pad[3] = 1;
						} break;

						case SDLK_q:
						{
							chip8.key_pad[4] = 1;
						} break;

						case SDLK_w:
						{
							chip8.key_pad[5] = 1;
						} break;

						case SDLK_e:
						{
							chip8.key_pad[6] = 1;
						} break;

						case SDLK_a:
						{
							chip8.key_pad[7] = 1;
						} break;

						case SDLK_s:
						{
							chip8.key_pad[8] = 1;
						} break;

						case SDLK_d:
						{
							chip8.key_pad[9] = 1;
						} break;

						case SDLK_z:
						{
							chip8.key_pad[0xA] = 1;
						} break;

						case SDLK_c:
						{
							chip8.key_pad[0xB] = 1;
						} break;

						case SDLK_4:
						{
							chip8.key_pad[0xC] = 1;
						} break;

						case SDLK_r:
						{
							chip8.key_pad[0xD] = 1;
						} break;

						case SDLK_f:
						{
							chip8.key_pad[0xE] = 1;
						} break;

						case SDLK_v:
						{
							chip8.key_pad[0xF] = 1;
						} break;
          }
        } break;
        case SDL_KEYUP: {
          switch (e.key.keysym.sym) {
            case SDLK_x:
						{
							chip8.key_pad[0] = 0;
						} break;

						case SDLK_1:
						{
							chip8.key_pad[1] = 0;
						} break;

						case SDLK_2:
						{
							chip8.key_pad[2] = 0;
						} break;

						case SDLK_3:
						{
							chip8.key_pad[3] = 0;
						} break;

						case SDLK_q:
						{
							chip8.key_pad[4] = 0;
						} break;

						case SDLK_w:
						{
							chip8.key_pad[5] = 0;
						} break;

						case SDLK_e:
						{
							chip8.key_pad[6] = 0;
						} break;

						case SDLK_a:
						{
							chip8.key_pad[7] = 0;
						} break;

						case SDLK_s:
						{
							chip8.key_pad[8] = 0;
						} break;

						case SDLK_d:
						{
							chip8.key_pad[9] = 0;
						} break;

						case SDLK_z:
						{
							chip8.key_pad[0xA] = 0;
						} break;

						case SDLK_c:
						{
							chip8.key_pad[0xB] = 0;
						} break;

						case SDLK_4:
						{
							chip8.key_pad[0xC] = 0;
						} break;

						case SDLK_r:
						{
							chip8.key_pad[0xD] = 0;
						} break;

						case SDLK_f:
						{
							chip8.key_pad[0xE] = 0;
						} break;

						case SDLK_v:
						{
							chip8.key_pad[0xF] = 0;
						} break;
          }
        } break;
      }
    }
    
    auto current_time = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(current_time - last_cycle_time).count();

    if (dt > cycle_delay) {
      last_cycle_time = current_time;
      chip8.cycle();
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