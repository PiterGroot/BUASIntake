#pragma once

#include "GameObject.h"
#include <iostream>
#include "Game.h"

class Waypoint : public GameObject 
{
public:
	Waypoint(sf::String name, sf::String texturePath, sf::Vector2f targetPosition, sf::Color color, bool doRotate = true);
	void OnUpdate(float deltaTime) override;
	sf::Vector2f targetPosition;

private:
	bool doRotate = true;
};