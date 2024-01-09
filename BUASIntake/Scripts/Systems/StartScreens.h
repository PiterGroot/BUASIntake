#pragma once
#include "../Framework/GameObject.h"
#include <vector>
#include <iostream>


class StartScreens : private GameObject
{
public:
	StartScreens(sf::Vector2f screenCenter);

private:
	void OnUpdate(float deltaTime) override;
	std::vector<GameObject> screens;
	
	int currentScreen = 0;
	int screenCount = 3;

	bool hasShownAllScreens = false;
};

