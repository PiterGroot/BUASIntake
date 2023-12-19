#include "Game.h"
#include "BoxCollider.h"

BoxCollider* boxCollider = nullptr;
Game* Game::instance = nullptr;
sf::Shader waterShader;

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

	boxCollider = new BoxCollider("Textures/circle.png", playerBoat->position + sf::Vector2f(0, 15), sf::Vector2f(1, 1));
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
	this->videoMode.width = 900;
	this->videoMode.height = 700;

	this->window = new sf::RenderWindow(this->videoMode, "Untitled boat game", sf::Style::Titlebar | sf::Style::Close);
	this->cameraView = this->window->getDefaultView();
	this->staticView = this->window->getDefaultView();

	//initialize rect for water shader
	waterShaderRect = sf::RectangleShape(sf::Vector2f(videoMode.width, videoMode.height));
	waterShaderRect.setOrigin(GetScreenCenter());
	waterShaderRect.setPosition(GetScreenCenter());

	//load water shader
	waterShader.loadFromFile("water_shader.frag", sf::Shader::Fragment);
	waterShader.setUniform("resolution", sf::Vector2f(window->getSize()));
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

	//update "camera" movement
	cameraView.setCenter(playerBoat->position);

	//update player logic
	playerBoat->UpdatePlayer(deltaTime);

	//pass necessary variables to the water shader
	waterShader.setUniform("time", elapsedTime);
	waterShader.setUniform("scrollDirX", (playerBoat->position.x + (-playerBoat->currentMoveDir.x)));
	waterShader.setUniform("scrollDirY", (-playerBoat->position.y + (playerBoat->currentMoveDir.y)));
}

//Rendering game
void Game::OnRender()
{
	// Clear the window
	this->window->clear(this->waterColor);

	//testing simple box collisions
	auto playerCollider = playerBoat->GetCollider();
	if (boxCollider->GetCollider().CheckCollision(playerCollider, 1)) {
		std::cout << "Player collided!!" << "\n";
	}

	// Draw objects that need to be stuck to the screen
	this->window->setView(staticView);
	for (sf::Sprite*& sprite : Game::hudGameobjects)
	{
		this->window->draw(*sprite);
	}
	
	//draw water shader with static view
	this->window->draw(waterShaderRect, &waterShader);
	
	// Draw objects in world space
	this->window->setView(cameraView);
	for (sf::Sprite*& sprite : Game::gameobjects) 
	{
		this->window->draw(*sprite);
	}

	this->window->display();
}
