#include "ball.h"

/* Constructors */

Ball::Ball() : position(Vec2d(0, 0)), velocity(Vec2d(0.1, 0)) {}

Ball::Ball(Vec2d& pos) : position(pos), velocity(Vec2d(0.1, 0)) {}

Ball::Ball(Vec2d& pos, Vec2d v) : position(pos), velocity(v) {}

/**
 * Update ball's position according to delta time
 */
void Ball::update(int dt) { position += velocity * dt; }

/**
 * Update ball's direction according after colliding with paddle
 */
void Ball::processCollision(CollisionPoint& cp) {
  if (cp == CollisionPoint::None) return;
  velocity.x *= -1;
  if (cp == CollisionPoint::Upper)
    velocity.y = -0.75 * BALL_VELOCITY;
  else if (cp == CollisionPoint::Lower)
    velocity.y = 0.75 * BALL_VELOCITY;
}