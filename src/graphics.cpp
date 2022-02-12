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

Graphics::Graphics(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font,
                   TTF_Font* titleFont) {
  this->renderer = renderer;
  this->window = window;
  this->font = font;
  this->titleFont = titleFont;
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
  // TODO: catch ttf error
  // if (!playerText || !aiText) raise_ttf_error("Unable to render text!");

  // convert to texture
  playerTexture = SDL_CreateTextureFromSurface(renderer, playerText);
  aiTexture = SDL_CreateTextureFromSurface(renderer, aiText);
  // TODO: catch error
  // if (!playerTexture || !aiTexture)
  //   raise_ttf_error("Unable to create texture from surface!");

  // draw text
  playerDst = SDL_Rect{SCREEN_WIDTH / 4 * 3, 20, playerText->w, playerText->h};
  aiDst = SDL_Rect{SCREEN_WIDTH / 4, 20, aiText->w, aiText->h};
  SDL_RenderCopy(renderer, playerTexture, nullptr, &playerDst);
  SDL_RenderCopy(renderer, aiTexture, nullptr, &aiDst);
}

/**
 * Draw the final winning/losing page. winner = 1 if player wins, 0 if ai wins.
 */
void Graphics::displayResult(int winner) {
  assert(font);
  assert(renderer);
  // render text
  SDL_Color color = {255, 255, 255, 255};
  SDL_Surface* resultText;
  if (winner == 1) {
    resultText = TTF_RenderText_Solid(font, "You Win!", color);
  } else {
    resultText = TTF_RenderText_Solid(font, "You Lose!", color);
  }
  SDL_Surface* instruction =
      TTF_RenderText_Solid(font, "Press r to restart, q to quit", color);
  SDL_Texture* resultTexture =
      SDL_CreateTextureFromSurface(renderer, resultText);
  SDL_Texture* instructionTexture =
      SDL_CreateTextureFromSurface(renderer, instruction);
  SDL_Rect resDst = SDL_Rect{SCREEN_WIDTH / 2 - resultText->w / 2,
                             SCREEN_HEIGHT / 3, resultText->w, resultText->h};
  SDL_Rect insDst =
      SDL_Rect{SCREEN_WIDTH / 2 - instruction->w / 2, SCREEN_HEIGHT / 3 * 2,
               instruction->w, instruction->h};
  SDL_RenderCopy(renderer, resultTexture, nullptr, &resDst);
  SDL_RenderCopy(renderer, instructionTexture, nullptr, &insDst);
}

void Graphics::displayPause() {
  assert(titleFont);
  assert(renderer);
  // draw background
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect rect{SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 50, 400, 100};
  SDL_RenderFillRect(renderer, &rect);
  // draw text
  SDL_Color color = {0, 0, 0, 255};
  SDL_Surface* text = TTF_RenderText_Solid(titleFont, "paused", color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
  SDL_Rect dst = SDL_Rect{SCREEN_WIDTH / 2 - text->w / 2,
                          SCREEN_HEIGHT / 2 - text->h / 2, text->w, text->h};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}
