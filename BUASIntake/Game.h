#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "vec2.hpp"
#include "PlayerBoat.h"
#include "GameObject.h"

class Game
{
private:
	std::list<GameObject*> objectsToDelete;

	sf::RenderWindow* window;
	sf::Event windowEvent;
	sf::VideoMode videoMode;
	sf::Color waterColor;

	sf::View cameraView;
	sf::View staticView;

	sf::RectangleShape waterShaderRect;

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
	
	std::list<GameObject*> gameobjects;
	std::list<GameObject*> hudGameobjects;
	
	sf::Vector2f GetScreenCenter();
	const bool isWindowActive() const;

	void PrintToConsole(sf::String message);
	void OnUpdateWindowEvents();
	void OnUpdate(float deltaTime);
	void OnLateUpdate(float deltaTime);
	void OnRender();
};