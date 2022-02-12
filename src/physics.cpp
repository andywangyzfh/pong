#include "physics.h"

/**
 * Check if the ball collide with the paddle.
 */
CollisionPoint collideWithPaddle(Ball& ball, Paddle& paddle) {
  // final result
  CollisionPoint cp = CollisionPoint::None;
  float ballLeft = ball.position.x;
  float ballRight = ball.position.x + BALL_WIDTH;
  float ballTop = ball.position.y;
  float ballBottom = ball.position.y + BALL_HEIGHT;

  float paddleLeft = paddle.position.x;
  float paddleRight = paddle.position.x + PADDLE_WIDTH;
  float paddleTop = paddle.position.y;
  float paddleBottom = paddle.position.y + PADDLE_HEIGHT;

  // No collision
  if (ballLeft >= paddleRight || ballRight <= paddleLeft ||
      ballTop >= paddleBottom || ballBottom <= paddleTop)
    return cp;

  // Check collision point
  float upperPaddle = paddleBottom - (PADDLE_HEIGHT / 3.0f * 2);
  float middlePaddle = paddleBottom - (PADDLE_HEIGHT / 3.0f);
  if (ballBottom < upperPaddle) {
    cp = CollisionPoint::Upper;
  } else if ((ballBottom > upperPaddle) && (ballBottom < middlePaddle)) {
    cp = CollisionPoint::Middle;
  } else {
    cp = CollisionPoint::Lower;
  }

  return cp;
}