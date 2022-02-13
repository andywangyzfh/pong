#include "physics.h"

/**
 * Check if the ball collide with the paddle.
 */
CollisionPoint collideWithPaddle(Ball& ball, Paddle& paddle) {
  CollisionPoint cp;

  // parameters
  float ballLeft = ball.position.x;
  float ballRight = ball.position.x + BALL_WIDTH;
  float ballTop = ball.position.y;
  float ballBottom = ball.position.y + BALL_HEIGHT;

  float paddleLeft = paddle.position.x;
  float paddleRight = paddle.position.x + paddle.size.x;
  float paddleTop = paddle.position.y;
  float paddleBottom = paddle.position.y + paddle.size.y;

  // No collision
  if (ballLeft >= paddleRight || ballRight <= paddleLeft ||
      ballTop >= paddleBottom || ballBottom <= paddleTop)
    return cp;

  // Check collision type
  float upperPaddle = paddleBottom - (PADDLE_HEIGHT / 3.0f * 2);
  float middlePaddle = paddleBottom - (PADDLE_HEIGHT / 3.0f);
  if (ballBottom < upperPaddle) {
    cp.type = CollisionType::Upper;
  } else if ((ballBottom > upperPaddle) && (ballBottom < middlePaddle)) {
    cp.type = CollisionType::Middle;
  } else {
    cp.type = CollisionType::Lower;
  }

  // Compute deviation
  if (ball.velocity.x > 0) {
    cp.deviation.x = paddleLeft - ballRight;
  } else {
    cp.deviation.x = paddleRight - ballLeft;
  }

  return cp;
}

/**
 * Check if the ball collide with the wall.
 */
CollisionPoint collideWithWall(Ball& ball) {
  CollisionPoint cp;

  float ballLeft = ball.position.x;
  float ballRight = ball.position.x + BALL_WIDTH;
  float ballTop = ball.position.y;
  float ballBottom = ball.position.y + BALL_HEIGHT;

  if (ballLeft < 0) {
    cp.type = CollisionType::Left;
  } else if (ballRight >= SCREEN_WIDTH) {
    cp.type = CollisionType::Right;
  } else if (ballTop < 0) {
    cp.type = CollisionType::Wall;
    cp.deviation.y = -ballTop;
  } else if (ballBottom >= SCREEN_HEIGHT) {
    cp.type = CollisionType::Wall;
    cp.deviation.y = SCREEN_HEIGHT - ballBottom;
  }
  return cp;
}