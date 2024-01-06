#include "PlayerBoat.h"
#include "Game.h"

//forward declaration update methods
void UpdateDistanceLabel(sf::Vector2f currentPosition);
void UpdateStorageLabel(PlayerBoat* player);
void UpdateFuelLabel(float currentFuel);
void UpdateCleanupLabel();

void OnCollideWithVortex(float currentFuel, PlayerBoat* player);
void OnCollideWithPickup(Collider& other, PlayerBoat* player);
void OnCollideWithKraken(Collider& other, float currentFuel, PlayerBoat* player);
bool TryCleanupDebris(float currentStorageAmount, float storageCapacity);

int startStorageAmount = 6;
float defaultMoveSpeed = 250;

float moveSpeedModifier = 1;
float enemyMoveSpeedModifier = .35f;

float startFuelAmount = 1000;
float wiggleFuelCost = 20;
int randWiggleTries = 0;

float activeFuelConsumption = 25;
float passiveFuelConsumption = 1;

bool isInsideKraken = false;
bool isInsidePickup = false;
int randCleanupTries = 0;

PlayerBoat::PlayerBoat(sf::Vector2f spawnPosition) : Collider(this, false) // call the Collider constructor
{
	//initialize player stats
	fuel = startFuelAmount;
	moveSpeed = defaultMoveSpeed;
	storageCapacity = startStorageAmount;

	//load necessary direction texturess
	upDirection.loadFromFile("Textures/Ship/ship1.png");
	upRightDirection.loadFromFile("Textures/Ship/ship15.png");
	rightDirection.loadFromFile("Textures/Ship/ship13.png");
	rightDownDirection.loadFromFile("Textures/Ship/ship11.png");
	downDirection.loadFromFile("Textures/Ship/ship9.png");
	downLeftDirection.loadFromFile("Textures/Ship/ship7.png");
	leftDirection.loadFromFile("Textures/Ship/ship5.png");
	leftUpDirection.loadFromFile("Textures/Ship/ship3.png");

	getDirectionalSprite = {
		{ sf::Vector2f(0, -1), upDirection},
		{ sf::Vector2f(1, -1), upRightDirection},
		{ sf::Vector2f(1, 0), rightDirection},
		{ sf::Vector2f(1, 1), rightDownDirection},
		{ sf::Vector2f(0, 1), downDirection},
		{ sf::Vector2f(-1, 1), downLeftDirection},
		{ sf::Vector2f(-1, 0), leftDirection},
		{ sf::Vector2f(-1, -1), leftUpDirection}
	};

	objectSprite.setScale(sf::Vector2f(2, 2));
	GameObject::InitializeGameobject("Player", "Textures/Ship/ship1.png", spawnPosition);
	Game::instance->updatingGameobjects.push_back(this);
}

void PlayerBoat::MovePlayer(sf::Vector2f newPosition, float deltaTime)
{
	if (fuel <= 0.1f)
		return;

	sf::Vector2f currentPosition = position;
	MoveGameObject(position += newPosition * deltaTime);

	if (currentPosition != position) SetFuel(fuel - deltaTime * activeFuelConsumption);
	else SetFuel(fuel - deltaTime * passiveFuelConsumption);
}

void PlayerBoat::OnUpdate(float deltaTime)
{
	currentMoveDirection = GetMovementDirection();

	if (currentMoveDirection != sf::Vector2f(0, 0))
		objectSprite.setTexture(getDirectionalSprite[currentMoveDirection]);
	
	//Update UI info labelss
	UpdateFuelLabel(fuel);
	UpdateDistanceLabel(position);
	
	bool isInsideVortex = Game::instance->collisionManager->HasCollision(this, ObjectTag::Vortex);
	isInsideKraken = Game::instance->collisionManager->HasCollision(this, ObjectTag::Kraken);

	if (!isInsideVortex && !isInsideKraken) objectSprite.setRotation(0);

	moveSpeedModifier = isInsideKraken || isInsideVortex ? enemyMoveSpeedModifier : 1;
	MovePlayer(normalized(currentMoveDirection) * moveSpeed * moveSpeedModifier, deltaTime);
}

void PlayerBoat::SetFuel(float newFuel) 
{
	fuel = abs(fuel = newFuel);
}

void PlayerBoat::OnCollision(Collider& other) 
{
	if (other.GetObject()->tag == ObjectTag::Pickup)
		OnCollideWithPickup(other, this);
	
	if (other.GetObject()->tag == ObjectTag::Kraken) 
		OnCollideWithKraken(other, fuel, this);

	if (other.GetObject()->tag == ObjectTag::Vortex)
		OnCollideWithVortex(fuel, this);

	if (other.GetObject()->tag == ObjectTag::PlayerHome) 
	{
		if (InputManager::instance->GetKeyDown(sf::Keyboard::Key::E)) 
		{
			if (Game::instance->playerHome->DepositWaste(currentStorageAmount)) 
			{
				currentStorageAmount = 0;
				UpdateStorageLabel(this);
				UpdateCleanupLabel();
			}
		}
	}
}

