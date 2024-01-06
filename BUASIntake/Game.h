#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <list>

#include "CollisionManager.h"
#include "EnemySpawner.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "TextManager.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "PlayerBoat.h"
#include "PlayerHome.h"
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

	sf::Shader waterShader;
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

	int plasticDebris = 300;
	int cleanedUpDebris = 0;
	
	PlayerBoat* playerBoat = nullptr;
	PlayerHome* playerHome = nullptr;

	AudioManager* audioManager = nullptr;
	CollisionManager* collisionManager = nullptr;
	TextManager* textManager = nullptr;
	InputManager* inputManager = nullptr;
	EnemySpawner* enemySpawner = nullptr;

	std::list<GameObject*> gameobjects;
	std::list<GameObject*> hudGameobjects;
	std::list<Collider*> activeColliders;
	std::list<GameObject*> updatingGameobjects;
	std::list<GameObject*> objectsToDelete;
	
	const bool isWindowActive() const;

	sf::Vector2f GetScreenCenter();
	sf::Event* GetWindowEvent();
	sf::View* GetCameraView();
	sf::Vector2u GetScreenSize();

	void OnUpdateWindowEvents();
	void OnUpdate(float deltaTime);
	void OnLateUpdate(float deltaTime);
	void OnRender();
};