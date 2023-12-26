#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "GameObject.h"
#include "PlayerBoat.h"
#include "vec2.hpp"

class Game
{
private:

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
	
	std::list<GameObject*> objectsToDelete;
	std::list<GameObject*> gameobjects;
	std::list<GameObject*> hudGameobjects;
	std::list<Collider*> activeColliders;
	
	sf::Vector2f GetScreenCenter();
	const bool isWindowActive() const;

	void OnUpdateWindowEvents();
	void OnUpdate(float deltaTime);
	void OnLateUpdate(float deltaTime);
	void OnRender();
};