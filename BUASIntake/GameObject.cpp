#include "Game.h"
#include "GameObject.h"

void GameObject::InitializeGameobject(sf::String texturePath, sf::Vector2f origin, bool isHudObject)
{
    objectTexture.loadFromFile(texturePath);
    objectSprite.setTexture(objectTexture);
    objectSprite.setOrigin(origin);

    if (isHudObject) Game::instance->hudGameobjects.push_back(&objectSprite);
    else Game::instance->gameobjects.push_back(&objectSprite);
}