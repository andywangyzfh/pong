#include "ball.h"

/* Constructors */

Ball::Ball() {
  // Start at center of the screen
  position = Vec2d(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
  // generate random starting direction;
  float a = this->getRandomFloat(-1.0f, 1.0f);
  float b = this->getRandomFloat(-1.0f, 1.0f);
  if (abs(a) > abs(b)) {
    velocity.x = a;
    velocity.y = b;
  } else {
    velocity.x = b;
    velocity.y = a;
  }
  velocity.normalize();
  velocity *= BALL_VELOCITY;
}

Ball::Ball(Vec2d& pos) : position(pos) {
  // generate random starting direction;
  float a = this->getRandomFloat(-1.0f, 1.0f);
  float b = this->getRandomFloat(-1.0f, 1.0f);
  if (abs(a) > abs(b)) {
    velocity.x = a;
    velocity.y = b;
  } else {
    velocity.x = b;
    velocity.y = a;
  }
  velocity.normalize();
  velocity *= BALL_VELOCITY;
}

Ball::Ball(Vec2d& pos, Vec2d v) : position(pos), velocity(v) {}

/**
 * Private helper method to generate random float between lo and hi.
 */
float Ball::getRandomFloat(float lo, float hi) {
  return lo + static_cast<float>(rand()) /
                  (static_cast<float>(RAND_MAX / (hi - lo)));
}

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
    velocity.y = -abs(velocity.x);
    velocity.y += this->getRandomFloat(-0.15, 0.15);
    velocity.normalize();
    velocity *= BALL_VELOCITY;
    // std::cout << "hit upper paddle" << std::endl;
  }
  // Hit lower part of paddle
  else if (cp.type == CollisionType::Lower) {
    velocity.x *= -1;
    // velocity.y = 0.75 * BALL_VELOCITY;
    velocity.y = abs(velocity.x);
    velocity.y += this->getRandomFloat(-0.15, 0.15);
    velocity.normalize();
    velocity *= BALL_VELOCITY;
    // std::cout << "hit lower paddle" << std::endl;
  }
  // Hit Middle part of paddle
  else if (cp.type == CollisionType::Middle) {
    velocity.x *= -1;
    velocity.y += this->getRandomFloat(-0.15, 0.15);
    velocity.normalize();
    velocity *= BALL_VELOCITY;
    // std::cout << "hit middle paddle" << std::endl;
  }
  // Hit upper wall or lower wall
  else if (cp.type == CollisionType::Wall) {
    velocity.y *= -1;
    // std::cout << "hit wall" << std::endl;
  }
  // Hit left wall or right wall. Someone scored, so reset position and speed.
  else if (cp.type == CollisionType::Left || cp.type == CollisionType::Right) {
    position = Vec2d(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    // generate random starting direction;
    float a = this->getRandomFloat(-1.0f, 1.0f);
    float b = this->getRandomFloat(-1.0f, 1.0f);
    if (abs(a) > abs(b)) {
      velocity.x = a;
      velocity.y = b;
    } else {
      velocity.x = b;
      velocity.y = a;
    }
    velocity.normalize();
    velocity *= BALL_VELOCITY;
    // std::cout << "scored" << std::endl;
  }
}