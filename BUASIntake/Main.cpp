#include "Game.h"

int main()
{
    Game game;
    sf::Clock clock;

    // run the program as long as the window is open
    while (game.isWindowActive())
    {
        float deltaTime = clock.restart().asSeconds();

        game.OnUpdate(deltaTime);
        game.OnRender();
        game.OnLateUpdate(deltaTime);
    }

    return 0;
}