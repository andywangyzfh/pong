#include <SDL.h>
#include <stdio.h>

#include <iostream>

#include "constants.h"
#include "graphics.h"

void raise_error(const std::string& msg) {
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

int main(int argc, char** argv) {
  /*** Initialization ***/

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) raise_error("SDL could not initialize!");

  // Create window
  SDL_Window* window =
      SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) raise_error("Window could not be created!");

  // Small delay to allow the system to create the window.
  SDL_Delay(100);

  // Create renderer
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) raise_error("Unable to create renderer!");

  Graphics* graphics = new Graphics(renderer, window);
  graphics->initMap();

  /*** Main Loop ***/

  bool running = true;
  SDL_Event e;
  // While application is running
  while (running) {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) running = false;

      // User presses a key
      else if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        }
      }

      /*
       * TODO: rendering
       */
    }
  }

  /*** Clean Up ***/

  // Destroy renderer
  SDL_DestroyRenderer(renderer);

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  // Done.
  return 0;
}