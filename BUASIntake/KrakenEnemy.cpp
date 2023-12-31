#include "KrakenEnemy.h"

float krakenMoveSpeed = 125;

KrakenEnemy::KrakenEnemy(sf::String name, sf::String texture, sf::Vector2f position) : Enemy(name, texture, position)
{
	tag = ObjectTag::Kraken;
	moveSpeed = krakenMoveSpeed;
	moveDirection = GetPlayerDirection();
}

void KrakenEnemy::OnUpdate(float deltaTime) 
{
	MoveGameObject(position += moveDirection * moveSpeed * deltaTime);
}