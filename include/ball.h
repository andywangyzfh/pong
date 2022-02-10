#ifndef _BALL_H_
#define _BALL_H_

// #include <SDL.h>

// #include "constants.h"
#include "vec2d.h"

class Ball {
 public:
  /* Members */
  Vec2d position;
  Vec2d velocity;

  /* Constructor */
  Ball();
  Ball(Vec2d& pos);
  Ball(Vec2d& pos, Vec2d v);
  void update(int dt);
};

#endif /* _BALL_H_ */