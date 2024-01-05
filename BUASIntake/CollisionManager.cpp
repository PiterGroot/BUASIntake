#include "CollisionManager.h"
#include "Game.h"

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
            if (collA->CheckCollision(*collB, 0)) {
                // Collision occurred, invoke the callback for each collider
                collA->OnCollision(*collB);
                collB->OnCollision(*collA);
            }

            ++nextColliderIterator;
        }
    }
}

//Manual check if a collider has collision with another collider
bool CollisionManager::HasCollision(Collider* collA, GameObject::ObjectTag tag) 
{
    auto colliders = Game::instance->activeColliders;
    auto startIterator = colliders.cbegin();
    auto endIterator = colliders.cend();

    for (; startIterator != endIterator; ++startIterator) {
        Collider* collB = *startIterator;
        if (collA == collB) continue;

        if (collA->CheckCollision(*collB, 0)) 
        {
            if (collB->GetObject()->tag == tag) 
                return true;
        }
    }
    return false;
}
