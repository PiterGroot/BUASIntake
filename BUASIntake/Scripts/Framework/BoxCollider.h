#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"

class BoxCollider : public GameObject, public Collider
{
public:
	BoxCollider(sf::String name, sf::String texturePath, sf::Vector2f position, bool isTrigger);
};