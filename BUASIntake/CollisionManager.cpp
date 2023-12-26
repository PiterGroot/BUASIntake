#include "CollisionManager.h"
#include <iostream>

void CollisionManager::ResolveCollisions(std::list<Collider*> activeColliders)
{
    //Get list iterators
    auto startIterator = activeColliders.begin();
    auto endIterator = activeColliders.end();

    //Loop over all colliders while startIterator hasn't reached the end of the list
    for (; startIterator != endIterator; ++startIterator) {
        Collider* collA = *startIterator;

        if (collA == nullptr)
            continue;

        // Iterate over the rest of the colliders
        auto nextColliderIterator = std::next(startIterator);
        while (nextColliderIterator != endIterator) {
            Collider* collB = *nextColliderIterator;

            if (collB == nullptr)
                continue;
            
            // Actual collision check and collision resolve
            if (collA->CheckCollision(*collB, 0)) {
                collA->OnCollision(collB);
            }
            
            ++nextColliderIterator;
        }
    }
}