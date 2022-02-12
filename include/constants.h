#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "vec2d.h"

// Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

// Ball size constants
const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;
const float BALL_VELOCITY = 0.75f;

// Paddle constants
const int PADDLE_WIDTH = 15;
const int PADDLE_HEIGHT = 50;
const float PADDLE_VELOCITY = 0.5f;

// Collision point
enum CollisionPoint { None, Upper, Middle, Lower };

#endif /* _CONSTANTS_H_ */