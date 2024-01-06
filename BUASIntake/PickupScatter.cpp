#include "PickupScatter.h"

float spawnRange = 5000;
float randomSpriteScaler = .4f;

//Randomly scatter pickups inside a circular shape
PickupScatter::PickupScatter(int pickupAmount) 
{
	for (int i = 0; i < pickupAmount; i++)
	{
		sf::Vector2f randPoint = RandomPointInCircle(0, 0, spawnRange);
		BoxCollider* collider = new BoxCollider("Pickup " + i, "Textures/Other/trash.png", randPoint, true);
		collider->objectSprite.setRotation(rand() % 360);

		float randomScaler = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / randomSpriteScaler));
		collider->objectSprite.setScale(sf::Vector2f(1, 1) * randomScaler);
	}
}