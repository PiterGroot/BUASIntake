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
		Hurricane,
		Kraken
	};

	sf::String name;
	sf::Texture objectTexture;
	sf::Sprite objectSprite;
	sf::Vector2f position;

	ObjectTag tag = ObjectTag::Default;

	void MoveGameObject(sf::Vector2f newPosition);
	void InitializeGameobject(sf::String name, sf::String texturePath, sf::Vector2f position, bool isHudObject = false);
	virtual void OnUpdate(float deltaTime) {};
};