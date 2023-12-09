#include "Game.h"
#include "PlayerBoat.h"
#include "Menu.h"
#include <iostream>

float frameDuration = 0.01f;
float elapsedTime = 0;

PlayerBoat playerBoat;
Menu mainMenu;

#pragma region 
Game::Game()
{
	this->OnInitialize();
	this->OnInitializeWindow();

	mainMenu.CreateButton(Vector2f(this->videoMode.width / 2, this->videoMode.height / 2), "haha");
}

Game::~Game()
{
	delete this->window;
}
#pragma endregion

//game initialization
void Game::OnInitialize()
{
	this->window = nullptr;
	this->waterColor = Color(3, 165, 252);

	this->testRockexture.loadFromFile("Textures/circle.png");
	this->testRockSprite.setTexture(this->testRockexture);
}

//window initialization
void Game::OnInitializeWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;

	this->window = new RenderWindow(this->videoMode, "Game Window", Style::Titlebar | Style::Close);
	this->cameraView = this->window->getDefaultView();
	this->staticView = this->window->getDefaultView();
	
	//spawn player on center of screen
	playerBoat.position = Vector2f(this->videoMode.width / 2, this->videoMode.height / 2);
	this->testRockSprite.setPosition(playerBoat.position);

	this->staticView.setCenter(playerBoat.position);
}

//Check if window is running
const bool Game::isWindowActive() const
{
	return this->window->isOpen();
}

//Handle window polling events
void Game::OnUpdateWindowEvents()
{
	while (this->window->pollEvent(this->windowEvent))
	{
		if (windowEvent.type == Event::Closed)
			this->window->close();

		if (Event::KeyPressed)
		{
			if (this->windowEvent.key.code == Keyboard::Escape)
				this->window->close();
		}
	}
}

//Update game loop
void Game::OnUpdate(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->OnUpdateWindowEvents();

	Vector2f viewPos = cameraView.getCenter();
	Vector2f lerpedViewCenter = lerp(viewPos, playerBoat.position, 5 * this->deltaTime);
	cameraView.setCenter(lerpedViewCenter);

	playerBoat.UpdatePlayer(deltaTime);
}

//Rendering game
void Game::OnRender()
{
	// Clear the window
	this->window->clear(this->waterColor);

	this->window->setView(staticView);
	for (sf::Sprite& menuButton : mainMenu.menuButtons)
	{
		this->window->draw(menuButton);
	}

	// Draw objects
	this->window->setView(cameraView);

	this->window->draw(playerBoat.boatSprite);
	this->window->draw(testRockSprite);

	this->window->display();
}
