#include <SDL.h>
#include <stdio.h>

#include <iostream>

#include "constants.h"
#include "graphics.h"
#include "physics.h"

void raise_error(const std::string& msg) {
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

void raise_ttf_error(const std::string& msg) {
  std::cerr << msg << " (" << TTF_GetError() << ")" << std::endl;
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

  // Init TTF
  if (TTF_Init() < 0) raise_ttf_error("Unable to initialize TTF!");

  // Small delay to allow the system to create the window.
  SDL_Delay(100);

  // Create renderer
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) raise_error("Unable to create renderer!");

  // Load font
  TTF_Font* font = TTF_OpenFont("../resource/Arial.ttf", 50);
  if (font == NULL) raise_error("Unable to open font!");

  // Initialize map
  Graphics* graphics = new Graphics(renderer, window, font);
  graphics->initMap();

  // Draw ball
  Vec2d center(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
  Ball ball(center);
  graphics->drawBall(ball);

  // Draw paddle
  Vec2d aiPos(40, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
  Vec2d playerPos(SCREEN_WIDTH - 40, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
  Paddle aiPaddle(aiPos, 0.0f);
  Paddle playerPaddle(playerPos, 0.0f);
  graphics->drawPaddle(aiPaddle);
  graphics->drawPaddle(playerPaddle);

  // Draw score
  Score score;
  graphics->updateScore(score);

  // Render all
  SDL_RenderPresent(renderer);

  int dt = 0;

  /*** Main Loop ***/

  bool running = true;
  SDL_Event e;
  // While application is running
  while (running) {
    // Get start time
    auto start = SDL_GetTicks64();

    bool paddleDown = false, paddleUp = false;

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) running = false;
      // User presses a key
      // TODO: update key press events to key states
      else if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        } else if (e.key.keysym.sym == SDLK_LEFT) {
          paddleDown = true;
        } else if (e.key.keysym.sym == SDLK_RIGHT) {
          paddleUp = true;
        }
      } else if (e.type == SDL_KEYUP) {
        if (e.key.keysym.sym == SDLK_LEFT) {
          paddleDown = false;
        } else if (e.key.keysym.sym == SDLK_LEFT) {
          paddleUp = false;
        }
      }
    }
    // Update paddle speed according to the direction
    if (paddleUp) {
      playerPaddle.velocity = -PADDLE_VELOCITY;
    } else if (paddleDown) {
      playerPaddle.velocity = PADDLE_VELOCITY;
    } else {
      playerPaddle.velocity = 0.0f;
    }

    playerPaddle.update(dt);
    ball.update(dt);

    // Check collision
    if (collideWithPaddle(ball, playerPaddle) ||
        collideWithPaddle(ball, aiPaddle)) {
      ball.velocity.x *= -1;
    }

    // Render current frame
    // Clear the window to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set the draw color to be white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    graphics->initMap();
    graphics->drawBall(ball);
    graphics->drawPaddle(aiPaddle);
    graphics->drawPaddle(playerPaddle);
    SDL_RenderPresent(renderer);

    dt = SDL_GetTicks64() - start;
  }

  /*** Clean Up ***/

  // Destroy renderer
  SDL_DestroyRenderer(renderer);

  // Destroy window
  SDL_DestroyWindow(window);

  // Destroy font
  TTF_CloseFont(font);
  TTF_Quit();

  // Quit SDL subsystems
  SDL_Quit();

  // Done.
  return 0;
}