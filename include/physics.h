#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "ball.h"
#include "paddle.h"

// class Physics {
/* constructor */
// Physics();

/* Collision detection */
bool collideWithPaddle(Ball& ball, Paddle& paddle);
// bool collideWithWall(Ball& ball);
// };

#endif /* _PHYSICS_H_ */