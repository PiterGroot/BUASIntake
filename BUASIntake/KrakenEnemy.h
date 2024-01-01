#pragma once
#include "Enemy.h"
#include "Game.h"

class KrakenEnemy : public Enemy
{
public:
    KrakenEnemy(sf::String name, sf::String texture, sf::Vector2f position);
    void HandleDespawn(float deltaTime) override;

private:
    void OnUpdate(float deltaTime) override;
};
