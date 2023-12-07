#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class PlayerBoat 
{
private:
	Texture boatTexture;

public:
	float fuel;
	float moveSpeed;

	Vector2f position;
	Sprite boatSprite;
	
	PlayerBoat();
	virtual ~PlayerBoat();

	void MovePlayer(Vector2f newPosition);
};
