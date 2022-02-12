#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "ball.h"
#include "collision.h"
#include "constants.h"
#include "paddle.h"

/* Collision detection */
CollisionPoint collideWithPaddle(Ball& ball, Paddle& paddle);

CollisionPoint collideWithWall(Ball& ball);

#endif /* _PHYSICS_H_ */