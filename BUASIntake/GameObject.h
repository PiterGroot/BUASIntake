#pragma once
#include "SFML/Graphics.hpp"

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
	}
};