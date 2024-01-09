#include <iostream>
#include "InputManager.h"
#include "../Game.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() 
{
    instance = this;
}

//Helper method for getting a checking single inputs
bool InputManager::GetKeyDown(sf::Keyboard::Key key) {
	if (sf::Keyboard::isKeyPressed(key) && canPressKey) {
		canPressKey = false;
		return true;
	}
	if (sf::Event::KeyReleased && Game::instance->GetWindowEvent()->key.code == key) {
		canPressKey = true;
	}

    return false;
}