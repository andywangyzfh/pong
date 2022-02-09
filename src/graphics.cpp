#include "graphics.h"

Graphics::Graphics() : renderer(nullptr), window(nullptr){};

Graphics::Graphics(SDL_Renderer* renderer, SDL_Window* window) {
  this->renderer = renderer;
  this->window = window;
}

void Graphics::drawBall(Ball& ball) {
  // TODO: assert renderer here
  SDL_Rect rect;
  rect.x = ball.position.x;
  rect.y = ball.position.y;
  rect.w = BALL_WIDTH;
  rect.w = BALL_HEIGHT;
  SDL_RenderFillRect(renderer, &rect);
}

void Graphics::drawPaddle(Paddle& paddle) {
  // TODO: assert renderer here
  SDL_Rect rect;
  rect.x = paddle.position.x;
  rect.y = paddle.position.y;
  rect.w = PADDLE_WIDTH;
  rect.w = PADDLE_HEIGHT;
  SDL_RenderFillRect(renderer, &rect);
}