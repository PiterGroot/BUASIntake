#include "PlayerHome.h"
#include "Waypoint.h"

float waypointYOffset = 70;
float wasteFuelReward = 75;

int moveSpeedBonus = 10;
int storageBonus = 1;
int activeTankBonus = 2;
int passiveTankBonus = 0.05f;

int depositsNeededToPowerup = 10;

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
	Game::instance->updatingGameobjects.push_back(this);
}

void PlayerHome::OnUpdate(float deltaTime) 
{
	if (!isChoosingUpgrade)
		return;

	if (InputManager::instance->GetKeyDown(sf::Keyboard::Key::Num1)) //choose speed upgrade
	{
		Game::instance->playerBoat->moveSpeed += moveSpeedBonus;
		TogglePowerupScreen();
	}
	if (InputManager::instance->GetKeyDown(sf::Keyboard::Key::Num2)) //choose storage upgrade
	{
		Game::instance->playerBoat->storageCapacity += storageBonus;
		Game::instance->playerBoat->UpdateStorageLabel(Game::instance->playerBoat);
		TogglePowerupScreen();
	}
	if (InputManager::instance->GetKeyDown(sf::Keyboard::Key::Num3)) //choose tank upgrade
	{
		Game::instance->playerBoat->activeFuelConsumption -= activeTankBonus;
		Game::instance->playerBoat->passiveFuelConsumption -= passiveTankBonus;
		TogglePowerupScreen();
	}
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

	//Update upgrade couter text label
	int progress = Game::instance->cleanedUpDebris % depositsNeededToPowerup;
	TextManager::instance->UpdateTextLabel("PowerupCounter", std::to_string(progress) + "/10");
	
	//Player has deposited enough to get a powerup
	if (progress < lastProgress) 
		TogglePowerupScreen();

	lastProgress = progress;
	return true;
}

//Toggle upgrade "shop" state
void PlayerHome::TogglePowerupScreen() 
{
	isChoosingUpgrade = !isChoosingUpgrade;

	if (isChoosingUpgrade) std::cout << "\nPowerup!" << "\n";
	if (!isChoosingUpgrade) AudioManager::instance->PlaySound(AudioManager::SoundTypes::Powerup);

	Game::instance->enemySpawner->canUpdate = !isChoosingUpgrade; //temporary disable enemy spawner while in shop
	Game::instance->playerBoat->isActive = !isChoosingUpgrade;

	powerupScreen->isActive = isChoosingUpgrade;
}