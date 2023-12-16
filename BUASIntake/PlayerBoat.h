#pragma once

class Game;
#include "GameObject.h"

class PlayerBoat : public GameObject
{
private:	
	void MovePlayer(sf::Vector2f newPosition, float deltaTime);

public:
	float fuel;
	float moveSpeed;

	void UpdatePlayer(float deltaTime);
	void InitializePlayer();
};
