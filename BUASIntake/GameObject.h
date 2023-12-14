#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

class GameObject 
{
public:
	sf::Texture objectTexture;
	sf::Sprite objectSprite;
	sf::Vector2f position;
	
	void Initialize(sf::String texturePath, sf::Vector2f origin)
	{
		objectTexture.loadFromFile(texturePath);
		objectSprite.setTexture(objectTexture);
		objectSprite.setOrigin(origin);

		Game::gameobjects.push_back(&objectSprite);
	}
};