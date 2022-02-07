// Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

void csci437_error(const std::string& msg) {
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

int main(int argc, char** argv) {
  /*** Initialization ***/

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) csci437_error("SDL could not initialize!");

  // Create window
  SDL_Window* window = SDL_CreateWindow(
      "CSCI-437 Skeleton", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) csci437_error("Window could not be created!");

  // Small delay to allow the system to create the window.
  SDL_Delay(100);

  // Get window surface
  SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
  if (screenSurface == NULL) csci437_error("Unable to get window surface!");

  // Make the surface blue
  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0, 0, 255));

  // Update the surface
  SDL_UpdateWindowSurface(window);

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
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_q) running = false;
        if (e.key.keysym.sym == SDLK_r)
          SDL_FillRect(screenSurface, NULL,
                       SDL_MapRGB(screenSurface->format, 255, 0, 0));
        if (e.key.keysym.sym == SDLK_g)
          SDL_FillRect(screenSurface, NULL,
                       SDL_MapRGB(screenSurface->format, 0, 255, 0));
        if (e.key.keysym.sym == SDLK_b)
          SDL_FillRect(screenSurface, NULL,
                       SDL_MapRGB(screenSurface->format, 0, 0, 255));
      }

      // Update the surface
      SDL_UpdateWindowSurface(window);
    }
  }

  /*** Clean Up ***/

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  // Done.
  return 0;
}
