#include "Game.h"
Vector2f GetMovementDirection();

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
	this->waterColor = Color(3, 165, 252);

	this->boatTexture.loadFromFile("Textures/circle.png");
	this->boatSprite.setTexture(boatTexture);
	this->boatSprite.setOrigin(this->playerBoat.origin);

	this->testRockexture.loadFromFile("Textures/circle.png");
	this->testRockSprite.setTexture(this->testRockexture);
}

//window initialization
void Game::OnInitializeWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;

	this->window = new RenderWindow(this->videoMode, "Game Window", Style::Titlebar | Style::Close);
	this->view = this->window->getDefaultView();
	
	//spawn player on center of screen
	this->playerBoat.position = Vector2f(this->videoMode.width / 2, this->videoMode.height / 2);
	this->testRockSprite.setPosition(this->playerBoat.position);
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
	this->OnUpdateWindowEvents();

	Vector2f viewPos = view.getCenter();
	Vector2f lerpedViewCenter = lerp(viewPos, this->playerBoat.position, 5 * deltaTime);
	this->view.setCenter(lerpedViewCenter);

	auto moveDir = GetMovementDirection();
	this->playerBoat.position += moveDir * this->playerBoat.moveSpeed * deltaTime;
	this->boatSprite.setPosition(this->playerBoat.position);
}

//Rendering game
void Game::OnRender()
{
	// Clear the window
	this->window->clear(this->waterColor);

	// Draw objects
	this->window->setView(view);
	this->window->draw(boatSprite);
	this->window->draw(testRockSprite);

	this->window->display();
}

//Get normalized movement direction
Vector2f GetMovementDirection() {
	Vector2f direction;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		direction += Vector2f(0, -1);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		direction += Vector2f(-1, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		direction -= Vector2f(0, -1);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		direction += Vector2f(1, 0);
	}
	
	return normalized(direction);
}
