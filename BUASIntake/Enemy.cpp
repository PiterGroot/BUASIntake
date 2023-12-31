#include "Enemy.h"

Enemy::Enemy(sf::String name, sf::String texture, sf::Vector2f position) : Collider(this, false)
{
	tag = ObjectTag::Enemy;
	InitializeGameobject(name, texture, position);
	Game::instance->updatingGameobjects.push_back(this);
}

void Enemy::OnUpdate(float deltaTime) 
{
	sf::Vector2f playerPosition = Game::instance->playerBoat->position;
	sf::Vector2f dir = playerPosition - position;

	moveDirection = normalized(dir);

	MoveGameObject(position += moveDirection * moveSpeed * deltaTime);
}