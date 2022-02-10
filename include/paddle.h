#ifndef _PADDLE_H_
#define _PADDLE_H_

// #include <SDL.h>

#include "constants.h"
#include "vec2d.h"

class Paddle {
 public:
  Paddle();
  Paddle(Vec2d& pos, float v);
  void update(float dt);
  // void draw(SDL_Renderer* renderer);

  Vec2d position;

  float velocity;
  // SDL_Rect rect{};
};

#endif /* _PADDLE_H_ */