#pragma once
#include"SFML/Graphics.hpp"
#include "GameObject.h"

class Collider
{
public:
	Collider(GameObject* object, bool isTrigger);

	bool CheckCollision(Collider& other, float pushBack);
	void MoveBodies(Collider& other, float thisDeltaX, float thisDeltaY, float otherDeltaX, float otherDeltaY);
	void SetTrigger(bool isTrigger) { isTriggerCollider = isTrigger; }
	void AdjustPositions(Collider& other, sf::Vector2f intersect, sf::Vector2f deltaPosition, float pushBack);

	void MoveBody(sf::Vector2f deltaPosition) { object->MoveGameObject(object->position += deltaPosition); };
	void OnCollision(Collider* collider);

	sf::Vector2f GetBodyPosition() { return object->position; }
	sf::Vector2f GetHalfBodySize() { return sf::Vector2f(object->objectTexture.getSize()) * .5f; };

	GameObject* GetObject() { return object; };

private:
	GameObject* object;
	//NOTE: trigger colliders are currently broken, need to determine if actually needed otherwise just remove it
	bool isTriggerCollider = false; 
};