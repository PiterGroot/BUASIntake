#include <iostream>
#include "CollisionManager.h"

void CollisionManager::ResolveCollisions(std::list<Collider*> activeColliders)
{
    auto iterator1 = activeColliders.begin();
    auto end = activeColliders.end();

    for (; iterator1 != end; ++iterator1) {
        Collider* collA = *iterator1;

        if (collA == nullptr)
            continue;

        // Iterate over the rest of the colliders
        auto iterator2 = std::next(iterator1);
        while (iterator2 != end) {
            Collider* collB = *iterator2;

            if (collB == nullptr)
                continue;

            if (collA->CheckCollision(*collB, 0)) {
                // Collision detected
                //std::cout << "Collision between collider1 and collider2!\n";
            }

            ++iterator2;
        }
    }

	//auto playerCollider = playerBoat->GetCollider();
	//if (boxCollider != nullptr) {
	//	if (boxCollider->CheckCollision(playerCollider, 1)) {
	//		std::cout << "Player collided!!" << "\n";

	//		// mark collider object for deletion
	//		objectsToDelete.push_back(boxCollider);
	//		boxCollider = nullptr;
	//	}
	//}
}