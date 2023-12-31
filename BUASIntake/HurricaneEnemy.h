#pragma once
#include "Enemy.h"

class HurricaneEnemy : public Enemy
{
public:
    HurricaneEnemy(sf::String name, sf::String texture, sf::Vector2f position);

private:
    void OnUpdate(float deltaTime) override;
};
