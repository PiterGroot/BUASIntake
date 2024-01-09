#pragma once
#include "../Framework/GameObject.h"
#include "../Framework/Collider.h"

class PlayerHome : public GameObject, public Collider
{
public:
	PlayerHome(sf::String name, sf::String texture, sf::Vector2f position);

	bool DepositWaste(int amount);
	void OnUpdate(float deltaTime) override;
	bool isChoosingUpgrade = false;

private:
	void TogglePowerupScreen();

	GameObject* powerupScreen = nullptr;
	int lastProgress = 0;
};

