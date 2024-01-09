#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <list>

#include "Managers/CollisionManager.h"
#include "Systems/PickupScatter.h"
#include "Managers/InputManager.h"
#include "Managers/AudioManager.h"
#include "Framework/BoxCollider.h"
#include "Systems/StartScreens.h"
#include "Systems/EnemySpawner.h"
#include "Managers/TextManager.h"
#include "Framework/GameObject.h"
#include "Gameplay/PlayerBoat.h"
#include "Gameplay/PlayerHome.h"
#include "Framework/vec2.hpp"

class Game
{
public:
	Game();
	virtual ~Game();

	static Game* instance;

	bool isGameOver = false;
	bool isGameStarted = false;

	int initialPickupSpawnRange = 3000;
	int plasticDebris = 50;
	int cleanedUpDebris = 0;
	
	PlayerBoat* playerBoat = nullptr;
	PlayerHome* playerHome = nullptr;

	AudioManager* audioManager = nullptr;
	CollisionManager* collisionManager = nullptr;
	TextManager* textManager = nullptr;
	InputManager* inputManager = nullptr;
	EnemySpawner* enemySpawner = nullptr;

	std::list<GameObject*> pickups;
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

private:
	sf::RenderWindow* window = nullptr;
	sf::Image windowIcon;
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
	float startupTime;

	void OnInitialize();
	void OnInitializeWindow();
};