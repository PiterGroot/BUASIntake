#include "BoxCollider.h"
#include "Game.h"

BoxCollider::BoxCollider(sf::String name, sf::String texturePath, sf::Vector2f position, bool isTrigger)
	: Collider(this, isTrigger) // Call the Collider constructor
{
	Game::instance->activeColliders.push_back(this);
	InitializeGameobject(name, texturePath, this->position = position);
}