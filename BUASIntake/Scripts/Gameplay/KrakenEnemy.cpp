#include "KrakenEnemy.h"

float krakenMoveSpeed = 125;

KrakenEnemy::KrakenEnemy(sf::String name, sf::String texture, sf::Vector2f position) : Enemy(name, texture, position)
{
	tag = ObjectTag::Kraken;

	moveSpeed = krakenMoveSpeed * GetRandomScaler(.8f, 1.25f);
	objectSprite.setScale(sf::Vector2f(2, 2));
}

void KrakenEnemy::OnUpdate(float deltaTime) 
{
	if (!Game::instance->enemySpawner->canUpdate)
		return;

	moveDirection = GetPlayerDirection();
	float distance = magnitude(moveDirection);
	
	if (distance >= despawnRange) 
	{
		HandleDespawn(deltaTime);
		return;
	}

	despawnTimer = 0;
	if (distance <= .5f) //sit still when kraken is approximately on player to prevent visible jitter
		return;

	//move towards current player position
	MoveGameObject(position += normalized(moveDirection) * moveSpeed * deltaTime);
}

//Despawn if enemy is to far away from player
void KrakenEnemy::HandleDespawn(float deltaTime) 
{
	despawnTimer += deltaTime;
	if (despawnTimer >= despawnTime) { //despawning
		Game::instance->activeColliders.remove(this);
		Game::instance->objectsToDelete.push_back(this);
	}
}