#include "physics.h"

/**
 * Check if the ball collide with the paddle.
 */
bool collideWithPaddle(Ball& ball, Paddle& paddle) {
  float ballLeft = ball.position.x;
  float ballRight = ball.position.x + BALL_WIDTH;
  float ballTop = ball.position.y;
  float ballBottom = ball.position.y + BALL_HEIGHT;

  float paddleLeft = paddle.position.x;
  float paddleRight = paddle.position.x + PADDLE_WIDTH;
  float paddleTop = paddle.position.y;
  float paddleBottom = paddle.position.y + PADDLE_HEIGHT;

  if (ballLeft >= paddleRight || ballRight <= paddleLeft ||
      ballTop >= paddleBottom || ballBottom <= paddleTop)
    return false;

  return true;
}