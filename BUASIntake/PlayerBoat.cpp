#include "PlayerBoat.h"
#include <iostream>
#include "Game.h"

#pragma region MyRegion

float startFuelAmount = 250;
float defaultMoveSpeed = 350;
float fuelConsumption = 25;

PlayerBoat::PlayerBoat()
{
	fuel = startFuelAmount;
	moveSpeed = defaultMoveSpeed;

	boatTexture.loadFromFile("Textures/circle.png");
	boatSprite.setTexture(boatTexture);
	boatSprite.setOrigin(playerOrigin);
}

PlayerBoat::~PlayerBoat()
{
}

#pragma endregion


void PlayerBoat::MovePlayer(Vector2f newPosition, float deltaTime)
{
	if (fuel <= 0)
		return;

	Vector2f currentPosition = position;

	this->position += newPosition;
	boatSprite.setPosition(this->position);

	if (currentPosition != position) {
		fuel -= deltaTime * fuelConsumption;
		std::cout << fuel << "\n";
	}
}