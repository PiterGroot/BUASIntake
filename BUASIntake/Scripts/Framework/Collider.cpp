#include "Collider.h"
#include <iostream>
#include "../Game.h"

Collider::Collider(GameObject* object, bool isTrigger) : object(object)
{
    isTriggerCollider = isTrigger;
    Game::instance->activeColliders.push_back(this);
}

//AABB collison check
bool Collider::CheckCollision(Collider& other, float pushBack)
{
    sf::Vector2f otherPosition = other.GetBodyPosition();
    sf::Vector2f otherHalfSize = other.GetHalfBodySize();

    sf::Vector2f thisPosition = GetBodyPosition();
    sf::Vector2f thisHalfSize = GetHalfBodySize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        AdjustPositions(other, sf::Vector2f(intersectX, intersectY), sf::Vector2f(deltaX, deltaY), pushBack);
        return true;
    }

    return false;
}

//Check if intersects overlap
void Collider::AdjustPositions(Collider& other, sf::Vector2f intersect, sf::Vector2f deltaPosition, float pushBack)
{
    if (isTriggerCollider || other.isTriggerCollider)
        return;

    pushBack = std::min(std::max(pushBack, 0.0f), 1.0f);

    if (intersect.x > intersect.y && deltaPosition.x > 0.0f)
        MoveBodies(other, intersect.x * (1.0f - pushBack), 0.0f, -intersect.x * pushBack, 0.0f);
    else if (intersect.x > intersect.y && deltaPosition.x <= 0.0f)
        MoveBodies(other, -intersect.x * (1.0f - pushBack), 0.0f, intersect.x * pushBack, 0.0f);
    else if (intersect.y > intersect.x && deltaPosition.y > 0.0f)
        MoveBodies(other, 0.0f, intersect.y * (1.0f - pushBack), 0.0f, -intersect.y * pushBack);
    else if (intersect.y > intersect.x && deltaPosition.y <= 0.0f)
        MoveBodies(other, 0.0f, -intersect.y * (1.0f - pushBack), 0.0f, intersect.y * pushBack);
}

//Push back objects based on initial pushback value
void Collider::MoveBodies(Collider& other, float thisDeltaX, float thisDeltaY, float otherDeltaX, float otherDeltaY)
{
    MoveBody(sf::Vector2f(thisDeltaX, thisDeltaY));
    other.MoveBody(sf::Vector2f(otherDeltaX, otherDeltaY));
}

//Actual move object
void Collider::MoveBody(sf::Vector2f deltaPosition)
{
    object->MoveGameObject(object->position += deltaPosition);
}

//Set if this collider should act as a trigger
void Collider::SetTrigger(bool trigger) 
{
    isTriggerCollider = trigger;
}

//Get current object position
sf::Vector2f Collider::GetBodyPosition() 
{
    return object->position;
}

//Get current object half size
sf::Vector2f Collider::GetHalfBodySize()
{
    return sf::Vector2f(object->objectTexture.getSize()) * .5f;
}

//Get reference to current gameobject
GameObject* Collider::GetObject() 
{
    return object;
}