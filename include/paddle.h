#ifndef _PADDLE_H_
#define _PADDLE_H_

#include <SDL.h>

#include "constants.h"
#include "vec2d.h"

class paddle {
 public:
  paddle(vec2d& pos);
  void draw(SDL_Renderer* renderer);

  vec2d position;
  SDL_Rect rect{};
};

#endif /* _PADDLE_H_ */