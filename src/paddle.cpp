#include "paddle.h"

/* Constructors */
Paddle::Paddle() : position(Vec2d()), velocity(0.0f) {
  size = Vec2d(PADDLE_WIDTH, PADDLE_HEIGHT);
}

Paddle::Paddle(Vec2d& pos, float v) : position(pos), velocity(v) {
  size = Vec2d(PADDLE_WIDTH, PADDLE_HEIGHT);
}

/**
 * Update the paddle's position according to dt. If the position is out of
 * boundary, set it back to boundary point.
 */
void Paddle::update(int dt) {
  // update position
  position.y += velocity * dt;
  // check if out of boundary
  if (position.y < 0)
    position.y = 0;
  else if (position.y > SCREEN_HEIGHT - size.y)
    position.y = SCREEN_HEIGHT - size.y;
}
