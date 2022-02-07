// Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

void csci437_error(const std::string& msg) {
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

void csci437_img_error(const std::string& msg) {
  std::cerr << msg << " (" << IMG_GetError() << ")" << std::endl;
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

  // Init Bitmap loading
  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
    csci437_img_error("SDL could not initialize bitmap loaders!");

  // Small delay to allow the system to create the window.
  SDL_Delay(100);

  // Create renderer
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) csci437_error("Unable to create renderer!");

  // Load bitmap
  SDL_Surface* image = IMG_Load("../resource/bitmap.png");
  if (image == NULL) csci437_img_error("Could not image!");

  // convert to texture
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL) csci437_error("Could not create texture from surface!");

  // delete image
  SDL_FreeSurface(image);
  image = NULL;

  bool red = true, green = true, blue = true;
  float angle = 0;

  SDL_Rect dst = {(SCREEN_WIDTH - 256) / 2, (SCREEN_HEIGHT - 256) / 2, 256,
                  256};
  SDL_Point rot = {128, 128};

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
        if (e.key.keysym.sym == SDLK_r) red = !red;
        if (e.key.keysym.sym == SDLK_g) green = !green;
        if (e.key.keysym.sym == SDLK_b) blue = !blue;
        if (e.key.keysym.sym == SDLK_z) angle -= 10;
        if (e.key.keysym.sym == SDLK_x) angle += 10;
      }

      // render
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      SDL_SetTextureColorMod(texture, red * 255, green * 255, blue * 255);
      SDL_RenderCopyEx(renderer, texture, NULL, &dst, angle, &rot,
                       SDL_FLIP_NONE);
      SDL_RenderPresent(renderer);
    }
  }

  /*** Clean Up ***/

  // Destroy texture
  SDL_DestroyTexture(texture);

  // Destroy renderer
  SDL_DestroyRenderer(renderer);

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();

  // Done.
  return 0;
}