#pragma region OnCollision methods

void OnCollideWithVortex(float currentFuel, PlayerBoat* player) 
{
	player->objectSprite.setRotation(rand() % 360);
	player->SetFuel(currentFuel - 1.5f);
}

void OnCollideWithKraken(Collider& other, float currentFuel, PlayerBoat* player)
{
	if (!isInsideKraken)
		randWiggleTries = std::rand() % 10 + 3;

	if (InputManager::instance->GetKeyDown(sf::Keyboard::Key::E))
	{
		randWiggleTries--;
		player->SetFuel(currentFuel - wiggleFuelCost);

		int randomCleanUpSound = std::rand() % 3 + 2;
		AudioManager::instance->PlaySound(static_cast<AudioManager::SoundTypes>(randomCleanUpSound));
		player->objectSprite.setRotation(rand() % 360);
	}

	if (randWiggleTries == 0)
	{
		std::cout << "\nPlayer freed from kraken!" << "\n";
		InputManager::instance->Reset();
		player->objectSprite.setRotation(0);

		AudioManager::instance->PlaySound(AudioManager::SoundTypes::Kill_Kraken);

		Game::instance->activeColliders.remove(&other);
		Game::instance->objectsToDelete.push_back(other.GetObject());
	}
}

void OnCollideWithPickup(Collider& other, PlayerBoat* player)
{
	//Generate random number for cleanup tries when player collides the pickup for the first time
	if (!isInsidePickup)
		randCleanupTries = std::rand() % 5 + 1;

	isInsidePickup = true;

	if (TryCleanupDebris(player->currentStorageAmount, player->storageCapacity)) {
		std::cout << "cleanup" << "\n";

		//play random cleanup sound effect
		int randomCleanUpSound = std::rand() % 3 + 2;
		AudioManager::instance->PlaySound(static_cast<AudioManager::SoundTypes>(randomCleanUpSound));
	}

	if (randCleanupTries == 0) {
		std::cout << "\nPlayer pickedup debris!" << "\n";

		isInsidePickup = false;
		InputManager::instance->Reset();

		AudioManager::instance->PlaySound(AudioManager::SoundTypes::Pickup);
		player->currentStorageAmount++;

		UpdateStorageLabel(player);

		Game::instance->activeColliders.remove(&other);
		Game::instance->objectsToDelete.push_back(other.GetObject());
	}
}
#pragma endregion

//Cleanup "minigame" when floating ontop of debris
bool TryCleanupDebris(float currentStorageAmount, float storageCapacity) 
{
	if (InputManager::instance->GetKeyDown(sf::Keyboard::Space)) 
	{
		//Check if there is enough space in storage before picking up
		if (currentStorageAmount >= storageCapacity)
		{
			AudioManager::instance->PlaySound(AudioManager::SoundTypes::Deny);
			return false;
		}
		randCleanupTries--;
		return true;
	}
	return false;
}

//Update player storage label based on current storage
void UpdateStorageLabel(PlayerBoat* player) 
{
	sf::String storageText = std::to_string(player->currentStorageAmount) + "/" + std::to_string(startStorageAmount);
	TextManager::instance->UpdateTextLabel("CurrentStorage", "Storage " + storageText);
}

//Update cleanup label based on how dirty the lake is
void UpdateCleanupLabel() 
{
	float startDebris = Game::instance->plasticDebris;
	float cleanedUp = Game::instance->cleanedUpDebris;
	float dirtyPerc = 100 - ((cleanedUp / startDebris) * 100);

	std::ostringstream cleanupStringStream;
	cleanupStringStream << std::fixed << std::setprecision(2) << dirtyPerc;
	TextManager::instance->UpdateTextLabel("PlasticStatus", "Lake cleanup " + cleanupStringStream.str() + " %");
}

//Update fuel text label
void UpdateFuelLabel(float currentFuel) {
	std::ostringstream fuelStringStream;
	fuelStringStream << std::fixed << std::setprecision(2) << currentFuel;
	TextManager::instance->UpdateTextLabel("Fuel", "Fuel " + fuelStringStream.str());
}

//Update distance text label
void UpdateDistanceLabel(sf::Vector2f currentPosition) 
{
	std::ostringstream distanceStream;
	sf::Vector2f diff = currentPosition - sf::Vector2f(-300, 65); //hardcoded testbase coords for testing
	float distance = magnitude(diff) / 100;

	distanceStream << std::fixed << std::setprecision(2) << distance;
	TextManager::instance->UpdateTextLabel("Distance", "Distance " + distanceStream.str() + " m");
}

//Get movement direction
sf::Vector2f PlayerBoat::GetMovementDirection() {
	sf::Vector2f direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		direction += sf::Vector2f(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		direction += sf::Vector2f(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		direction -= sf::Vector2f(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		direction += sf::Vector2f(1, 0);
	}

	return direction;
}