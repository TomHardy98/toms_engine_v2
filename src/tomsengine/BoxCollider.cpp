#include "BoxCollider.h"
#include "Entity.h"
#include "Transform.h"
#include <glm/ext.hpp>   // Allows for the use of GLM

namespace tomsengine
{
	BoxCollider::~BoxCollider()
	{

	}

	bool BoxCollider::checkCollisions(std::shared_ptr<Entity> otherEntity)
	{
		glm::vec3 prevPos = getEntity()->getComponent<Transform>()->getPosition();
		glm::vec3 prevPosOther = otherEntity->getComponent<Transform>()->getPosition();

		if (getEntity()->getComponent<Transform>()->getPosition().x <= (otherEntity->getComponent<Transform>()->getPosition().x + otherEntity->getComponent<Transform>()->getScale().x / 0.7f)
			&& getEntity()->getComponent<Transform>()->getPosition().x >= (otherEntity->getComponent<Transform>()->getPosition().x - otherEntity->getComponent<Transform>()->getScale().x / 0.7f))
		{
			if (getEntity()->getComponent<Transform>()->getPosition().y <= (otherEntity->getComponent<Transform>()->getPosition().y + otherEntity->getComponent<Transform>()->getScale().y / 0.7f)
				&& getEntity()->getComponent<Transform>()->getPosition().y >= (otherEntity->getComponent<Transform>()->getPosition().y - otherEntity->getComponent<Transform>()->getScale().y / 0.7f))
			{
				if (getEntity()->getComponent<Transform>()->getPosition().z <= (otherEntity->getComponent<Transform>()->getPosition().z + otherEntity->getComponent<Transform>()->getScale().z / 0.7f)
					&& getEntity()->getComponent<Transform>()->getPosition().z >= (otherEntity->getComponent<Transform>()->getPosition().z - otherEntity->getComponent<Transform>()->getScale().z / 0.7f))
				{
					getEntity()->getComponent<Transform>()->velocity = -getEntity()->getComponent<Transform>()->velocity;

					return true;
				}
			}
		}

		return false;
	}
}