#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "Game.h"

class Enemy : public GameObject, public Collider
{
public:
	Enemy(sf::String name, sf::String texture, sf::Vector2f position);
	void OnUpdate(float deltaTime) override;

private:
	float moveSpeed = 100;
	sf::Vector2f moveDirection;
};