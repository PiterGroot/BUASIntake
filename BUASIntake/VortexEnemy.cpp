#include "VortexEnemy.h"

float hurricaneMoveSpeed = 100;
float rotationSpeed = 300;

VortexEnemy::VortexEnemy(sf::String name, sf::String texture, sf::Vector2f position) : Enemy(name, texture, position)
{
	tag = ObjectTag::Vortex;
	moveSpeed = hurricaneMoveSpeed;
	objectSprite.setScale(sf::Vector2f(2, 2));
	moveDirection = normalized(GetPlayerDirection()); //only get player direction on spawn
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

	//move towards current player position and simple rotation "animation"
	objectSprite.rotate(deltaTime * rotationSpeed);
	MoveGameObject(position += moveDirection * moveSpeed * deltaTime);
}

//Despawn if enemy is to far away from player
void VortexEnemy::HandleDespawn(float deltaTime) 
{
	despawnTimer += deltaTime;
	if (despawnTimer >= despawnTime) { //despawning
		Game::instance->activeColliders.remove(this);
		Game::instance->objectsToDelete.push_back(this);
	}
}