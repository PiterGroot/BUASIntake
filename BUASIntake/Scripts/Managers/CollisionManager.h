#pragma once

#include "../Framework/Collider.h"
#include <list>

class CollisionManager 
{
public:
	void ResolveCollisions(std::list<Collider*> activeColliders);
	bool HasCollision(Collider* collA, GameObject::ObjectTag tag);
};