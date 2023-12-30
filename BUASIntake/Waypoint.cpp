#include "Waypoint.h"

Waypoint::Waypoint(sf::String name, sf::String texturePath, sf::Vector2f targetPosition)
{
	this->targetPosition = targetPosition;

	InitializeGameobject(name, texturePath, this->targetPosition, false);
	Game::instance->updatingGameobjects.push_back(this);
}

//Updating position for clamping
void Waypoint::OnUpdate(float deltaTime) 
{
    // move to desired target position
    MoveGameObject(position = targetPosition);

    sf::Vector2f screenCenter = Game::instance->GetScreenCenter();
    sf::View* cameraView = Game::instance->GetCameraView();

    sf::Vector2f cameraCenterPosition = cameraView->getCenter();
    sf::Vector2f spriteHalfSize = sf::Vector2f(objectTexture.getSize()) * .5f;

    // calculate the clamping bounds, taking into account the sprite's size
    sf::Vector2f minBounds = cameraCenterPosition - screenCenter + spriteHalfSize;
    sf::Vector2f maxBounds = cameraCenterPosition + screenCenter - spriteHalfSize;

    sf::Vector2f clampedPosition = clampVec2(position, minBounds, maxBounds);

    // clamp position to the screen
    MoveGameObject(position = clampedPosition);
}