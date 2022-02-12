#include "ball.h"

/* Constructors */

Ball::Ball() : position(Vec2d(0, 0)), velocity(Vec2d(0.3, 0)) {}

Ball::Ball(Vec2d& pos) : position(pos), velocity(Vec2d(0.3, 0)) {}

Ball::Ball(Vec2d& pos, Vec2d v) : position(pos), velocity(v) {}

/**
 * Update ball's position according to delta time
 */
void Ball::update(int dt) { position += velocity * dt; }

/**
 * Update ball's direction according after colliding with paddle
 */
void Ball::processCollision(CollisionPoint& cp) {
  // Process deviation
  position += cp.deviation;

  // Hit nothing
  if (cp.type == CollisionType::None) return;
  // Hit upper part of paddle
  if (cp.type == CollisionType::Upper) {
    velocity.x *= -1;
    velocity.y = -0.75 * BALL_VELOCITY;
    std::cout << "hit upper paddle" << std::endl;
  }
  // Hit lower part of paddle
  else if (cp.type == CollisionType::Lower) {
    velocity.x *= -1;
    velocity.y = 0.75 * BALL_VELOCITY;
    std::cout << "hit lower paddle" << std::endl;
  }
  // Hit Middle part of paddle
  else if (cp.type == CollisionType::Middle) {
    velocity.x *= -1;
    std::cout << "hit middle paddle" << std::endl;
  }
  // Hit upper wall or lower wall
  else if (cp.type == CollisionType::Wall) {
    velocity.y *= -1;
    std::cout << "hit wall" << std::endl;
  }
  // Hit left wall or right wall. Someone scored, so reset position and speed.
  else if (cp.type == CollisionType::Left || cp.type == CollisionType::Right) {
    position = Vec2d(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    velocity.x = BALL_VELOCITY;
    velocity.y = BALL_VELOCITY;
    std::cout << "scored" << std::endl;
  }
}