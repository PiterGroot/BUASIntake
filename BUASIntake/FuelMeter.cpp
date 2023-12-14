#include "GameObject.h"	

class FuelMeter : public GameObject
{
public:
	void Spawn() {
		GameObject::Initialize("Textures/UI/fueelbar.png", sf::Vector2f(15, 50));
		position = sf::Vector2f(0, -50);
		objectSprite.setPosition(position);
	}
};