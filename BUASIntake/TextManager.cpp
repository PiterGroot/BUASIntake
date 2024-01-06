#include "TextManager.h"
#include"Game.h";

TextManager* TextManager::instance = nullptr;

TextManager::TextManager()
{
	instance = this;

	CreateTextLabel("Fuel", "Fuel ", sf::Vector2f(0, 0), 24);
	CreateTextLabel("Distance", "Dist ", sf::Vector2f(0, 30), 24);
	CreateTextLabel("PlasticStatus", "Lake cleanup 100%", sf::Vector2f(0, 60), 24);
	CreateTextLabel("CurrentStorage", "Storage: 0/0", sf::Vector2f(0, 90), 24);

	int screenWidth = Game::instance->GetScreenSize().x;
	CreateTextLabel("GameTimer", "0.00", sf::Vector2f((screenWidth / 2) - 40, 0), 30, sf::Color::White);
}

//Helper method for easily creating text labels on the screen with a given string, position, fontsize and color
void TextManager::CreateTextLabel(sf::String labelId, sf::String initText, sf::Vector2f position, int fontSize, sf::Color textColor)
{
	textLabels.insert(std::pair<sf::String, TextLabelContainer*>(labelId, new TextLabelContainer(initText, position, fontSize, textColor)));
}

//Helper method for updating textlabels based on a label id
void TextManager::UpdateTextLabel(sf::String labelId, sf::String newText) 
{
	if (textLabels[labelId] == nullptr) { //check if label exist before trying to update it
		std::cout << "\nCouldn't update text label of id" << labelId.toAnsiString() << "! Forgot to initialize it?" << "\n";
		return;
	}

	textLabels[labelId]->UpdateText(newText);
}

//Returns a textlabel based on a label id
TextManager::TextLabelContainer* TextManager::GetTextlabel(sf::String labelId)
{
	if (textLabels[labelId] == nullptr) { //check if label exist before trying to return it
		std::cout << "\nCouldn't return text label of id" << labelId.toAnsiString() << "! Forgot to initialize it?" << "\n";
		return nullptr;
	}
	
	return textLabels[labelId];
}

//Draw all textlabels to the screen
void TextManager::Draw(sf::RenderWindow* window)
{
	for (const auto& labelPair : TextManager::textLabels) 
	{
		window->draw(*labelPair.second->text);
	}
}
