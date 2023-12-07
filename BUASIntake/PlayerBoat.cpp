#include "PlayerBoat.h"

#pragma region MyRegion

float startFuelAmount = 250;
float defaultMoveSpeed = 350;
String boatTextureFile = "Textures/circle.png";

PlayerBoat::PlayerBoat()
{
	fuel = startFuelAmount;
	moveSpeed = defaultMoveSpeed;

	boatTexture.loadFromFile("Textures/circle.png");
	boatSprite.setTexture(boatTexture);
	boatSprite.setOrigin(Vector2f(32, 32));
}

PlayerBoat::~PlayerBoat()
{
}

#pragma endregion


void PlayerBoat::MovePlayer(Vector2f newPosition) 
{
	this->position += newPosition;
	boatSprite.setPosition(this->position);
}