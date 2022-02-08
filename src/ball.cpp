#include "ball.h"

ball::ball(vec2d& pos) : position(pos) {
  rect.x = static_cast<int>(pos.x);
  rect.y = static_cast<int>(pos.y);
  rect.w = BALL_WIDTH;
  rect.h = BALL_HEIGHT;
}

void ball::draw(SDL_Renderer* renderer) {
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
  SDL_RenderFillRect(renderer, &rect);
}