#pragma once
#include <SFML/Graphics.hpp>
#include "vec2.hpp"
#include <iostream>
#include <list>
#include "PlayerBoat.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event windowEvent;
	sf::VideoMode videoMode;
	sf::Color waterColor;

	sf::View cameraView;
	sf::View staticView;

	float deltaTime;
	float elapsedTime;

	void OnInitialize();
	void OnInitializeWindow();

//constructor / destructors
public:
	Game();
	virtual ~Game();
	
	static Game* instance;
	PlayerBoat* playerBoat;
	
	std::list<sf::Sprite*> gameobjects;
	std::list<sf::Sprite*> hudGameobjects;
	
	sf::Vector2f GetScreenCenter();
	const bool isWindowActive() const;

	void PrintToConsole(sf::String message);
	void OnUpdateWindowEvents();
	void OnUpdate(float deltaTime);
	void OnRender();
};

