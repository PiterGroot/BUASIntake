#include "BoxCollider.h"

BoxCollider::BoxCollider(sf::String name, sf::String texturePath, sf::Vector2f position, bool isTrigger)
	: Collider(GetGameObject(), isTrigger) // Call the Collider constructor
{
	InitializeGameobject(name, texturePath, this->position = position);
}