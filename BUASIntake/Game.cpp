#include "Game.h"
Game* Game::instance = nullptr;

Game::Game()
{
	OnInitializeWindow();
	OnInitialize();
}

Game::~Game()
{
	delete window;
	delete playerBoat;
}

//Game initialization
void Game::OnInitialize()
{
	instance = this;

	playerBoat = new PlayerBoat(sf::Vector2f(0, 0));
	playerHome = new PlayerHome("PlayerHome", "Textures/Debug/rock.png", sf::Vector2f(-300, 65));

	//Create necessary managers / systems
	collisionManager = new CollisionManager();
	audioManager = new AudioManager();
	textManager = new TextManager();
	inputManager = new InputManager();

	enemySpawner = new EnemySpawner();
	new PickupScatter(plasticDebris);

	waterColor = sf::Color(3, 165, 252); //out of bounds background color
	srand(time(0)); //set random seed
}

//window initialization
void Game::OnInitializeWindow()
{
	videoMode.width = 900;
	videoMode.height = 700;

	//Create window
	window = new sf::RenderWindow(videoMode, "Untitled boat game", sf::Style::Titlebar | sf::Style::Close);
	cameraView = window->getDefaultView();
	staticView = window->getDefaultView();

	//Initialize rect for water shader
	waterShaderRect = sf::RectangleShape(sf::Vector2f(videoMode.width, videoMode.height));
	waterShaderRect.setOrigin(GetScreenCenter());
	waterShaderRect.setPosition(GetScreenCenter());
	
	//Load water shader
	waterShader.loadFromFile("Resources/Shader/water_shader.frag", sf::Shader::Fragment);
	waterShader.setUniform("resolution", sf::Vector2f(window->getSize()));
}

//Update game loop
void Game::OnUpdate(float deltaTime)
{
	this->deltaTime = deltaTime;
	elapsedTime += deltaTime;

	//Update window polling events
	OnUpdateWindowEvents();

	//Update gameobjects that needs to be updated
	for (GameObject* object : Game::updatingGameobjects)
	{
		object->OnUpdate(deltaTime);
	}

	std::ostringstream timerStringStream;
	timerStringStream << std::fixed << std::setprecision(2) << elapsedTime;
	textManager->UpdateTextLabel("GameTimer", timerStringStream.str());

	//Resolve possible collisions
	collisionManager->ResolveCollisions(activeColliders);
	
	//Update "camera" movement
	cameraView.setCenter(playerBoat->position);

	//Pass necessary variables to the water shader
	waterShader.setUniform("time", elapsedTime);
	waterShader.setUniform("scrollDirX", (playerBoat->position.x + (-playerBoat->currentMoveDirection.x)));
	waterShader.setUniform("scrollDirY", (-playerBoat->position.y + (playerBoat->currentMoveDirection.y)));
}

//Update loop after the render pass
void Game::OnLateUpdate(float deltaTime) 
{
	// Remove objects marked for deletion (needs to be done AFTER we have have passed the update loop)
	for (auto& objectToDelete : objectsToDelete) {

		// Remove from updatingGameobjects if it contains the object
		auto updatingIterator = std::remove(updatingGameobjects.begin(), updatingGameobjects.end(), objectToDelete);
		if (updatingIterator != updatingGameobjects.end()) {
			updatingGameobjects.erase(updatingIterator);
		}

		auto iterator = std::remove(Game::gameobjects.begin(), Game::gameobjects.end(), objectToDelete);
		Game::gameobjects.erase(iterator, Game::gameobjects.end());

		delete objectToDelete;
	}
	objectsToDelete.clear(); // Clear the list for the next frame
}

//Rendering game
void Game::OnRender()
{
	// Clear the window
	window->clear(waterColor);
	
	//Draw water shader with static view
	window->draw(waterShaderRect, &waterShader);

	// Draw objects in world space
	window->setView(cameraView);

	//Draw active text labels that need to move along with camera
	textManager->DrawInWorld(window);
	for (GameObject* object : Game::gameobjects) //draw all active gameobjects in worldspace
	{
		if (object->isActive)
			window->draw(object->objectSprite);
	}

	// Draw objects that need to be stuck to the screen (UI/HUD elements)
	window->setView(staticView);
	for (GameObject* object : Game::hudGameobjects)
	{
		if (object->isActive)
			window->draw(object->objectSprite);
	}

	//Draw active text labels stuck on the screen
	textManager->Draw(window);

	window->display(); //display to window
}

//Handle window polling events
void Game::OnUpdateWindowEvents()
{
	while (window->pollEvent(windowEvent))
	{
		if (windowEvent.type == sf::Event::Closed)
			window->close();

		if (sf::Event::KeyPressed)
		{
			if (windowEvent.key.code == sf::Keyboard::Escape)
				window->close();
		}
	}
}

//Gets the window width and height
sf::Vector2u Game::GetScreenSize() 
{
	return window->getSize();
}

//Get center of the screen resolution
sf::Vector2f Game::GetScreenCenter() 
{
	return sf::Vector2f(videoMode.width / 2, videoMode.height / 2);
}

//Gets current windowEvent
sf::Event* Game::GetWindowEvent() 
{
	return &windowEvent;
}

//Gets the camera view
sf::View* Game::GetCameraView() 
{
	return &cameraView;
}

//Check if window is running
const bool Game::isWindowActive() const
{
	return window->isOpen();
}