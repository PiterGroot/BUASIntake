#include "Waypoint.h"

Waypoint::Waypoint(sf::String name, sf::String texturePath, sf::Vector2f targetPosition, sf::Color color, bool doRotate)
{
    this->doRotate = doRotate;
	this->targetPosition = targetPosition;

    objectSprite.setColor(color);
	InitializeGameobject(name, texturePath, this->targetPosition, false);

	Game::instance->updatingGameobjects.push_back(this);
}

//Updating position for clamping
void Waypoint::OnUpdate(float deltaTime) 
{
    if(doRotate) RotateTowardsBase(this, targetPosition);
    ClampPosition(this, targetPosition);
}

//Rotate waypoint towards its base point
void Waypoint::RotateTowardsBase(GameObject* waypoint, sf::Vector2f targetPosition)
{
    sf::Vector2f basePosition = targetPosition + sf::Vector2f(0, 10);
    float angle = std::atan2(basePosition.y - waypoint->position.y, basePosition.x - waypoint->position.x) * 180 / PI;
    waypoint->objectSprite.setRotation(angle);
}

//Clamps sprite to the screen to make sure it is always visible
void Waypoint::ClampPosition(GameObject* waypoint, sf::Vector2f targetPosition) {
    // move to desired target position
    waypoint->MoveGameObject(waypoint->position = targetPosition);

    sf::Vector2f screenCenter = Game::instance->GetScreenCenter();
    sf::View* cameraView = Game::instance->GetCameraView();

    sf::Vector2f cameraCenterPosition = cameraView->getCenter();
    sf::Vector2f spriteHalfSize = sf::Vector2f(waypoint->objectTexture.getSize()) * .5f;

    // calculate the clamping bounds, taking into account the sprite's size
    sf::Vector2f minBounds = cameraCenterPosition - screenCenter + spriteHalfSize;
    sf::Vector2f maxBounds = cameraCenterPosition + screenCenter - spriteHalfSize;

    sf::Vector2f clampedPosition = ClampVec2(waypoint->position, minBounds, maxBounds);

    // clamp position to the screen
    waypoint->MoveGameObject(waypoint->position = clampedPosition);
}
