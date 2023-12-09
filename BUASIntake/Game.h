#pragma once

#include <SFML/Graphics.hpp>
#include "vec2.hpp"
using namespace sf;

class Game
{
private:
	RenderWindow* window;
	Event windowEvent;
	VideoMode videoMode;
	Color waterColor;

	Sprite testRockSprite;
	Texture testRockexture;

	View cameraView;
	View staticView;

	void OnInitialize();
	void OnInitializeWindow();


//constructor / destructors
public:
	float deltaTime;

	Game();
	virtual ~Game();

	const bool isWindowActive() const;

	void OnUpdateWindowEvents();
	void OnUpdate(float deltaTime);
	void OnRender();
};

