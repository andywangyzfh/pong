//Using SDL and standard IO
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

void csci437_error(const std::string& msg)
{
  std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
  exit(0);
}

int main(int argc, char** argv)
{
  /*** Initialization ***/
  
  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) csci437_error("SDL could not initialize!");

  // Create window
  SDL_Window* window = SDL_CreateWindow( "CSCI-437 Skeleton", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  if( window == NULL ) csci437_error("Window could not be created!");

  // Small delay to allow the system to create the window.
  SDL_Delay(100);
    
  // Create renderer
  SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
  if (renderer == NULL) csci437_error("Unable to create renderer!");

  bool box=true, circle=true, line=true;
  
  /*** Main Loop ***/
  bool running = true;
  SDL_Event e;

  // While application is running
  while( running )
  {
    // Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
      // User requests quit
      if( e.type == SDL_QUIT ) running = false;

      // User presses a key
      if( e.type == SDL_KEYDOWN )
      {
        if( e.key.keysym.sym == SDLK_q ) running = false;
        if( e.key.keysym.sym == SDLK_b ) box = !box;
        if( e.key.keysym.sym == SDLK_c ) circle = !circle;
        if( e.key.keysym.sym == SDLK_l ) line = !line;
      }

      // render
      SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
      SDL_RenderClear( renderer );

      if(line)
      {
        thickLineRGBA(renderer, 0, 0, 500, 600, 8, 255, 255, 255, 128);
        lineRGBA(renderer, 768, 0, 0, 1024, 0, 0, 255, 128); 
      }
      if(box)
      {
        boxRGBA(renderer, 30, 50, 330, 250, 255, 0, 0, 128);
        rectangleRGBA(renderer, 30, 50, 330, 250, 255, 255, 255, 255);
      }

      if(circle)
      {
        filledCircleRGBA(renderer, 500, 600, 100, 0, 255, 0, 128);
        circleRGBA(renderer, 500, 600, 100, 255, 255, 255, 255);
      }
      
      SDL_RenderPresent( renderer );
    }
  }

  /*** Clean Up ***/

  // Destroy renderer
  SDL_DestroyRenderer( renderer );
  
  // Destroy window
  SDL_DestroyWindow( window );

  // Quit SDL subsystems
  SDL_Quit();
  
  // Done.
  return 0;
}
