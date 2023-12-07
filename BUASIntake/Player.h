#pragma once
#include <SFML/System/Vector2.hpp>
using namespace sf;


class Player
{
private:
	float moveSpeed = 350;
	float fuel = 250;

	Vector2f position;
	Vector2f origin;

public:
	void Testje();
};

