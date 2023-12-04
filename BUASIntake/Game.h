#pragma once

#include <SFML/Graphics.hpp>
#include "vec2.hpp"
using namespace sf;

class Game
{
private:
	struct PlayerBoat
	{
		Vector2f position;
		float moveSpeed = 350;
		Vector2f origin = Vector2f(32, 32);
	};

	RenderWindow* window;
	Event windowEvent;
	VideoMode videoMode;
	Color waterColor;

	Sprite boatSprite;
	Texture boatTexture;

	Sprite testRockSprite;
	Texture testRockexture;

	PlayerBoat playerBoat;
	View view;

	Clock clock;
	float deltaTime;

	void OnInitialize();
	void OnInitializeWindow();


//constructor / destructors
public:
	Game();
		virtual ~Game();

		const bool isWindowActive() const;

		void OnUpdateWindowEvents();
		void OnUpdate(float deltaTime);
		void OnRender();
};

