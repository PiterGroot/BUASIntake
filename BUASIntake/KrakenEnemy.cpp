#include "KrakenEnemy.h"
#include <iostream>

float krakenMoveSpeed = 125;
float passiveRange = 420;

KrakenEnemy::KrakenEnemy(sf::String name, sf::String texture, sf::Vector2f position) : Enemy(name, texture, position)
{
	tag = ObjectTag::Kraken;
	moveSpeed = krakenMoveSpeed;
	objectSprite.setScale(sf::Vector2f(2, 2));
}

void KrakenEnemy::OnUpdate(float deltaTime) 
{
	moveDirection = GetPlayerDirection();
	
	float distance = magnitude(moveDirection);
	if (distance <= .5f || distance >= passiveRange)
		return;

	MoveGameObject(position += normalized(moveDirection) * moveSpeed * deltaTime);
}