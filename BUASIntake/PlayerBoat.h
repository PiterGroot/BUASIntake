#pragma once

class Game;

#include "GameObject.h"
#include "vec2.hpp"
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

public:
	std::map<sf::Vector2f, sf::Texture, Vector2fEquals> getDirectionalSprite;

	float fuel;
	float moveSpeed;

	void UpdatePlayer(float deltaTime);
	void InitializePlayer();
};
