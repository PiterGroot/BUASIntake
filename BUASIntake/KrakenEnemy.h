#pragma once
#include "Enemy.h"
#include "Game.h"

class KrakenEnemy : public Enemy
{
public:
    KrakenEnemy(sf::String name, sf::String texture, sf::Vector2f position);

private:
    void OnUpdate(float deltaTime) override;
    void HandleDespawn(float deltaTime) override;

    float despawnRange = 460;
    float despawnTime = 10;
    float despawnTimer = 0;
};
