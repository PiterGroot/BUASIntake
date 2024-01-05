#include "Game.h"

void ScatterPickups(int pickupsAmount);
Game* Game::instance = nullptr;

#pragma region 
Game::Game()
{
	instance = this;

	OnInitialize();
	OnInitializeWindow();

	playerBoat = new PlayerBoat(sf::Vector2f(0,0));
	playerHome = new PlayerHome("PlayerHome", "Textures/Debug/rock.png", sf::Vector2f(-300, 65));

	KrakenEnemy* kraken = new KrakenEnemy("Kraken", "Textures/Enemy/tentacle.png", sf::Vector2f(0, -250));
	VortexEnemy* vortex = new VortexEnemy("Vortex", "Textures/Enemy/vortex.png", sf::Vector2f(0, 250));

	//create necessary managers
	collisionManager = new CollisionManager();
	audioManager = new AudioManager();
	textManager = new TextManager();
	inputManager = new InputManager();
	
	ScatterPickups(plasticDebris); //randomly spawn pickups
}

Game::~Game()
{
	delete window;
	delete playerBoat;
}
#pragma endregion

//game initialization
void Game::OnInitialize()
{
	window = nullptr;
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

	// Draw objects that need to be stuck to the screen (UI/HUD elements)
	window->setView(staticView);
	for (GameObject* object : Game::hudGameobjects)
	{
		window->draw(object->objectSprite);
	}

	//Draw water shader with static view
	window->draw(waterShaderRect, &waterShader);

	//Draw active text labels
	textManager->Draw(window);
	
	// Draw objects in world space
	window->setView(cameraView);
	for (GameObject* object : Game::gameobjects)
	{
		window->draw(object->objectSprite);
	}

	window->display();
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

//Returns a random point inside an arbitrary circle
sf::Vector2f RandomPointInCircle(float radius) {
	float angle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f * PI;
	float randomRadius = std::sqrt(static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * radius;

	float x = randomRadius * std::cos(angle);
	float y = randomRadius * std::sin(angle);

	return sf::Vector2f(x, y);
}

//Randomly scatter pickups inside a circular shape
void ScatterPickups(int pickupsAmount) 
{
	for (int i = 0; i < pickupsAmount; i++)
	{
		sf::Vector2f randPoint = RandomPointInCircle(5000);
		BoxCollider* collider = new BoxCollider("Pickup " + i, "Textures/Other/trash.png", randPoint, true);
		collider->objectSprite.setRotation(rand() % 360);

		float randomScaler = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.4f));
		collider->objectSprite.setScale(sf::Vector2f(1, 1) * randomScaler);
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