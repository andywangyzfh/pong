#include "graphics.h"

Graphics::Graphics() : renderer(nullptr), window(nullptr){};

Graphics::Graphics(SDL_Renderer* renderer, SDL_Window* window) {
  this->renderer = renderer;
  this->window = window;
}

void Graphics::drawBall(Ball& ball) {
  // Assert renderer exists
  assert(renderer);
  // Draw rectangle
  SDL_Rect rect;
  rect.x = ball.position.x;
  rect.y = ball.position.y;
  rect.w = BALL_WIDTH;
  rect.w = BALL_HEIGHT;
  SDL_RenderFillRect(renderer, &rect);
}

void Graphics::drawPaddle(Paddle& paddle) {
  // Assert renderer exists
  assert(renderer);
  // Draw rectangle
  SDL_Rect rect;
  rect.x = paddle.position.x;
  rect.y = paddle.position.y;
  rect.w = PADDLE_WIDTH;
  rect.w = PADDLE_HEIGHT;
  SDL_RenderFillRect(renderer, &rect);
}

void Graphics::initMap() {
  // Assert renderer exists
  assert(renderer);

  // Clear the window to black
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Draw net
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (int y = 0; y < SCREEN_HEIGHT; y += 4) {
    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, y);
  }
  SDL_RenderPresent(renderer);
}