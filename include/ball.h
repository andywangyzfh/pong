#ifndef _BALL_H_
#define _BALL_H_

#include <SDL.h>

#include "constants.h"
#include "vec2d.h"

class ball {
 public:
  /* Members */
  vec2d position;
  SDL_Rect rect{};

  /* Constructor */
  ball(vec2d& pos);
  void draw(SDL_Renderer* renderer);
};

#endif /* _BALL_H_ */