#include "PlayerHome.h"

float waypointOffset = 70;

PlayerHome::PlayerHome(sf::String name, sf::String texture, sf::Vector2f position) : Collider(this, false)
{
	sf::Vector2f wayPointPosition = sf::Vector2f(position.x, position.y - waypointOffset);
	Waypoint* waypoint = new Waypoint("BaseWaypoint", "Textures/waypoint.png", wayPointPosition, sf::Color::Green);

	tag = ObjectTag::PlayerHome;
	objectSprite.setScale(sf::Vector2f(6, 6));
	InitializeGameobject(name, texture, position, false);
}
