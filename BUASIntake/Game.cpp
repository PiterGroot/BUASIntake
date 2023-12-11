#include "Game.h"
#include "PlayerBoat.h"
#include <iostream>

float frameDuration = 0.01f;
float elapsedTime = 0;

PlayerBoat playerBoat;

#pragma region 
Game::Game()
{
	this->OnInitialize();
	this->OnInitializeWindow();
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
	this->waterColor = sf::Color(3, 165, 252);

	this->testRockexture.loadFromFile("Textures/circle.png");
	this->testRockSprite.setTexture(this->testRockexture);
}

//window initialization
void Game::OnInitializeWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;

	this->window = new sf::RenderWindow(this->videoMode, "Game Window", sf::Style::Titlebar | sf::Style::Close);
	this->cameraView = this->window->getDefaultView();
	this->staticView = this->window->getDefaultView();
	
	//spawn player on center of screen
	playerBoat.position = sf::Vector2f(this->videoMode.width / 2, this->videoMode.height / 2);
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
		if (windowEvent.type == sf::Event::Closed)
			this->window->close();

		if (sf::Event::KeyPressed)
		{
			if (this->windowEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
		}
	}
}

//Update game loop
void Game::OnUpdate(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->OnUpdateWindowEvents();

	sf::Vector2f viewPos = cameraView.getCenter();
	sf::Vector2f lerpedViewCenter = lerp(viewPos, playerBoat.position, 5 * this->deltaTime);
	cameraView.setCenter(lerpedViewCenter);

	playerBoat.UpdatePlayer(deltaTime);
}

//Rendering game
void Game::OnRender()
{
	// Clear the window
	this->window->clear(this->waterColor);

	this->window->setView(staticView);
	// Draw screen space

	// Draw objects world space
	this->window->setView(cameraView);

	this->window->draw(playerBoat.objectSprite);
	this->window->draw(testRockSprite);

	this->window->display();
}
