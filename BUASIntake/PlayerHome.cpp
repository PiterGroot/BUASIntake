#include "PlayerHome.h"
#include "Waypoint.h"

float waypointOffset = 70;

PlayerHome::PlayerHome(sf::String name, sf::String texture, sf::Vector2f position) : Collider(this, false)
{
	sf::Vector2f wayPointPosition = sf::Vector2f(position.x, position.y - waypointOffset);
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
	Game::instance->cleanedUpDebris += amount; //update cleanup amount for cleanup percentage label
	AudioManager::instance->PlaySound(AudioManager::SoundTypes::Deposit);

	return true;
}
