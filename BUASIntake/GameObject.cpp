#include "GameObject.h"
#include "Game.h"

void GameObject::InitializeGameobject(sf::String name, sf::String texturePath, sf::Vector2f position, bool isHudObject)
{
    this->name = name;
    this->position = position;

    objectTexture.loadFromFile(texturePath);
    objectSprite.setTexture(objectTexture);
    objectSprite.setOrigin(sf::Vector2f(objectTexture.getSize()) * .5f);
    objectSprite.setPosition(this->position);

    if (isHudObject) Game::instance->hudGameobjects.push_back(this);
    else Game::instance->gameobjects.push_back(this);
}

void GameObject::MoveGameObject(sf::Vector2f newPosition) 
{
    objectSprite.setPosition(newPosition);
}