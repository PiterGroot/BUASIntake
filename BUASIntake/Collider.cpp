#include "Collider.h"

Collider::Collider(GameObject& object) : object(object)
{
}

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

void Collider::AdjustPositions(Collider& other, sf::Vector2f intersect, sf::Vector2f deltaPosition, float pushBack)
{
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

void Collider::MoveBodies(Collider& other, float thisDeltaX, float thisDeltaY, float otherDeltaX, float otherDeltaY)
{
    if (isTriggerCollider)
        return;

    MoveBody(sf::Vector2f(thisDeltaX, thisDeltaY));
    other.MoveBody(sf::Vector2f(otherDeltaX, otherDeltaY));
}
