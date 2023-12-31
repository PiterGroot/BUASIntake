#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include <functional>

class Collider
{
public:
    Collider(GameObject* object, bool isTrigger);

    bool CheckCollision(Collider& other, float pushBack);
    void SetTrigger(bool isTrigger) { isTriggerCollider = isTrigger; }
    virtual void OnCollision(Collider& other) {};

    sf::Vector2f GetBodyPosition() { return object->position; }
    sf::Vector2f GetHalfBodySize() { return sf::Vector2f(object->objectTexture.getSize()) * .5f; };
    GameObject* GetObject() { return object; };

private:
    GameObject* object;
    bool isTriggerCollider = false;
    
    void MoveBodies(Collider& other, float thisDeltaX, float thisDeltaY, float otherDeltaX, float otherDeltaY);
    void MoveBody(sf::Vector2f deltaPosition) { object->MoveGameObject(object->position += deltaPosition); };
    void AdjustPositions(Collider& other, sf::Vector2f intersect, sf::Vector2f deltaPosition, float pushBack);
};