#include "PlayerBoat.h"
#include "Game.h"

//forward declaration update methods
void UpdateFuelLabel(float currentFuel);
void UpdateDistanceLabel(sf::Vector2f currentPosition);
void UpdateCleanupLabel();

bool TryCleanupDebris(float currentStorageAmount, float storageCapacity);

int startStorageAmount = 6;
float startFuelAmount = 1000;
float defaultMoveSpeed = 250;

float activeFuelConsumption = 25;
float passiveFuelConsumption = 1;

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
	if (fuel <= 0)
		return;

	sf::Vector2f currentPosition = position;
	MoveGameObject(position += newPosition * deltaTime);

	if (currentPosition != position) fuel -= deltaTime * activeFuelConsumption;
	else fuel -= deltaTime * passiveFuelConsumption;
}

void PlayerBoat::OnUpdate(float deltaTime)
{
	currentMoveDirection = GetMovementDirection();

	if (currentMoveDirection != sf::Vector2f(0, 0))
		objectSprite.setTexture(getDirectionalSprite[currentMoveDirection]);
	
	//Update UI info labelss
	UpdateFuelLabel(fuel);
	UpdateDistanceLabel(position);
	
	MovePlayer(normalized(currentMoveDirection) * moveSpeed, deltaTime);
}

void PlayerBoat::OnCollision(Collider& other) 
{
	if (other.GetObject()->tag == ObjectTag::Pickup)
	{
		//Generate random number for cleanup tries when player collides the pickup for the first time
		if (!isInsidePickup)
			randCleanupTries = std::rand() % 5 + 1;

		isInsidePickup = true;

		if (TryCleanupDebris(currentStorageAmount, storageCapacity)) {
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
			currentStorageAmount++;

			sf::String storageText = std::to_string(currentStorageAmount) + "/" + std::to_string(startStorageAmount);
			TextManager::instance->UpdateTextLabel("CurrentStorage", "Storage " + storageText);

			UpdateCleanupLabel();

			Game::instance->activeColliders.remove(&other);
			Game::instance->objectsToDelete.push_back(other.GetObject());
		}
	}
}

//Cleanup "minigame" when floating ontop of debris
bool TryCleanupDebris(float currentStorageAmount, float storageCapacity) 
{
	if (InputManager::instance->GetKeyDown(sf::Keyboard::E)) 
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