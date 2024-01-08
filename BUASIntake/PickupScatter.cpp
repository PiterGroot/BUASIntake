#include "PickupScatter.h"
#include "Game.h"

float spawnRange = 5000;
float randomSpriteScaler = .4f;

//Randomly scatter pickups inside a circular shape
PickupScatter::PickupScatter(int pickupAmount) 
{
	srand(time(0)); //random seed based on current time
	for (int i = 0; i < pickupAmount; i++)
	{
		//spawn pickup on random point
		sf::Vector2f randPoint = RandomPointInCircle(0, 0, spawnRange);
		BoxCollider* collider = new BoxCollider("Pickup " + i, "Textures/Other/trash.png", randPoint, true);
		collider->objectSprite.setRotation(rand() % 360); //give pickup random rotation

		//randomly scale pickup sprite a little bit
		float randomScaler = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / randomSpriteScaler));
		collider->objectSprite.setScale(sf::Vector2f(1, 1) * randomScaler);
		
		Game::instance->pickups.push_back(collider);
	}
}