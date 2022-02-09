#include "paddle.h"

Paddle::Paddle() : position(Vec2d()) {}

Paddle::Paddle(Vec2d& pos) : position(pos) {
  // rect.x = static_cast<int>(pos.x);
  // rect.y = static_cast<int>(pos.y);
  // rect.w = PADDLE_WIDTH;
  // rect.h = PADDLE_HEIGHT;
}

// void Paddle::draw(SDL_Renderer* renderer) {
//   rect.x = static_cast<int>(position.x);
//   rect.y = static_cast<int>(position.y);
// }