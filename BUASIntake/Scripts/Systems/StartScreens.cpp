#include "StartScreens.h"
#include "../Game.h"

StartScreens::StartScreens(sf::Vector2f screenCenter)
{
	screens.resize(screenCount + 1);

	screens[0].InitializeGameobject("StartScreen", "Textures/Other/startscreen.png", screenCenter, true);

	screens[1].InitializeGameobject("TutorialScreen", "Textures/Other/tutorial.png", screenCenter, true);
	screens[1].isActive = false;

	screens[2].InitializeGameobject("Tutorial1Screen", "Textures/Other/tutorial1.png", screenCenter, true);
	screens[2].isActive = false;

	screens[3].InitializeGameobject("Tutorial2Screen", "Textures/Other/tutorial2.png", screenCenter, true);
	screens[3].isActive = false;

	Game::instance->updatingGameobjects.push_back(this);
}

void StartScreens::OnUpdate(float deltaTime) 
{
	if (hasShownAllScreens)
		return;

	if (InputManager::instance->GetKeyDown(sf::Keyboard::Key::Space)) {
		screens[currentScreen].isActive = false;
		currentScreen++;
		
		//play random "confirmation" sound
		int randomCleanUpSound = std::rand() % 3 + 2;
		AudioManager::instance->PlaySound(static_cast<AudioManager::SoundTypes>(randomCleanUpSound));

		//Start game
		if (currentScreen > screenCount) {
			Game::instance->isGameStarted = true;
			Game::instance->playerBoat->isActive = true;
			Game::instance->enemySpawner->canUpdate = true;

			hasShownAllScreens = true;
			Game::instance->updatingGameobjects.push_back(Game::instance->playerBoat);
			return;
		}
			
		screens[currentScreen].isActive = true;
	}
}
