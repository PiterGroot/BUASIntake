#pragma once

#include "../Framework/GameObject.h"
#include "../Game.h"
#include <iostream>

class Waypoint : public GameObject 
{
public:
	Waypoint(sf::String name, sf::String texturePath, sf::Vector2f targetPosition, sf::Color color, bool doRotate = true);
	void OnUpdate(float deltaTime) override;

	void RotateTowardsBase(GameObject* waypoint, sf::Vector2f targetPosition);
	void ClampPosition(GameObject* waypoint, sf::Vector2f targetPosition);

	sf::Vector2f targetPosition;

private:
	bool doRotate = true;
};