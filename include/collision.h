/**
 *  Data structures for collision detection
 */
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "vec2d.h"

// Collision point
enum CollisionType { None, Upper, Middle, Lower, Wall, Left, Right };

struct CollisionPoint {
  CollisionType type = None;
  Vec2d deviation = Vec2d(0, 0);
};

#endif /* _COLLISION_H_ */