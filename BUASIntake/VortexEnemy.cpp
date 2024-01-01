#include "VortexEnemy.h"

float hurricaneMoveSpeed = 100;
float rotationSpeed = 300;

VortexEnemy::VortexEnemy(sf::String name, sf::String texture, sf::Vector2f position) : Enemy(name, texture, position)
{
	tag = ObjectTag::Hurricane;
	moveSpeed = hurricaneMoveSpeed;
	objectSprite.setScale(sf::Vector2f(2, 2));
	moveDirection = normalized(GetPlayerDirection());
}

void VortexEnemy::OnUpdate(float deltaTime)
{
	objectSprite.rotate(deltaTime * rotationSpeed);
	MoveGameObject(position += moveDirection * moveSpeed * deltaTime);
}