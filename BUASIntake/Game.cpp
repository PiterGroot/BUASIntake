#include "Game.h"

Game* Game::instance = nullptr;
sf::Shader shader;

#pragma region 
Game::Game()
{
	this->playerBoat = new PlayerBoat();

	this->OnInitialize();
	this->OnInitializeWindow();

	playerBoat->position = GetScreenCenter();
	this->staticView.setCenter(playerBoat->position);
	
	instance = this;
	this->playerBoat->InitializePlayer();

	shader.loadFromFile("water_shader.frag", sf::Shader::Fragment);
	//shader.setUniform("iResolution", sf::Vector2f(window->getSize()));
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
}

//window initialization
void Game::OnInitializeWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;

	this->window = new sf::RenderWindow(this->videoMode, "Untitled boat game", sf::Style::Titlebar | sf::Style::Close);
	this->cameraView = this->window->getDefaultView();
	this->staticView = this->window->getDefaultView();
}

void Game::PrintToConsole(sf::String message)
{
	std::cout << message.toAnsiString() << "\n";
}

//Gets the current center of the screen
sf::Vector2f Game::GetScreenCenter() 
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
	this->elapsedTime += deltaTime;

	this->OnUpdateWindowEvents();

	sf::Vector2f viewPos = cameraView.getCenter();
	sf::Vector2f lerpedViewCenter = lerp(viewPos, playerBoat->position, 5 * this->deltaTime);
	cameraView.setCenter(lerpedViewCenter);

	playerBoat->UpdatePlayer(deltaTime);
	shader.setUniform("iTime", elapsedTime);

	/*if (playerBoat->currentMoveDir == sf::Vector2f(0, 0))
		return;*/

	shader.setUniform("scrollDirX", (playerBoat->position.x + (-playerBoat->currentMoveDir.x)));
	shader.setUniform("scrollDirY", (-playerBoat->position.y + (playerBoat->currentMoveDir.y)));
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
	
	sf::RectangleShape fullscreenRect(sf::Vector2f(videoMode.width, videoMode.height));
	fullscreenRect.setFillColor(sf::Color::White);
	fullscreenRect.setOrigin(videoMode.width / 2, videoMode.height / 2);
	fullscreenRect.setPosition(videoMode.width / 2, videoMode.height / 2);
	this->window->draw(fullscreenRect, &shader);
	
	// Draw objects in world space
	this->window->setView(cameraView);
	for (sf::Sprite*& sprite : Game::gameobjects) 
	{
		this->window->draw(*sprite);
	}

	this->window->display();
}
