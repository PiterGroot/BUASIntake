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
	if (!canUpdateTimer)
		return;

	waveTimer += deltaTime;

	//Before spawning a new enemy wave
	if (waveTimer >= secondsBetweenWaves) {
		waveTimer = 0;

		//while secondsBetweenWaves is bigger than the minSecondsBetweenWaves decrement
		//current timeBetweenWavesDecrement to increase difficulity while time is goin on
		if(secondsBetweenWaves > minSecondsBetweenWaves) secondsBetweenWaves -= timeBetweenWavesDecrement;
		//Also increment currrentEnemiesToSpawn when secondsBetweenWaves is less than waveEnemyIncrementThreshold 
		if (secondsBetweenWaves <= waveEnemyIncrementThreshold) currrentEnemiesToSpawn++;

		//Spawn new wave
		currentWave++;
		srand(time(0));
		SpawnEnemyWave(Game::instance->playerBoat->position);
	}
}

void EnemySpawner::SpawnEnemyWave(sf::Vector2f position) 
{
	for (int i = 0; i < currrentEnemiesToSpawn; i++)
	{
		SpawnRandomEnemy(RandomPointOnCircleEdge(position.x, position.y, 650));
	}
}

//Spawn a random enemy on given spawnPosition
void EnemySpawner::SpawnRandomEnemy(sf::Vector2f spawnPosition) 
{
	std::cout << spawnPosition.x << " " << spawnPosition.y << "\n";

	//Get random enemy ObjectTag index
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