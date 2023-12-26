#include <list>
#include "Collider.h"

class CollisionManager 
{

public:
	void ResolveCollisions(std::list<Collider*> activeColliders);
};