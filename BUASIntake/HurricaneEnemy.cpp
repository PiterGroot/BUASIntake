#include "HurricaneEnemy.h"

float hurricaneMoveSpeed = 100;

HurricaneEnemy::HurricaneEnemy(sf::String name, sf::String texture, sf::Vector2f position) : Enemy(name, texture, position)
{
	tag = ObjectTag::Hurricane;
	moveSpeed = hurricaneMoveSpeed;
}

void HurricaneEnemy::OnUpdate(float deltaTime)
{
	moveDirection = GetPlayerDirection();
	MoveGameObject(position += moveDirection * moveSpeed * deltaTime);
}