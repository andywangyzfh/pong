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
  Graphics(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font,
           TTF_Font* titleFont, TTF_Font* smallFont);

  /* destructor */
  ~Graphics();

  /* Draw actor */
  void drawBall(Ball& ball);
  void drawPaddle(Paddle& paddle);

  /* Render map */
  void initMap();

  /* Update Score */
  void updateScore(Score& score);

  /* Draw winning/losing page */
  void displayResult(int winner);

  /* Draw paused message */
  void displayPause();

  /* Display starting page */
  void displayStartingPage();

 private:
  /* SDL utils */
  SDL_Renderer* renderer;
  SDL_Window* window;
  TTF_Font* font;
  TTF_Font* titleFont;
  TTF_Font* smallFont;

  /* score board */
  SDL_Surface* playerText;
  SDL_Surface* aiText;
  SDL_Surface* resultText;
  SDL_Surface* instruction;
  SDL_Surface* text;
  SDL_Surface* title;
  SDL_Surface* description;
  SDL_Texture* texture;
  SDL_Texture* playerTexture;
  SDL_Texture* aiTexture;
  SDL_Texture* resultTexture;
  SDL_Texture* instructionTexture;
  SDL_Texture* titleTexture;
  SDL_Texture* descriptionTexture;
  SDL_Rect playerDst;
  SDL_Rect aiDst;
};

#endif /* _GRAPHICS_H_ */