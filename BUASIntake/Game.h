#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <list>

#include "CollisionManager.h"
#include "AudioManager.h"
#include "TextManager.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "PlayerBoat.h"
#include "Waypoint.h"
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
	sf::Font textFont;

	float deltaTime;
	float elapsedTime;

	void OnInitialize();
	void OnInitializeWindow();

public:
	Game();
	virtual ~Game();
	
	static Game* instance;
	PlayerBoat* playerBoat = nullptr;

	AudioManager* audioManager = nullptr;
	CollisionManager* collisionManager = nullptr;
	TextManager* textManager = nullptr;

	std::list<GameObject*> gameobjects;
	std::list<GameObject*> hudGameobjects;
	std::list<Collider*> activeColliders;
	std::list<GameObject*> updatingGameobjects;
	std::list<GameObject*> objectsToDelete;
	
	sf::Vector2f GetScreenCenter();
	const bool isWindowActive() const;

	sf::Event* GetWindowEvent();
	sf::View* GetCameraView();
	void OnUpdateWindowEvents();
	void OnUpdate(float deltaTime);
	void OnLateUpdate(float deltaTime);
	void OnRender();
};