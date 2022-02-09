#ifndef _BALL_H_
#define _BALL_H_

// #include <SDL.h>

// #include "constants.h"
#include "vec2d.h"

class Ball {
 public:
  /* Members */
  Vec2d position;
  // SDL_Rect rect{};

  /* Constructor */
  Ball();
  Ball(Vec2d& pos);
  void update(Vec2d& pos);
  // void draw(SDL_Renderer* renderer);
};

#endif /* _BALL_H_ */