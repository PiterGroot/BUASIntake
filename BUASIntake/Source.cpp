#include <SFML/Graphics.hpp>

using namespace sf;

// Define the Ball struct
struct Ball
{
    Vector2f position;
    float moveSpeed = 350;
    Vector2f origin = Vector2f(32, 32);
};

Texture ballTexture;
Sprite ball;
Ball player;

float deltaTime;
Vector2f GetMovementDirection();

int main()
{
    // Create the window
    RenderWindow window(VideoMode(800, 600), "Game Window", Style::Titlebar | Style::Close);

    //load ball texture
    ballTexture.loadFromFile("ball.png");
    ball.setTexture(ballTexture);

    Vector2u windowSize = window.getSize();
    player.position = Vector2f(windowSize.x / 2, windowSize.y / 2);

    Clock clock;

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

        // clear the window with black color
        window.clear(Color::Black);

        auto moveDir = GetMovementDirection();
        player.position += moveDir * player.moveSpeed * deltaTime;

        ball.setPosition(player.position - player.origin);
        window.draw(ball);

        // end the current frame
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