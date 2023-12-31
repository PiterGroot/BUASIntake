#include "Enemy.h"
#include "Game.h"`

Enemy::Enemy(sf::String name, sf::String texture, sf::Vector2f position) : Collider(this, false)
{
	InitializeGameobject(name, texture, position);
	Game::instance->updatingGameobjects.push_back(this);
}

sf::Vector2f Enemy::GetPlayerDirection() 
{
	sf::Vector2f playerPosition = Game::instance->playerBoat->position;
	sf::Vector2f dir = playerPosition - position;

	return normalized(dir);
}