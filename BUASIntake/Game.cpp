#include "Game.h"
#include "BoxCollider.h"

BoxCollider* boxCollider = nullptr;
Game* Game::instance = nullptr;
sf::Shader waterShader;

GameObject* testBaseWaypoint = nullptr;
GameObject* testBase = nullptr;

#pragma region 
Game::Game()
{
	this->playerBoat = new PlayerBoat();

	this->OnInitialize();
	this->OnInitializeWindow();

	instance = this;
	sf::Vector2f screenCenter = sf::Vector2f(GetScreenCenter());

	this->playerBoat->InitializePlayer(sf::Vector2f(0,0));
	boxCollider = new BoxCollider("Textures/circle.png", sf::Vector2f(100, 0), true);
	
	testBase = new GameObject();
	testBase->objectSprite.setScale(sf::Vector2f(6, 6));
	testBase->InitializeGameobject("Textures/rock.png", sf::Vector2f(-300, 65));
	
	testBaseWaypoint = new GameObject();
	testBaseWaypoint->objectSprite.setColor(sf::Color(255, 0, 0, 255));
	testBaseWaypoint->InitializeGameobject("Textures/circle.png", sf::Vector2f(0, 0));

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
	
	//update player logic
	playerBoat->UpdatePlayer(deltaTime);

	auto playerCollider = playerBoat->GetCollider();
	if (boxCollider != nullptr) {
		if (boxCollider->CheckCollision(playerCollider, 1)) {
			std::cout << "Player collided!!" << "\n";

			// mark collider object for deletion
			objectsToDelete.push_back(boxCollider);
			boxCollider = nullptr;
		}
	}

	//testing clamped "waypoint" to screen
	testBaseWaypoint->objectSprite.setPosition(testBaseWaypoint->position = sf::Vector2f(-300, 0));
	
	sf::Vector2f clampedPosition = clampVec2(testBaseWaypoint->position, cameraView.getCenter() + sf::Vector2f(-450, -350), cameraView.getCenter() + sf::Vector2f(450, 350));
	testBaseWaypoint->objectSprite.setPosition(testBaseWaypoint->position = clampedPosition);

	//update "camera" movement
	cameraView.setCenter(playerBoat->position);

	//pass necessary variables to the water shader
	waterShader.setUniform("time", elapsedTime);
	waterShader.setUniform("scrollDirX", (playerBoat->position.x + (-playerBoat->currentMoveDir.x)));
	waterShader.setUniform("scrollDirY", (-playerBoat->position.y + (playerBoat->currentMoveDir.y)));
}

//Update loop after the render pass
void Game::OnLateUpdate(float deltaTime) 
{
	// remove objects marked for deletion
	for (auto& objectToDelete : objectsToDelete) {
		auto iterator = std::remove(Game::gameobjects.begin(), Game::gameobjects.end(), objectToDelete);
		Game::gameobjects.erase(iterator, Game::gameobjects.end());

		delete objectToDelete;
	}
	objectsToDelete.clear(); // clear the list for the next frame
}

//Rendering game
void Game::OnRender()
{
	// Clear the window
	this->window->clear(this->waterColor);

	// Draw objects that need to be stuck to the screen
	this->window->setView(staticView);
	for (GameObject* object : Game::hudGameobjects)
	{
		this->window->draw(object->objectSprite);
	}
	
	//draw water shader with static view
	this->window->draw(waterShaderRect, &waterShader);
	
	// Draw objects in world space
	this->window->setView(cameraView);
	for (GameObject* object : Game::gameobjects)
	{
		this->window->draw(object->objectSprite);
	}

	this->window->display();
}