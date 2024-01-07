#pragma once

#include "GameObject.h"
#include "vec2.hpp"
#include "Enemy.h"
#include <vector>

class EnemySpawner : private GameObject
{
public:
	EnemySpawner();
	bool canUpdate = true;

private:
	void OnUpdate(float deltaTime) override;
	void SpawnEnemyWave(sf::Vector2f position);
	void SpawnRandomEnemy(sf::Vector2f spawnPosition);

	std::vector<ObjectTag> possibleEnemies;
};