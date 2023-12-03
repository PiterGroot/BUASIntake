#include <SFML/Graphics.hpp>
#include "vec2.hpp"
using namespace sf;

// Define the Boat struct
struct Boat
{
    Vector2f position;
    float moveSpeed = 350;
    Vector2f origin = Vector2f(32, 32);
};

Texture boatTexture;
Sprite boatSprite;
Boat player;
Boat test;

float deltaTime;
Vector2f GetMovementDirection();

const Color waterColor(3, 165, 252);

int main()
{
    // Create the window
    RenderWindow window(VideoMode(800, 600), "Game Window", Style::Titlebar | Style::Close);

    //load ball texture
    boatTexture.loadFromFile("ball.png");
    boatSprite.setTexture(boatTexture);

    Vector2u windowSize = window.getSize();
    player.position = Vector2f(windowSize.x / 2, windowSize.y / 2);
    test.position = player.position;

    Clock clock;
    View view = window.getDefaultView();
    
    // run the program as long as the window is open
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        // check all the window's events that were triggered since the last iteration of the loop
        Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            // "close requested" event: we close the window
            if (windowEvent.type == Event::Closed)
                window.close();
        }
        
        // Update player position
        auto moveDir = GetMovementDirection();
        player.position += moveDir * player.moveSpeed * deltaTime;

        // Update view center to follow the player
        Vector2f viewPos = view.getCenter();
        Vector2f lerpedViewCenter = lerp(viewPos, player.position, 5 * deltaTime);
        view.setCenter(lerpedViewCenter);

        // Clear the window
        window.clear(waterColor);
        window.setView(view);

        // Draw the ball
        boatSprite.setPosition(player.position - player.origin);
        window.draw(boatSprite);

        Sprite testSprite = boatSprite;
        testSprite.setPosition(test.position);
        window.draw(testSprite);
        
        // Display the content
        window.display();
    }

    return 0;
}

Vector2f Normalize(const Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return Vector2f(source.x / length, source.y / length);
    else
        return source;
}


Vector2f GetMovementDirection() {
    Vector2f direction;
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        direction += Vector2f(0, -1);
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        direction += Vector2f(-1, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        direction -= Vector2f(0, -1);
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        direction += Vector2f(1, 0);
    }
    return Normalize(direction);
}