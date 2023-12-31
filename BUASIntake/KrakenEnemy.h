#pragma once
#include "Enemy.h"

class KrakenEnemy : public Enemy
{
public:
    KrakenEnemy(sf::String name, sf::String texture, sf::Vector2f position);

private:
    void OnUpdate(float deltaTime) override;
};
