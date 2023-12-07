#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class PlayerBoat 
{
private:
	Vector2f playerOrigin = Vector2f(32, 32);
	Texture boatTexture;

public:
	float fuel;
	float moveSpeed;

	Vector2f position;
	Sprite boatSprite;
	
	PlayerBoat();
	virtual ~PlayerBoat();

	void MovePlayer(Vector2f newPosition, float deltaTime);
};
