#include "Game.h"

float frameDuration = 0.01f;
float elapsedTime = 0;

Game* Game::instance = nullptr;

#pragma region 
Game::Game()
{
	this->playerBoat = new PlayerBoat();

	this->OnInitialize();
	this->OnInitializeWindow();
	
	instance = this;
	this->playerBoat->InitializePlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->playerBoat;
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
	playerBoat->position = GetScreenSize();
	this->testRockSprite.setPosition(playerBoat->position);

	this->staticView.setCenter(playerBoat->position);
}

void Game::PrintToConsole(sf::String message)
{
	std::cout << message.toAnsiString() << "\n";
}

sf::Vector2f Game::GetScreenSize() 
{
	return sf::Vector2f(videoMode.width / 2, this->videoMode.height / 2);
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
	sf::Vector2f lerpedViewCenter = lerp(viewPos, playerBoat->position, 5 * this->deltaTime);
	cameraView.setCenter(lerpedViewCenter);

	playerBoat->UpdatePlayer(deltaTime);
}

//Rendering game
void Game::OnRender()
{
	// Clear the window
	this->window->clear(this->waterColor);

	// Draw objects that need to be stuck to the screen
	this->window->setView(staticView);
	for (sf::Sprite*& sprite : Game::hudGameobjects)
	{
		this->window->draw(*sprite);
	}

	// Draw objects in world space
	this->window->setView(cameraView);
	for (sf::Sprite*& sprite : Game::gameobjects) 
	{
		this->window->draw(*sprite);
	}

	//this->window->draw(playerBoat.objectSprite);
	this->window->draw(testRockSprite);

	this->window->display();
}
