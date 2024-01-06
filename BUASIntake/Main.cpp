#include "Game.h"

int main()
{
    Game* game = new Game();
    sf::Clock clock;

    // Run game as long as the window is open
    while (game->isWindowActive())
    {
        float deltaTime = clock.restart().asSeconds(); //calculate deltatime

        game->OnUpdate(deltaTime); //call game main update loop
        game->OnRender(); //call game render loop
        game->OnLateUpdate(deltaTime); //call game late update loop
    }

    return 0;
}