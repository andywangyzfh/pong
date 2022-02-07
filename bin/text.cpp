//Using SDL and standard IO
#include <SDL.h>
#include <SDL_ttf.h>
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

void csci437_ttf_error(const std::string& msg)
{
  std::cerr << msg << " (" << TTF_GetError() << ")" << std::endl;
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

  // init TTF
  if( TTF_Init() < 0 ) csci437_ttf_error("Unable to initialize TTF!");

  // Small delay to allow the system to create the window.
  SDL_Delay(100);
    
  // Create renderer
  SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
  if (renderer == NULL) csci437_error("Unable to create renderer!");

  // Load font
  TTF_Font* font = TTF_OpenFont("../resource/Arial.ttf", 50);
  if (font == NULL) csci437_error("Unable to open font!");

  // render text
  SDL_Color color = { 255, 255, 255 };
  SDL_Surface* text = TTF_RenderText_Solid( font, "Hello World!", color );
  if ( text == NULL ) csci437_ttf_error("Unable to render text!");
  
  // convert to texture
  SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, text );
  if(texture == NULL) csci437_error("Could not create texture from surface!");
  
  bool red=true, green=true, blue=true;
  float angle = 0;
  
  SDL_Rect dst = { (SCREEN_WIDTH - text->w) / 2, (SCREEN_HEIGHT - text->h) / 2, text->w, text->h};
  SDL_Point rot = {text->w/2, text->h/2};

  // delete image
  SDL_FreeSurface( text );
  text = NULL;
  
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
        if( e.key.keysym.sym == SDLK_r ) red = !red;
        if( e.key.keysym.sym == SDLK_g ) green = !green;
        if( e.key.keysym.sym == SDLK_b ) blue = !blue;
        if( e.key.keysym.sym == SDLK_z ) angle -= 10;
        if( e.key.keysym.sym == SDLK_x ) angle += 10;
      }

      // render
      SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
      SDL_RenderClear( renderer );
      SDL_SetTextureColorMod( texture, red*255, green*255, blue*255 );
      SDL_RenderCopyEx( renderer, texture, NULL, &dst, angle, &rot, SDL_FLIP_NONE );
      SDL_RenderPresent( renderer );
    }
  }

  /*** Clean Up ***/

  // Destroy texture
  SDL_DestroyTexture( texture );
  
  // Destroy renderer
  SDL_DestroyRenderer( renderer );
  
  // Destroy window
  SDL_DestroyWindow( window );

  // Quit SDL subsystems
  SDL_Quit();
  
  // Done.
  return 0;
}
