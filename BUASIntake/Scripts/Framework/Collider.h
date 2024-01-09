#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

class Collider
{
public:
    Collider(GameObject* object, bool isTrigger);
    bool CheckCollision(Collider& other, float pushBack);

    void SetTrigger(bool isTrigger);
    virtual void OnCollision(Collider& other) {};

    sf::Vector2f GetBodyPosition();
    sf::Vector2f GetHalfBodySize();
    GameObject* GetObject();

private:
    GameObject* object;
    bool isTriggerCollider = false;
    
    void MoveBody(sf::Vector2f deltaPosition);
    void MoveBodies(Collider& other, float thisDeltaX, float thisDeltaY, float otherDeltaX, float otherDeltaY);
    void AdjustPositions(Collider& other, sf::Vector2f intersect, sf::Vector2f deltaPosition, float pushBack);
};