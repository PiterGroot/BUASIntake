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
	void SetFuel(float newFuel);
	float GetFuel();

	int storageCapacity = 0;
	int currentStorageAmount = 0;
	
	sf::Vector2f currentMoveDirection;
	
private:

	float fuel = 0;
	float moveSpeed = 0;

	sf::Vector2f GetMovementDirection();
	
	sf::Texture upDirection;
	sf::Texture upRightDirection;
	sf::Texture rightDirection;
	sf::Texture rightDownDirection;
	sf::Texture downDirection;
	sf::Texture downLeftDirection;
	sf::Texture leftDirection;
	sf::Texture leftUpDirection;

	std::map<sf::Vector2f, sf::Texture, Vector2fEquals> getDirectionalSprite;
	void MovePlayer(sf::Vector2f newPosition, float deltaTime);

	void UpdateDistanceLabel(sf::Vector2f currentPosition);
	void UpdateStorageLabel(PlayerBoat* player);
	void UpdateFuelLabel(float currentFuel);
	void UpdateCleanupLabel();

	void OnCollideWithVortex(PlayerBoat* player);
	void OnCollideWithPickup(Collider& other, PlayerBoat* player);
	void OnCollideWithKraken(Collider& other, PlayerBoat* player);
	bool TryCleanupDebris(float currentStorageAmount, float storageCapacity);
};