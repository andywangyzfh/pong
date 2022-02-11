#include "ball.h"

/* Constructors */

Ball::Ball() : position(Vec2d(0, 0)), velocity(Vec2d(0, 0)) {}

Ball::Ball(Vec2d& pos) : position(pos), velocity(Vec2d(1, 0)) {}

Ball::Ball(Vec2d& pos, Vec2d v) : position(pos), velocity(v) {}

/**
 * Update ball's position according to delta time
 */
void Ball::update(int dt) { position += velocity * dt; }