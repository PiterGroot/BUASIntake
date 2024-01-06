#include "GameObject.h"
#include "Game.h"

//Set necessary gameobject values and create/initialize gameobject for rendering and updating 
void GameObject::InitializeGameobject(sf::String name, sf::String texturePath, sf::Vector2f position, bool isHudObject)
{
    this->name = name;
    this->position = position;

    if (!texturePath.isEmpty()) 
    {
        objectTexture.loadFromFile(texturePath);
        objectSprite.setTexture(objectTexture);
    }

    objectSprite.setOrigin(sf::Vector2f(objectTexture.getSize()) * .5f);
    objectSprite.setPosition(this->position);

    //push object to hudGameobjects if it need to be stuck to the screen (UI objects)
    //otherwise push it to gameobjects which is used for normal objects that are rendered in worldspace
    if (isHudObject) Game::instance->hudGameobjects.push_back(this);
    else Game::instance->gameobjects.push_back(this);
}

//Helper method to translate a gameobject
void GameObject::MoveGameObject(sf::Vector2f newPosition) 
{
    objectSprite.setPosition(newPosition);
}