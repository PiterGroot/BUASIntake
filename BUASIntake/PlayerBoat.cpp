#include "PlayerBoat.h"
#include <iostream>

float startFuelAmount = 250;
float defaultMoveSpeed = 350;

float activeFuelConsumption = 25;
float passiveFuelConsumption = 2;

#pragma region Constructor / Deconstructor

//FuelMeter fuelMeter;
PlayerBoat::PlayerBoat()
{
	fuel = startFuelAmount;
	moveSpeed = defaultMoveSpeed;
}

PlayerBoat::~PlayerBoat()
{
}

#pragma endregion

void PlayerBoat::SpawnPlayer() 
{
	GameObject::InitializeGameobject("Textures/circle.png", sf::Vector2f(32, 32));
}

void PlayerBoat::MovePlayer(sf::Vector2f newPosition, float deltaTime)
{
	if (fuel <= 0)
		return;

	sf::Vector2f currentPosition = position;

	position += newPosition * deltaTime;
	objectSprite.setPosition(position);

	if (currentPosition != position) 
		fuel -= deltaTime * activeFuelConsumption;
	else
		fuel -= deltaTime * passiveFuelConsumption;
	
	//std::cout << fuel << "\n";
}

//Get normalized movement direction
sf::Vector2f GetMovementDirection() {
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

	return normalized(direction);
}

void PlayerBoat::UpdatePlayer(float deltaTime)
{
	auto moveDir = GetMovementDirection();
	MovePlayer(moveDir * moveSpeed, deltaTime);
}