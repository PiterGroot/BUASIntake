#include "Collider.h"
#include <list>

class CollisionManager 
{
public:
	void ResolveCollisions(std::list<Collider*> activeColliders);
};