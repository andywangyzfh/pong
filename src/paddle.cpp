#include "paddle.h"

paddle::paddle(vec2d& pos) : position(pos) {
  rect.x = static_cast<int>(pos.x);
  rect.y = static_cast<int>(pos.y);
  rect.w = PADDLE_WIDTH;
  rect.h = PADDLE_HEIGHT;
}

void paddle::draw(SDL_Renderer* renderer) {
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
  SDL_RenderFillRect(renderer, &rect);
}