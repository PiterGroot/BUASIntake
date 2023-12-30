#include "PlayerBoat.h"
#include "Game.h"

//forward declaration update methods
void UpdateFuelLabel(float currentFuel);
void UpdateDistanceLabel(sf::Vector2f currentPosition);

float startFuelAmount = 1000;
float defaultMoveSpeed = 250;

float activeFuelConsumption = 25;
float passiveFuelConsumption = 1;

bool cleanupPressed = false;
bool isInsidePickup = false;
int randCleanupTries = 0;

// Call the Collider constructor
PlayerBoat::PlayerBoat() : Collider(this, false) {}

void PlayerBoat::InitializePlayer(sf::Vector2f spawnPosition) 
{ 
	//initialize player stats
	fuel = startFuelAmount;
	moveSpeed = defaultMoveSpeed;
	
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
	currentMoveDir = GetMovementDirection();

	if (currentMoveDir != sf::Vector2f(0, 0))
		objectSprite.setTexture(getDirectionalSprite[currentMoveDir]);

	UpdateFuelLabel(fuel);
	UpdateDistanceLabel(position);

	MovePlayer(normalized(currentMoveDir) * moveSpeed, deltaTime);
}

void PlayerBoat::OnCollision(Collider& other) 
{
	if (other.GetObject()->tag == GameObject::ObjectTag::Pickup)
	{
		if (!isInsidePickup)
			randCleanupTries = std::rand() % 3 + 1;

		isInsidePickup = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && cleanupPressed) {
			randCleanupTries--;

			AudioManager::instance->PlaySound(AudioManager::SoundTypes::Cleanup);
			std::cout << "cleanup" << "\n";
			cleanupPressed = false;
		}
		if (sf::Event::KeyReleased) {
			if (Game::instance->GetWindowEvent()->key.code == sf::Keyboard::E) {
				cleanupPressed = true;
			}
		}

		if (randCleanupTries == 0) {
			isInsidePickup = false;

			std::cout << "Player collided with pickup!" << "\n";
			AudioManager::instance->PlaySound(AudioManager::SoundTypes::Pickup);

			Game::instance->activeColliders.remove(&other);
			Game::instance->objectsToDelete.push_back(other.GetObject());
		}
	}
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