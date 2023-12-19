#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Collider.h"

class BoxCollider : public GameObject
{
public:
	BoxCollider(sf::String texturePath, sf::Vector2f position, sf::Vector2f size);

	Collider GetCollider() { return Collider(GetGameObject()); }
	void Draw(sf::RenderWindow& window);
};