#include "paddle.h"

Paddle::Paddle() : position(Vec2d()), velocity(0.0f) {}

Paddle::Paddle(Vec2d& pos, float v) : position(pos), velocity(v) {}

void Paddle::update(float dt) {
  // update position
  position.y += velocity * dt;
  // check if out of boundary
  if (position.y < 0)
    position.y = 0;
  else if (position.y > SCREEN_HEIGHT - PADDLE_HEIGHT)
    position.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
}
