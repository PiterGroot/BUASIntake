#include "PlayerHome.h"
#include "Waypoint.h"

float waypointYOffset = 70;
float wasteFuelReward = 75;
int depositsNeededToPowerup = 10;

int lastProgress = 0;
GameObject* powerupScreen = nullptr;

PlayerHome::PlayerHome(sf::String name, sf::String texture, sf::Vector2f position) : Collider(this, false)
{
	sf::Vector2f screenCenter = Game::instance->GetScreenCenter();

	powerupScreen = new GameObject();
	powerupScreen->isActive = false;
	powerupScreen->InitializeGameobject("PowerupScreen", "Textures/Other/powerups.png", screenCenter, true);

	sf::Vector2f wayPointPosition = sf::Vector2f(position.x, position.y - waypointYOffset);
	Waypoint* waypoint = new Waypoint("BaseWaypoint", "Textures/Debug/waypoint.png", wayPointPosition, sf::Color::Green);

	BoxCollider* homeTriggerCollider = new BoxCollider("HomeTrigger", "Textures/Debug/boxcollider.png", position, true);
	homeTriggerCollider->tag = ObjectTag::PlayerHome;

	objectSprite.setScale(sf::Vector2f(6, 6));
	InitializeGameobject(name, texture, position, false);
}

//Returns true if player actually deposited anything
bool PlayerHome::DepositWaste(int amount) 
{
	if (amount <= 0)
		return false;

	std::cout << "deposit" << "\n";
	for (int i = 0; i < amount; i++)
	{
		float currentFuel = Game::instance->playerBoat->GetFuel();
		Game::instance->playerBoat->SetFuel(currentFuel + wasteFuelReward);
	}
	
	Game::instance->cleanedUpDebris += amount; //update cleanup amount for cleanup percentage label
	AudioManager::instance->PlaySound(AudioManager::SoundTypes::Deposit);

	int progress = Game::instance->cleanedUpDebris % depositsNeededToPowerup;
	TextManager::instance->UpdateTextLabel("PowerupCounter", std::to_string(progress) + "/10");
	
	if (progress < lastProgress) {
		Game::instance->enemySpawner->canUpdate = false;
		Game::instance->playerBoat->isActive = false;

		powerupScreen->isActive = true;
		std::cout << "Powerup" << "\n";
	}

	lastProgress = progress;
	return true;
}
