#include "Menu.h"
#include <SFML/System/Vector2.hpp>


Menu::Menu() 
{
	
}

Menu::~Menu()
{
}

void Menu::CreateButton(sf::Vector2f position, sf::String text)
{
	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;

	buttonTexture.loadFromFile("Textures/UI/button.png");
	buttonSprite.setOrigin(sf::Vector2f(buttonTexture.getSize().x / 2, buttonTexture.getSize().y / 2));
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setPosition(position);

	menuButtons.push_front({ buttonSprite });
}