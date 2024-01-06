#include "EnemySpawner.h"
#include "VortexEnemy.h"
#include "KrakenEnemy.h"

//KrakenEnemy* kraken = new KrakenEnemy("Kraken", "Textures/Enemy/tentacle.png", sf::Vector2f(0, -250));
//VortexEnemy* vortex = new VortexEnemy("Vortex", "Textures/Enemy/vortex.png", sf::Vector2f(0, 250));

EnemySpawner::EnemySpawner() 
{
	possibleEnemies.push_back(ObjectTag::Kraken);
	possibleEnemies.push_back(ObjectTag::Vortex);

	InitializeGameobject("EnemySpawner", "", sf::Vector2f(0, 0));
	Game::instance->updatingGameobjects.push_back(this);
}

void EnemySpawner::OnUpdate(float deltaTime) 
{

}

void EnemySpawner::SpawnRandomEnemy(sf::Vector2f position) 
{

}