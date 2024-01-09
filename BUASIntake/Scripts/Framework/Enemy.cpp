#include "Enemy.h"
#include "../Game.h"`

Enemy::Enemy(sf::String name, sf::String texture, sf::Vector2f position) : Collider(this, true)
{
	InitializeGameobject(name, texture, position);
	Game::instance->updatingGameobjects.push_back(this);
}

//Calculates and returns direction to the player
sf::Vector2f Enemy::GetPlayerDirection() 
{
	sf::Vector2f playerPosition = Game::instance->playerBoat->position;
	sf::Vector2f dir = playerPosition - position;

	return dir;
}

float Enemy::GetRandomScaler(float min, float max) 
{
	float randomSpeedScaler = static_cast<float>(std::rand()) / RAND_MAX;
	return randomSpeedScaler = min + randomSpeedScaler * (max - min);
}