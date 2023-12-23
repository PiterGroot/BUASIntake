#pragma once

class Game;

#include "GameObject.h"
#include "Collider.h"
#include <map>

class PlayerBoat : public GameObject
{
private:	
	void MovePlayer(sf::Vector2f newPosition, float deltaTime);
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

public:
	Collider GetCollider() { return Collider(GetGameObject()); }

	float fuel;
	float moveSpeed;
	sf::Vector2f currentMoveDir;

	void UpdatePlayer(float deltaTime);
	void InitializePlayer(sf::Vector2f spawnPosition);
};