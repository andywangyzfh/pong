#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include <iostream>

#include "constants.h"
#include "graphics.h"
#include "physics.h"

void raise_error(const std::string& msg) {
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

void raise_ttf_error(const std::string& msg) {
  std::cerr << msg << " (" << TTF_GetError() << ")" << std::endl;
  exit(0);
}

int main(int argc, char** argv) {
  /*** Initialization ***/

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    raise_error("SDL could not initialize!");

  // Create window
  SDL_Window* window =
      SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) raise_error("Window could not be created!");

  // Init TTF
  if (TTF_Init() < 0) raise_ttf_error("Unable to initialize TTF!");

  // Small delay to allow the system to create the window.
  SDL_Delay(100);

  // Create renderer
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) raise_error("Unable to create renderer!");

  // Load font
  TTF_Font* font = TTF_OpenFont("../resource/Arial.ttf", 50);
  TTF_Font* smallFont = TTF_OpenFont("../resource/Arial.ttf", 30);
  TTF_Font* titleFont =
      TTF_OpenFont("../resource/Comfortaa-VariableFont_wght.ttf", 50);
  if (!font || !smallFont || !titleFont)
    raise_ttf_error("Unable to open font!");

  // Init audio
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  Mix_Chunk* paddleSound = Mix_LoadWAV("../resource/paddle.wav");
  Mix_Chunk* wallSound = Mix_LoadWAV("../resource/wall.wav");
  if (!paddleSound || !wallSound) raise_error("Unable to load audio!");

  // Initialize graphics class
  Graphics* graphics =
      new Graphics(renderer, window, font, titleFont, smallFont);

  // Initialize ball
  Vec2d center(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
  Ball ball(center);

  // Initialize paddles
  Vec2d aiPos(40, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
  Vec2d playerPos(SCREEN_WIDTH - 40, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
  Paddle aiPaddle(aiPos, 0.0f);
  Paddle playerPaddle(playerPos, 0.0f);

  // Initialize score
  Score score;

  /*** Main Loop ***/

  // Define flags and utils
  bool running = true;
  bool starting = true;
  bool startingRendered = false;
  bool paused = false;
  bool pauseMessageRendered = false;
  SDL_Event e;
  int dt = 0;
  float difficulty = 1.0f;

  // While application is running
  while (running) {
    // Get start time
    auto start = SDL_GetTicks64();

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) running = false;
      // User presses a key
      else if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_q ||
            e.key.keysym.sym == SDLK_ESCAPE) {  // quit
          running = false;
        } else if (e.key.keysym.sym == SDLK_p) {  // pause
          paused = !paused;
          pauseMessageRendered = false;
        } else if (e.key.keysym.sym == SDLK_r) {  // restart
          // Reset ball & paddles' position
          ball = Ball();
          aiPaddle = Paddle(aiPos, 0.0f);
          playerPaddle = Paddle(playerPos, 0.0f);
          score = Score();
        } else if (e.key.keysym.sym == SDLK_1) {  // difficulty 1
          difficulty = 0.8;
          starting = false;
        } else if (e.key.keysym.sym == SDLK_2) {  // difficulty 2
          difficulty = 1;
          starting = false;
        } else if (e.key.keysym.sym == SDLK_3) {  // difficulty 3
          difficulty = 1.5;
          starting = false;
        } else if (e.key.keysym.sym == SDLK_4) {  // difficulty 4
          difficulty = 2.0;
          starting = false;
        } else if (e.key.keysym.sym ==
                   SDLK_d) {  // debug, set player score to 10
          score.playerScore = 10;
        } else if (e.key.keysym.sym == SDLK_f) {  // debug, set AI score to 10
          score.aiScore = 10;
        }
      }
    }

    // Render starting page if not rendered
    if (starting) {
      if (!startingRendered) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        graphics->displayStartingPage();
        SDL_RenderPresent(renderer);
        startingRendered = true;
      }
      continue;
    }

    // Check if the window is minimized. If so, pause the game.
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
      paused = true;
    }

    // Render paused message if not rendered
    if (paused) {
      if (!pauseMessageRendered) {
        graphics->displayPause();
        SDL_RenderPresent(renderer);
        pauseMessageRendered = true;
      }
      continue;
    }

    // Get key press and update paddle direction
    bool paddleDown = false, paddleUp = false;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_DOWN])
      paddleDown = true;
    else if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_UP])
      paddleUp = true;
    else {
      paddleUp = false;
      paddleDown = false;
    }

    // Update paddle speed according to the direction
    if (paddleUp) {
      playerPaddle.velocity = -PADDLE_VELOCITY;
    } else if (paddleDown) {
      playerPaddle.velocity = PADDLE_VELOCITY;
    } else {
      playerPaddle.velocity = 0.0f;
    }

    // AI paddle movement
    if (ball.velocity.x < 0) {
      if (aiPaddle.position.y + PADDLE_HEIGHT / 2 > ball.position.y) {
        aiPaddle.velocity = -AI_VELOCITY;
      } else {
        aiPaddle.velocity = AI_VELOCITY;
      }
    } else {
      aiPaddle.velocity = 0;
    }

    // Update paddle position according to dt
    playerPaddle.update(dt);
    aiPaddle.update(dt);
    ball.update(dt);

    // Check collision
    CollisionPoint cpPlayer = collideWithPaddle(ball, playerPaddle);
    CollisionPoint cpAI = collideWithPaddle(ball, aiPaddle);
    CollisionPoint cpWall = collideWithWall(ball);
    ball.processCollision(cpPlayer);
    ball.processCollision(cpAI);
    ball.processCollision(cpWall);

    // Play sound
    if (cpPlayer.type != CollisionType::None ||
        cpAI.type != CollisionType::None) {
      Mix_PlayChannel(-1, paddleSound, 0);
    }
    if (cpWall.type != CollisionType::None) {
      Mix_PlayChannel(-1, wallSound, 0);
    }

    // Update score if left/right wall is hit
    if (cpWall.type == CollisionType::Left) {
      score.goal(1);
    } else if (cpWall.type == CollisionType::Right) {
      score.goal(0);
    }

    // Render current frame
    // Clear the window to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set the draw color to be white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // If ai/player achieved 11 points, display winning/losing page, else
    // render updated ball & paddles.
    if (score.aiScore >= 11) {
      graphics->displayResult(0);
      ball.velocity = Vec2d(0, 0);
    } else if (score.playerScore >= 11) {
      graphics->displayResult(1);
      ball.velocity = Vec2d(0, 0);
    } else {
      graphics->initMap();
      graphics->drawBall(ball);
      graphics->drawPaddle(aiPaddle);
      graphics->drawPaddle(playerPaddle);
      graphics->updateScore(score);
    }
    SDL_RenderPresent(renderer);

    // Update dt
    dt = SDL_GetTicks64() - start;
    dt *= difficulty;
  }

  /*** Clean Up ***/

  // Destroy audio
  Mix_FreeChunk(paddleSound);
  Mix_FreeChunk(wallSound);
  Mix_Quit();

  // Destroy renderer
  SDL_DestroyRenderer(renderer);

  // Destroy window
  SDL_DestroyWindow(window);

  // Destroy font
  TTF_CloseFont(font);
  TTF_Quit();

  // Quit SDL subsystems
  SDL_Quit();

  // Done.
  return 0;
}