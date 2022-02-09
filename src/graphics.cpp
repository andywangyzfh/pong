#include "graphics.h"

// /**
//  * Raise error
//  */
// void raise_error(const std::string& msg) {
//   std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
//   exit(0);
// }

// void raise_ttf_error(const std::string& msg) {
//   std::cerr << msg << " (" << TTF_GetError() << ")" << std::endl;
//   exit(0);
// }

/* constructors */
Graphics::Graphics() : renderer(nullptr), window(nullptr), font(nullptr){};

Graphics::Graphics(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font) {
  this->renderer = renderer;
  this->window = window;
  this->font = font;
}

// /**
//  * Destructor
//  */
// ~Graphics() {
//   SDL_FreeSurface(playerText);
//   SDL_FreeSurface(aiText);
//   SDL_DestroyTexture(playerTexture);
//   SDL_DestroyTexture(aiTexture);
// }

/*
 * Draw ball on the map.
 */
void Graphics::drawBall(Ball& ball) {
  // Assert renderer exists
  assert(renderer);
  // Draw rectangle
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect rect;
  rect.x = static_cast<int>(ball.position.x);
  rect.y = static_cast<int>(ball.position.y);
  rect.w = BALL_WIDTH;
  rect.h = BALL_HEIGHT;
  SDL_RenderFillRect(renderer, &rect);
}

/**
 * Draw paddle on the map
 */
void Graphics::drawPaddle(Paddle& paddle) {
  // Assert renderer exists
  assert(renderer);
  // Draw rectangle
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect rect;
  rect.x = static_cast<int>(paddle.position.x);
  rect.y = static_cast<int>(paddle.position.y);
  rect.w = PADDLE_WIDTH;
  rect.h = PADDLE_HEIGHT;
  SDL_RenderFillRect(renderer, &rect);
}

/**
 * Initialization of the map. Draw the net and scores.
 */
void Graphics::initMap() {
  // Assert renderer exists
  assert(renderer);

  // Clear the window to black
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Draw net
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (int y = 0; y < SCREEN_HEIGHT; y += 4) {
    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, y);
  }
  // SDL_RenderPresent(renderer);
}

/**
 * Update player score
 */
void Graphics::updateScore(Score& score) {
  assert(font);
  assert(renderer);
  // render text
  SDL_Color color = {255, 255, 255, 255};
  playerText = TTF_RenderText_Solid(
      font, std::to_string(score.playerScore).c_str(), color);
  aiText =
      TTF_RenderText_Solid(font, std::to_string(score.aiScore).c_str(), color);
  // if (!playerText || !aiText) raise_ttf_error("Unable to render text!");

  // convert to texture
  playerTexture = SDL_CreateTextureFromSurface(renderer, playerText);
  aiTexture = SDL_CreateTextureFromSurface(renderer, aiText);
  // if (!playerTexture || !aiTexture)
  //   raise_ttf_error("Unable to create texture from surface!");

  // draw text
  playerDst = SDL_Rect{SCREEN_WIDTH / 4, 20, playerText->w, playerText->h};
  aiDst = SDL_Rect{SCREEN_WIDTH / 4 * 3, 20, aiText->w, aiText->h};
  SDL_RenderCopy(renderer, playerTexture, nullptr, &playerDst);
  SDL_RenderCopy(renderer, aiTexture, nullptr, &aiDst);
}