#include "CollisionManager.h"
#include <iostream>

void CollisionManager::ResolveCollisions(std::list<Collider*> activeColliders)
{
    auto startIterator = activeColliders.begin();
    auto endIterator = activeColliders.end();

    //Loop over all colliders while startIterator hasn't reached the end of the list
    for (; startIterator != endIterator; ++startIterator) {
        Collider* collA = *startIterator;

        // Iterate over the rest of the colliders
        auto nextColliderIterator = std::next(startIterator);
        while (nextColliderIterator != endIterator) {
            Collider* collB = *nextColliderIterator;

            // Actual collision check and collision resolve
            if (collA->CheckCollision(*collB, 1)) {
                // Collision occurred, invoke the callback for each collider
                collA->InvokeCollisionCallback(*collB);
                collB->InvokeCollisionCallback(*collA);
            }

            ++nextColliderIterator;
        }
    }
}
