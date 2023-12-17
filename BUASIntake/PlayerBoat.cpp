#include "PlayerBoat.h"
#include <iostream>

float startFuelAmount = 250;
float defaultMoveSpeed = 350;

float activeFuelConsumption = 25;
float passiveFuelConsumption = 2;

sf::Sprite* testSprite;

void PlayerBoat::InitializePlayer()
{
	fuel = startFuelAmount;
	moveSpeed = defaultMoveSpeed;

	upDirection.loadFromFile("Textures/Ship/ship1.png");
	upRightDirection.loadFromFile("Textures/Ship/ship15.png");
	rightDirection.loadFromFile("Textures/Ship/ship13.png");
	rightDownDirection.loadFromFile("Textures/Ship/ship11.png");
	downDirection.loadFromFile("Textures/Ship/ship9.png");
	downLeftDirection.loadFromFile("Textures/Ship/ship7.png");
	leftDirection.loadFromFile("Textures/Ship/ship5.png");
	leftUpDirection.loadFromFile("Textures/Ship/ship3.png");

	getDirectionalSprite = {
		{ sf::Vector2f(0, -1), upDirection},
		{ sf::Vector2f(1, -1), upRightDirection},
		{ sf::Vector2f(1, 0), rightDirection},
		{ sf::Vector2f(1, 1), rightDownDirection},
		{ sf::Vector2f(0, 1), downDirection},
		{ sf::Vector2f(-1, 1), downLeftDirection},
		{ sf::Vector2f(-1, 0), leftDirection},
		{ sf::Vector2f(-1, -1), leftUpDirection}
	};

	objectSprite.setScale(sf::Vector2f(2, 2));
	GameObject::InitializeGameobject("Textures/Ship/ship1.png", sf::Vector2f(32, 32));
}

void PlayerBoat::MovePlayer(sf::Vector2f newPosition, float deltaTime)
{
	if (fuel <= 0)
		return;

	sf::Vector2f currentPosition = position;

	position += newPosition * deltaTime;
	objectSprite.setPosition(position);

	if (currentPosition != position) fuel -= deltaTime * activeFuelConsumption;
	else fuel -= deltaTime * passiveFuelConsumption;
	
	//std::cout << fuel << "\n";
}


//Get normalized movement direction
sf::Vector2f PlayerBoat::GetMovementDirection() {
	sf::Vector2f direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		direction += sf::Vector2f(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		direction += sf::Vector2f(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		direction -= sf::Vector2f(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		direction += sf::Vector2f(1, 0);
	}
	
	return direction;
}

void PlayerBoat::UpdatePlayer(float deltaTime)
{
	auto moveDir = GetMovementDirection();

	if(moveDir == sf::Vector2f(0, 0)) objectSprite.setTexture(upDirection);
	else objectSprite.setTexture(getDirectionalSprite[moveDir]);

	std::cout << moveDir.x << " " << moveDir.y << " \n";

	MovePlayer(normalized(moveDir) * moveSpeed, deltaTime);
}