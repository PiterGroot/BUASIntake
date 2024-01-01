#pragma once
#include "GameObject.h"
#include "Collider.h"

class Enemy : public GameObject, public Collider
{
public:
    Enemy(sf::String name, sf::String texture, sf::Vector2f position);

    virtual void OnUpdate(float deltaTime) override = 0;
    sf::Vector2f GetPlayerDirection();

protected:
    float moveSpeed = 100;
    sf::Vector2f moveDirection;
};