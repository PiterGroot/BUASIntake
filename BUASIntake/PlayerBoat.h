#pragma once

#include "GameObject.h"
#include "Collider.h"
#include <iostream>
#include <map>

class PlayerBoat : public GameObject, public Collider
{
public:
	PlayerBoat(sf::Vector2f spawnPosition);

	void OnCollision(Collider& other) override;
	void OnUpdate(float deltaTime) override;
	void HandleGameOver(float deltaTime);
	
	void SetFuel(float newFuel);
	float GetFuel();

	void UpdateStorageLabel(PlayerBoat* player);

	sf::Vector2f currentMoveDirection;
	
	int storageCapacity = 0;
	int currentStorageAmount = 0;

	float activeFuelConsumption = 0;
	float passiveFuelConsumption = 0;
	
	float moveSpeed = 0;
	
private:
	float fuel = 0;
	float gameOverTimer = 0;

	int randCleanupTries = 0;
	int randWiggleTries = 0;

	bool isInsideKraken = false;
	bool isInsidePickup = false;

	bool isMoving = false;

	sf::Texture upDirection;
	sf::Texture upRightDirection;
	sf::Texture rightDirection;
	sf::Texture rightDownDirection;
	sf::Texture downDirection;
	sf::Texture downLeftDirection;
	sf::Texture leftDirection;
	sf::Texture leftUpDirection;

	std::map<sf::Vector2f, sf::Texture, Vector2fEquals> getDirectionalSprite;

	sf::Vector2f GetMovementDirection();
	void MovePlayer(sf::Vector2f newPosition, float deltaTime);

	void UpdateDistanceLabel(sf::Vector2f currentPosition);
	void UpdateFuelLabel(float currentFuel);
	void UpdateCleanupLabel();

	void OnCollideWithVortex(PlayerBoat* player);
	void OnCollideWithPickup(Collider& other, PlayerBoat* player);
	void OnCollideWithKraken(Collider& other, PlayerBoat* player);
	bool TryCleanupDebris(float currentStorageAmount, float storageCapacity);
};