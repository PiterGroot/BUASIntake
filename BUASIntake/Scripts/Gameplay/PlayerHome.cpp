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

	//Initialize shop screen
	powerupScreen = new GameObject();
	powerupScreen->isActive = false;
	powerupScreen->InitializeGameobject("PowerupScreen", "Textures/Other/powerups.png", screenCenter, true);

	//Create home waypoint
	sf::Vector2f wayPointPosition = sf::Vector2f(position.x, position.y - waypointYOffset);
	Waypoint* waypoint = new Waypoint("BaseWaypoint", "Textures/Debug/waypoint.png", wayPointPosition, sf::Color::Green);

	//Initialize external trigger collider for depositing
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
		PlayerBoat* player = Game::instance->playerBoat;
		if (player->storageCapacity >= player->maxStorage) //check if player hasn't reached maxStorage yet
		{
			AudioManager::instance->PlaySound(AudioManager::SoundTypes::Deny);
			return;
		}

		player->storageCapacity += storageBonus;
		player->UpdateStorageLabel(player);
		TogglePowerupScreen();
	}
	if (InputManager::instance->GetKeyDown(sf::Keyboard::Key::Num3)) //choose tank upgrade
	{
		PlayerBoat* player = Game::instance->playerBoat;
		
		bool activeCheck = player->activeFuelConsumption <= player->minActiveFuelConsumption;
		bool passiveCheck = player->passiveFuelConsumption <= player->minPassiveFuelConsumption;
		
		if (activeCheck && passiveCheck) //checks if player hasn't reached min fuel consumption yet
		{
			AudioManager::instance->PlaySound(AudioManager::SoundTypes::Deny);
			return;
		}

		if(!activeCheck) Game::instance->playerBoat->activeFuelConsumption -= activeTankBonus;
		if(!passiveCheck) Game::instance->playerBoat->passiveFuelConsumption -= passiveTankBonus;
		TogglePowerupScreen();
	}
}

//Returns true if player actually deposited anything
bool PlayerHome::DepositWaste(int amount) 
{
	if (amount <= 0)
		return false;
	
	std::cout << "deposit" << "\n";
	for (int i = 0; i < amount; i++) //give player fuel for each deposit
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

	Game::instance->enemySpawner->canUpdate = !isChoosingUpgrade; //toggle enemy spawner
	Game::instance->playerBoat->isActive = !isChoosingUpgrade;//toggle player updates

	powerupScreen->isActive = isChoosingUpgrade; //toggle shop screen
}