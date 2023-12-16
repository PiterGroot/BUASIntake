#pragma once
#include "SFML/Graphics.hpp"
#include "vec2.hpp"

class GameObject 
{
public:
	sf::Texture objectTexture;
	sf::Sprite objectSprite;
	sf::Vector2f position;
	
	void InitializeGameobject(sf::String texturePath, sf::Vector2f origin, bool isHudObject = false);
};