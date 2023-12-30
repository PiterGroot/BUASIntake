#pragma once

#include "GameObject.h"
#include <iostream>
#include "Game.h"

class Waypoint : public GameObject 
{
public:
	Waypoint(sf::String name, sf::String texturePath, sf::Vector2f targetPosition);
	void OnUpdate(float deltaTime) override;

private:
	sf::Vector2f targetPosition;
};