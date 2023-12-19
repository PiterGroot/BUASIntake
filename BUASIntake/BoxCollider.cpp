#include "BoxCollider.h"

BoxCollider::BoxCollider(sf::String texturePath, sf::Vector2f position, sf::Vector2f size) 
{
	InitializeGameobject(texturePath, sf::Vector2f(32, 32));
}