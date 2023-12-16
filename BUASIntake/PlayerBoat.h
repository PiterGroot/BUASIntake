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
	
	PlayerBoat();
	virtual ~PlayerBoat();

	void UpdatePlayer(float deltaTime);

	void SpawnPlayer();
};
