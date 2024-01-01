#pragma once
#include <SFML/Graphics.hpp>

class InputManager {
public:
    InputManager();
    static InputManager* instance;

    bool GetKeyDown(sf::Keyboard::Key key);
    bool canPressKey = true;

    void Reset() { canPressKey = true; };
};
