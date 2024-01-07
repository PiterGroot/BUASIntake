#pragma once
#include "Enemy.h"
#include "Game.h"

class VortexEnemy : public Enemy
{
public:
    VortexEnemy(sf::String name, sf::String texture, sf::Vector2f position);

private:
    void OnUpdate(float deltaTime) override;
    void HandleDespawn(float deltaTime) override;

    float despawnRange = 800;
    float despawnTime = 10;
    float despawnTimer = 0;
};
