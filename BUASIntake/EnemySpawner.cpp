#include "EnemySpawner.h"
#include "VortexEnemy.h"
#include "KrakenEnemy.h"

int currentWave = 0;
float waveTimer = 10;

float secondsBetweenWaves = 20;
float minSecondsBetweenWaves = 10;
float timeBetweenWavesDecrement = .5f;

int waveEnemyIncrementThreshold = 15;
int currrentEnemiesToSpawn = 3;

EnemySpawner::EnemySpawner() 
{
	possibleEnemies.push_back(ObjectTag::Kraken);
	possibleEnemies.push_back(ObjectTag::Vortex);

	InitializeGameobject("EnemySpawner", "", sf::Vector2f(0, 0));
	Game::instance->updatingGameobjects.push_back(this);
}

void EnemySpawner::OnUpdate(float deltaTime) 
{
	waveTimer += deltaTime;

	if (waveTimer >= secondsBetweenWaves) {
		waveTimer = 0;

		if(secondsBetweenWaves > minSecondsBetweenWaves) secondsBetweenWaves -= timeBetweenWavesDecrement;
		if (secondsBetweenWaves <= waveEnemyIncrementThreshold) currrentEnemiesToSpawn++;

		currentWave++;
		SpawnEnemyWave(Game::instance->playerBoat->position);
	}
}

void EnemySpawner::SpawnEnemyWave(sf::Vector2f position) 
{
	srand(time(0));
	for (int i = 0; i < currrentEnemiesToSpawn; i++)
	{
		SpawnRandomEnemy(RandomPointOnCircleEdge(position.x, position.y, 600));
	}
}

void EnemySpawner::SpawnRandomEnemy(sf::Vector2f spawnPosition) 
{
	std::cout << spawnPosition.x << " " << spawnPosition.y << "\n";

	int randomEnemyIndex = rand() % possibleEnemies.size();
	ObjectTag enemyTag = possibleEnemies[randomEnemyIndex];

	switch (enemyTag)
	{
		case ObjectTag::Kraken:
			new KrakenEnemy("KrakenEnemy", "Textures/Enemy/tentacle.png", sf::Vector2f(spawnPosition));
			break;
		case ObjectTag::Vortex:
			new VortexEnemy("VortexEnemy", "Textures/Enemy/vortex.png", sf::Vector2f(spawnPosition));
			break;
	}
}