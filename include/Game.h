#pragma once
#include <SDL.h>
#include "Board.h"
#include <bitset>
enum Signal : uint8_t{
    Zero,
    Button1,
    Button2,
    Button3,
    ButtonR
};
inline Board board;
class Game{
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    bool running = true;
    float desiredDensity = 20.625;
    bool showTiles = false;
    int bombIndex;

    int mouseState;
    int mouseX, mouseY;
    bool bDown;
    bool loseState = false;
    public:
        Game(int rows, int cols){initGame(rows, cols);}
        ~Game(){cleanup();}
        void handleResize(int r, int c, float dD){desiredDensity = dD; cleanup(); initGame(r, c);}
        void initGame(int rows, int cols);
        void run();
        void handleEvents();
        void handleInput();
        void update();
        void render();
        void cleanup();

        Signal signal;
}; 