#pragma once
#include <SFML/Graphics.hpp>
#include "vec2.hpp"
#include <iostream>
#include <list>

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event windowEvent;
	sf::VideoMode videoMode;
	sf::Color waterColor;

	sf::Sprite testRockSprite;
	sf::Texture testRockexture;

	sf::View cameraView;
	sf::View staticView;

	void OnInitialize();
	void OnInitializeWindow();


//constructor / destructors
public:
	static std::list<sf::Sprite*> gameobjects;
	float deltaTime;

	Game();
	virtual ~Game();

	const bool isWindowActive() const;

	void OnUpdateWindowEvents();
	void OnUpdate(float deltaTime);
	void OnRender();
};

