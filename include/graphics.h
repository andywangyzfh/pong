#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL.h>

#include "ball.h"
#include "constants.h"
#include "paddle.h"

class Graphics {
 public:
  /* constructor */
  Graphics();
  Graphics(SDL_Renderer* renderer, SDL_Window* window);

  /* Draw actor */
  void drawBall(Ball& ball);
  void drawPaddle(Paddle& paddle);

 private:
  SDL_Renderer* renderer;
  SDL_Window* window;
};

#endif /* _GRAPHICS_H_ */