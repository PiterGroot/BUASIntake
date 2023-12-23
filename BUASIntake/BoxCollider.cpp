#include "BoxCollider.h"

BoxCollider::BoxCollider(sf::String texturePath, sf::Vector2f position, bool isTrigger)
	: Collider(GetGameObject()) // Call the Collider constructor
{
	SetTrigger(isTrigger);
	InitializeGameobject(texturePath, this->position = position);
}