#include "KrakenEnemy.h"

float krakenMoveSpeed = 125;
float passiveRange = 460;

float despawnTime = 10;
float despawnTimer = 0;

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
	if (distance >= passiveRange) {
		HandleDespawn(deltaTime);
		return;
	}

	despawnTimer = 0;
	if (distance <= .5f)
		return;

	MoveGameObject(position += normalized(moveDirection) * moveSpeed * deltaTime);
}

void KrakenEnemy::HandleDespawn(float deltaTime) 
{
	despawnTimer += deltaTime;
	if (despawnTimer >= despawnTime) {
		Game::instance->activeColliders.remove(this);
		Game::instance->objectsToDelete.push_back(this);
	}
}