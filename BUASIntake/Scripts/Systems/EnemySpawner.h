#pragma once

#include "../Framework/GameObject.h"
#include "../Framework/vec2.hpp"
#include "../Framework/Enemy.h"
#include <vector>

class EnemySpawner : private GameObject
{
public:
	EnemySpawner();
	bool canUpdate = false;

private:
	void OnUpdate(float deltaTime) override;
	void SpawnEnemyWave(sf::Vector2f position);
	void SpawnRandomEnemy(sf::Vector2f spawnPosition);

	std::vector<ObjectTag> possibleEnemies;
};