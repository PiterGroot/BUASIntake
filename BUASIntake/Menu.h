#pragma once
#include "SFML/Graphics.hpp"
#include <forward_list>
#include <iostream>

class Menu 
{
public:

	std::forward_list<sf::Sprite> menuButtons;

	Menu();
	virtual ~Menu();
	virtual void CreateButton(sf::Vector2f position, sf::String text);

private:
	sf::Texture buttonTexture;

};