#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <assert.h>
#include <stdio.h>

#include <iostream>
#include <string>

#include "ball.h"
#include "constants.h"
#include "paddle.h"
#include "score.h"

class Graphics {
 public:
  /* constructor */
  Graphics();
  Graphics(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);

  // /* destructor */
  // ~Graphics();

  /* Draw actor */
  void drawBall(Ball& ball);
  void drawPaddle(Paddle& paddle);

  /* Render map */
  void initMap();

  /* Update Score */
  void updateScore(Score& score);

 private:
  /* SDL utils */
  SDL_Renderer* renderer;
  SDL_Window* window;
  TTF_Font* font;

  /* score board */
  SDL_Surface* playerText;
  SDL_Surface* aiText;
  SDL_Texture* playerTexture;
  SDL_Texture* aiTexture;
  SDL_Rect playerDst;
  SDL_Rect aiDst;
};

#endif /* _GRAPHICS_H_ */