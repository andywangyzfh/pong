#include "ball.h"

Ball::Ball() { position = Vec2d(); }

Ball::Ball(Vec2d& pos) : position(pos) {
  // rect.x = static_cast<int>(pos.x);
  // rect.y = static_cast<int>(pos.y);
  // rect.w = BALL_WIDTH;
  // rect.h = BALL_HEIGHT;
}

void Ball::update(Vec2d& pos) { position = pos; }

// void Ball::draw(SDL_Renderer* renderer) {
//   rect.x = static_cast<int>(position.x);
//   rect.y = static_cast<int>(position.y);
//   SDL_RenderFillRect(renderer, &rect);
// }