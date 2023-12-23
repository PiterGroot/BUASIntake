#pragma once
#include "GameObject.h"
#include"SFML/Graphics.hpp"

class Collider
{
public:
	Collider(GameObject& object);

	void SetTrigger(bool isTrigger) { isTriggerCollider = isTrigger; }

	bool CheckCollision(Collider& other, float pushBack);
	void MoveBody(sf::Vector2f deltaPosition) { object.MoveGameObject(object.position += deltaPosition); }
	void MoveBodies(Collider& other, float thisDeltaX, float thisDeltaY, float otherDeltaX, float otherDeltaY);
	void AdjustPositions(Collider& other, sf::Vector2f intersect, sf::Vector2f deltaPosition, float pushBack);

	sf::Vector2f GetBodyPosition() { return object.position; }
	sf::Vector2f GetHalfBodySize() { return sf::Vector2f(object.objectTexture.getSize()) * .5f; }

private:
	GameObject& object;
	bool isTriggerCollider = false;
};

