#pragma once
#include "Enemy.h"

class VortexEnemy : public Enemy
{
public:
    VortexEnemy(sf::String name, sf::String texture, sf::Vector2f position);

private:
    void OnUpdate(float deltaTime) override;
};
