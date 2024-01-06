#pragma once

#include "GameObject.h"
#include "Enemy.h"
#include <list>

class EnemySpawner : private GameObject
{
public:
	EnemySpawner();

private:
	void OnUpdate(float deltaTime) override;
	void SpawnRandomEnemy(sf::Vector2f position);

	std::list<ObjectTag> possibleEnemies;
};