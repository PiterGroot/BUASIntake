#include "PlayerBoat.h"
#include <iostream>
#include "Game.h"

Vector2f GetMovementDirection();

float startFuelAmount = 250;
float defaultMoveSpeed = 350;
float fuelConsumption = 25;

#pragma region Constructor / Deconstructor

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


void PlayerBoat::UpdatePlayer(float deltaTime)
{
	auto moveDir = GetMovementDirection();
	this->MovePlayer(moveDir * this->moveSpeed, deltaTime);
}

void PlayerBoat::MovePlayer(Vector2f newPosition, float deltaTime)
{
	if (fuel <= 0)
		return;

	Vector2f currentPosition = position;

	this->position += newPosition * deltaTime;
	boatSprite.setPosition(this->position);

	if (currentPosition != position) {
		fuel -= deltaTime * fuelConsumption;
		std::cout << fuel << "\n";
	}
}

//Get normalized movement direction
Vector2f GetMovementDirection() {
	Vector2f direction;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		direction += Vector2f(0, -1);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		direction += Vector2f(-1, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		direction -= Vector2f(0, -1);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		direction += Vector2f(1, 0);
	}

	return normalized(direction);
}