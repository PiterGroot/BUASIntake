#pragma once
#include "SFML/Graphics.hpp"
#include "vec2.hpp"

class GameObject 
{
public:
	enum ObjectTag
	{
		Default,
		Pickup,
		Vortex,
		Kraken,
		PlayerHome
	};

	sf::String name;
	sf::Texture objectTexture;
	sf::Sprite objectSprite;
	sf::Vector2f position;

	bool isActive = true;
	ObjectTag tag = ObjectTag::Default;

	void MoveGameObject(sf::Vector2f newPosition);
	virtual void OnUpdate(float deltaTime) {};
	void InitializeGameobject(sf::String name, sf::String texturePath, sf::Vector2f position, bool isHudObject = false);
};