#ifndef _PADDLE_H_
#define _PADDLE_H_

// #include <SDL.h>

#include "constants.h"
#include "vec2d.h"

class Paddle {
 public:
  /* constructors */
  Paddle();
  Paddle(Vec2d& pos, float v);

  /* update paddle's position according to dt */
  void update(int dt);

  /* members */
  Vec2d position;
  Vec2d size;
  float velocity;
};

#endif /* _PADDLE_H_ */