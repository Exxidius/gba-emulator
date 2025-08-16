#include <SDL3/SDL.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include <stdio.h>

int main() {
  int scaling_factor = 8;
  int width = 160;
  int height = 144;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("Error: SDL_Init(): %s\n", SDL_GetError());
    return -1;
  }

  SDL_WindowFlags flags = (SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE);
  SDL_Window* window = SDL_CreateWindow("ImGui + SDL3 (software)", 1280, 720, flags);
  if (!window)
  {
    printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer)
  {
    SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  SDL_ShowWindow(window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer3_Init(renderer);

  ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
  bool done = false;

  while (!done)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      ImGui_ImplSDL3_ProcessEvent(&event);
      if (event.type == SDL_EVENT_QUIT)
        done = true;
    }

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello");
    ImGui::Text("ImGui + SDL3 software rendering example");
    ImGui::End();

    ImGui::Render();

    SDL_SetRenderDrawColor(renderer,
        (Uint8)(clear_color.x * 255),
        (Uint8)(clear_color.y * 255),
        (Uint8)(clear_color.z * 255),
        (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
  }

  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
