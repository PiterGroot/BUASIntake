#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Graphics/Text.hpp"

#include <iostream>
#include <map>

class TextManager
{
public:
	struct TextLabelContainer 
	{
		bool isStatic = false;
		sf::Font* textFont = nullptr;
		sf::Text* text = nullptr;

		TextLabelContainer(sf::String initText, sf::Vector2f position, int fontSize = 24, sf::Color textColor = sf::Color::Black, bool isStatic = false) {
			textFont = new sf::Font();
			textFont->setSmooth(false);
			
			if (textFont->loadFromFile("Resources/Font/VCR_OSD_MONO_1.001.ttf"))
			{
				text = new sf::Text();
				text->setFont(*textFont);
				
				text->setFillColor(textColor);
				text->setPosition(position);

				text->setStyle(sf::Text::Bold);
				text->setCharacterSize(fontSize);
				text->setString(initText);

				this->isStatic = isStatic;
			}
		}

		void UpdateText(sf::String newText) 
		{
			text->setString(newText);
		}
	};

	TextManager();
	
	void CreateTextLabel(sf::String labelId, sf::String initText, sf::Vector2f position, int fontSize, sf::Color textColor = sf::Color::Black, bool isStatic = true);
	void UpdateTextLabel(sf::String labelId, sf::String newText);

	void Draw(sf::RenderWindow* window);
	void DrawInWorld(sf::RenderWindow* window);

	TextLabelContainer* GetTextlabel(sf::String labelId);

	static TextManager* instance;

private:
	std::map<sf::String, TextLabelContainer*> textLabels;
};

