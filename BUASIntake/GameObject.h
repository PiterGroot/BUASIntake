#pragma once
#include "SFML/Graphics.hpp"
#include "vec2.hpp"

class GameObject 
{
public:
	sf::String name;
	sf::Texture objectTexture;
	sf::Sprite objectSprite;
	sf::Vector2f position;

	void InitializeGameobject(sf::String name, sf::String texturePath, sf::Vector2f position, bool isHudObject = false);
	void MoveGameObject(sf::Vector2f newPosition);

	GameObject* GetGameObject() { return this; }
};