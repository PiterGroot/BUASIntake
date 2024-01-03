#include "TextManager.h"

TextManager* TextManager::instance = nullptr;

TextManager::TextManager()
{
	instance = this;

	CreateTextLabel("Fuel", "Fuel ", sf::Vector2f(0, 0), 24);
	CreateTextLabel("Distance", "Dist ", sf::Vector2f(0, 30), 24);
	CreateTextLabel("PlasticStatus", "Lake cleanup 100%", sf::Vector2f(0, 60), 24);
	CreateTextLabel("CurrentStorage", "Storage: 0/0", sf::Vector2f(0, 90), 24);
}

void TextManager::CreateTextLabel(sf::String labelId, sf::String initText, sf::Vector2f position, int fontSize, sf::Color textColor)
{
	textLabels.insert(std::pair<sf::String, TextLabelContainer*>(labelId, new TextLabelContainer(initText, position, fontSize, textColor)));
}

void TextManager::UpdateTextLabel(sf::String labelId, sf::String newText) 
{
	if (textLabels[labelId] == nullptr) {
		std::cout << "\nCouldn't update text label of id" << labelId.toAnsiString() << "! Forgot to initialize it?" << "\n";
		return;
	}

	textLabels[labelId]->UpdateText(newText);
}

TextManager::TextLabelContainer* TextManager::GetTextlabel(sf::String labelId)
{
	if (textLabels[labelId] == nullptr) {
		std::cout << "\nCouldn't return text label of id" << labelId.toAnsiString() << "! Forgot to initialize it?" << "\n";
		return NULL;
	}
	
	return textLabels[labelId];
}

void TextManager::Draw(sf::RenderWindow* window)
{
	for (const auto& labelPair : TextManager::textLabels) 
	{
		window->draw(*labelPair.second->text);
	}
}
