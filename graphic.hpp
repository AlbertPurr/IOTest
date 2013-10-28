#ifndef graph_h
#define graph_h

#include "library.hpp"

class Game
{
    public:
        int Init();// load data, initialize sdl
        int Render(); // manage screen display
        int Events(); //manage keyboard, mouse and other input
        int Loop(); // main loop of game
        int Cleanup(); // manage game quit, clearing all data
};


#endif // graph_h
