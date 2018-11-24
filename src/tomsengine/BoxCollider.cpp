#include "BoxCollider.h"
#include "Entity.h"
#include "Transform.h"
#include <glm/ext.hpp>   // Allows for the use of GLM

namespace tomsengine
{
	BoxCollider::~BoxCollider()
	{

	}

	/// Using AABB collision detection
	bool BoxCollider::checkCollisions(std::shared_ptr<Entity> otherEntity)
	{
		/// Uses two entities positions and scale to work out if theyre colliding by comparing each values. If collision has occured return true
		if (getEntity()->getComponent<Transform>()->getPosition().x <= (otherEntity->getComponent<Transform>()->getPosition().x + otherEntity->getComponent<Transform>()->getScale().x / 1)
			&& getEntity()->getComponent<Transform>()->getPosition().x >= (otherEntity->getComponent<Transform>()->getPosition().x - otherEntity->getComponent<Transform>()->getScale().x / 1))
		{
			if (getEntity()->getComponent<Transform>()->getPosition().y <= (otherEntity->getComponent<Transform>()->getPosition().y + otherEntity->getComponent<Transform>()->getScale().y / 1)
				&& getEntity()->getComponent<Transform>()->getPosition().y >= (otherEntity->getComponent<Transform>()->getPosition().y - otherEntity->getComponent<Transform>()->getScale().y / 1))
			{
				if (getEntity()->getComponent<Transform>()->getPosition().z <= (otherEntity->getComponent<Transform>()->getPosition().z + otherEntity->getComponent<Transform>()->getScale().z / 1)
					&& getEntity()->getComponent<Transform>()->getPosition().z >= (otherEntity->getComponent<Transform>()->getPosition().z - otherEntity->getComponent<Transform>()->getScale().z / 1))
				{
					/// Takes entities velocity and reverses it so they move away from each other
					getEntity()->getComponent<Transform>()->setVelocity(-getEntity()->getComponent<Transform>()->getVelocity());

					return true;
				}
			}
		}

		// If no collision has occured return false
		return false;
	}
}