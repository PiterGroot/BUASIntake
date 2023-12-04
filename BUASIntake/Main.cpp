#include "Game.h"

int main()
{
    Game game;
    Clock clock;
    
    // run the program as long as the window is open
    while (game.isWindowActive())
    {
        game.OnUpdate(clock.restart().asSeconds());
        game.OnRender();
    }

    return 0;
}
