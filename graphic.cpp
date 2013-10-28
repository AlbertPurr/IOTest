#ifndef graph_c
#define graph_c

#include "graphic.hpp"

int Game::Init()// load data, initialize sdl
{
    SDL_Init(SDL_INIT_EVERYTHING);
    return 0;
}

int Game::Render() // manage screen display
{
    return 0;
}

int Game::Events() //manage keyboard, mouse and other input
{
    return 0;
}

int Game::Loop() // main loop of game
{
   return 0;
}

int Game::Cleanup() // manage game quit, clearing all data
{
   return 0;
}


#endif // graph_c
