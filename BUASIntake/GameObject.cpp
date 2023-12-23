#include "Game.h"
#include "GameObject.h"


void GameObject::InitializeGameobject(sf::String texturePath, sf::Vector2f position, bool isHudObject)
{
    this->position = position;

    objectTexture.loadFromFile(texturePath);
    objectSprite.setTexture(objectTexture);
    objectSprite.setOrigin(sf::Vector2f(objectTexture.getSize()) * .5f);
    objectSprite.setPosition(this->position);

    if (isHudObject) Game::instance->hudGameobjects.push_back(&objectSprite);
    else Game::instance->gameobjects.push_back(&objectSprite);
}

void GameObject::MoveGameObject(sf::Vector2f newPosition) 
{
    objectSprite.setPosition(newPosition);
}