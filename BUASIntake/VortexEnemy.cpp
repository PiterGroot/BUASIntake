#include "VortexEnemy.h"

float hurricaneMoveSpeed = 100;
float rotationSpeed = 300;

VortexEnemy::VortexEnemy(sf::String name, sf::String texture, sf::Vector2f position) : Enemy(name, texture, position)
{
	tag = ObjectTag::Vortex;
	moveSpeed = hurricaneMoveSpeed;
	objectSprite.setScale(sf::Vector2f(2, 2));
	moveDirection = normalized(GetPlayerDirection());
}

void VortexEnemy::OnUpdate(float deltaTime)
{
	sf::Vector2f playerDirection = GetPlayerDirection();
	float distance = magnitude(playerDirection);
	
	if (distance >= despawnRange) 
	{
		HandleDespawn(deltaTime);
		return;
	}

	despawnTimer = 0;
	objectSprite.rotate(deltaTime * rotationSpeed);
	MoveGameObject(position += moveDirection * moveSpeed * deltaTime);
}

void VortexEnemy::HandleDespawn(float deltaTime) 
{
	despawnTimer += deltaTime;
	if (despawnTimer >= despawnTime) {
		Game::instance->activeColliders.remove(this);
		Game::instance->objectsToDelete.push_back(this);
	}
}