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
                   TTF_Font* titleFont, TTF_Font* smallFont) {
  this->renderer = renderer;
  this->window = window;
  this->font = font;
  this->titleFont = titleFont;
  this->smallFont = smallFont;
}

/**
 * Destructor
 */
Graphics::~Graphics() {
  SDL_FreeSurface(playerText);
  SDL_FreeSurface(aiText);
  SDL_FreeSurface(resultText);
  SDL_FreeSurface(instruction);
  SDL_FreeSurface(text);
  SDL_FreeSurface(title);
  SDL_FreeSurface(description);
  SDL_DestroyTexture(playerTexture);
  SDL_DestroyTexture(aiTexture);
  SDL_DestroyTexture(texture);
  SDL_DestroyTexture(resultTexture);
  SDL_DestroyTexture(instructionTexture);
  SDL_DestroyTexture(titleTexture);
  SDL_DestroyTexture(descriptionTexture);
}

/*
 * Draw ball on the map.
 */
void Graphics::drawBall(Ball& ball) {
  // Assert renderer exists
  assert(renderer);
  // Draw rectangle
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect rect;

  // resize
  int windowWidth, windowHeight;
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);
  rect.x = static_cast<int>(ball.position.x * windowWidth / SCREEN_WIDTH);
  rect.y = static_cast<int>(ball.position.y * windowHeight / SCREEN_HEIGHT);
  rect.w = static_cast<int>(BALL_WIDTH * 1.0f * windowWidth / SCREEN_WIDTH);
  rect.h = static_cast<int>(BALL_HEIGHT * 1.0f * windowHeight / SCREEN_HEIGHT);
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
  // resize
  int windowWidth, windowHeight;
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);
  rect.x = static_cast<int>(paddle.position.x * windowWidth / SCREEN_WIDTH);
  rect.y = static_cast<int>(paddle.position.y * windowHeight / SCREEN_HEIGHT);
  rect.w = static_cast<int>(PADDLE_WIDTH * 1.0f * windowWidth / SCREEN_WIDTH);
  rect.h =
      static_cast<int>(PADDLE_HEIGHT * 1.0f * windowHeight / SCREEN_HEIGHT);
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

  // resize
  int windowWidth, windowHeight;
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);

  // Draw net
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (int y = 0; y < windowHeight; y += 4) {
    SDL_RenderDrawPoint(renderer, windowWidth / 2, y);
  }
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

  // convert to texture
  playerTexture = SDL_CreateTextureFromSurface(renderer, playerText);
  aiTexture = SDL_CreateTextureFromSurface(renderer, aiText);

  // resize
  int windowWidth, windowHeight;
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);

  // draw text
  playerDst = SDL_Rect{windowWidth / 4 * 3, 20, playerText->w, playerText->h};
  aiDst = SDL_Rect{windowWidth / 4, 20, aiText->w, aiText->h};
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
  if (winner == 1) {
    resultText = TTF_RenderText_Solid(font, "You Win!", color);
  } else {
    resultText = TTF_RenderText_Solid(font, "You Lose!", color);
  }
  instruction =
      TTF_RenderText_Solid(smallFont, "Press R to restart, Q to quit", color);
  resultTexture = SDL_CreateTextureFromSurface(renderer, resultText);
  instructionTexture = SDL_CreateTextureFromSurface(renderer, instruction);

  // resize
  int windowWidth, windowHeight;
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);
  SDL_Rect resDst = SDL_Rect{windowWidth / 2 - resultText->w / 2,
                             windowHeight / 3, resultText->w, resultText->h};
  SDL_Rect insDst =
      SDL_Rect{windowWidth / 2 - instruction->w / 2, windowHeight / 3 * 2,
               instruction->w, instruction->h};
  // render
  SDL_RenderCopy(renderer, resultTexture, nullptr, &resDst);
  SDL_RenderCopy(renderer, instructionTexture, nullptr, &insDst);
}

/**
 * Display pause message in game states
 */
void Graphics::displayPause() {
  assert(titleFont);
  assert(renderer);

  // draw background
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect rect{SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 50, 400, 100};
  SDL_RenderFillRect(renderer, &rect);

  // draw text
  SDL_Color color = {0, 0, 0, 255};
  text = TTF_RenderText_Solid(titleFont, "paused", color);
  texture = SDL_CreateTextureFromSurface(renderer, text);
  SDL_Rect dst = SDL_Rect{SCREEN_WIDTH / 2 - text->w / 2,
                          SCREEN_HEIGHT / 2 - text->h / 2, text->w, text->h};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

/**
 * Display the starting page
 */
void Graphics::displayStartingPage() {
  assert(font);
  assert(titleFont);
  assert(renderer);

  // render text
  SDL_Color color = {255, 255, 255, 255};
  title = TTF_RenderText_Solid(titleFont, "PONG!", color);
  description =
      TTF_RenderText_Solid(smallFont, "Choose difficulty from 1 to 5", color);
  titleTexture = SDL_CreateTextureFromSurface(renderer, title);
  descriptionTexture = SDL_CreateTextureFromSurface(renderer, description);
  SDL_Rect resDst = SDL_Rect{SCREEN_WIDTH / 2 - title->w / 2, SCREEN_HEIGHT / 3,
                             title->w, title->h};
  SDL_Rect insDst =
      SDL_Rect{SCREEN_WIDTH / 2 - description->w / 2, SCREEN_HEIGHT / 3 * 2,
               description->w, description->h};
  SDL_RenderCopy(renderer, titleTexture, nullptr, &resDst);
  SDL_RenderCopy(renderer, descriptionTexture, nullptr, &insDst);
}