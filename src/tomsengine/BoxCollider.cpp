#include "BoxCollider.h"
#include "Entity.h"
#include "Transform.h"

namespace tomsengine
{
	BoxCollider::~BoxCollider()
	{

	}

	bool BoxCollider::checkCollisions(std::shared_ptr<Entity> otherEntity)
	{
		if (getEntity()->getComponent<Transform>()->getPosition().x <= (otherEntity->getComponent<Transform>()->getPosition().x + otherEntity->getComponent<Transform>()->getScale().x / 1)
			&& getEntity()->getComponent<Transform>()->getPosition().x >= (otherEntity->getComponent<Transform>()->getPosition().x - otherEntity->getComponent<Transform>()->getScale().x / 1))
		{
			if (getEntity()->getComponent<Transform>()->getPosition().y <= (otherEntity->getComponent<Transform>()->getPosition().y + otherEntity->getComponent<Transform>()->getScale().y / 1)
				&& getEntity()->getComponent<Transform>()->getPosition().y >= (otherEntity->getComponent<Transform>()->getPosition().y - otherEntity->getComponent<Transform>()->getScale().y / 1))
			{
				if (getEntity()->getComponent<Transform>()->getPosition().z <= (otherEntity->getComponent<Transform>()->getPosition().z + otherEntity->getComponent<Transform>()->getScale().z / 1)
					&& getEntity()->getComponent<Transform>()->getPosition().z >= (otherEntity->getComponent<Transform>()->getPosition().z - otherEntity->getComponent<Transform>()->getScale().z / 1))
				{
					getEntity()->getComponent<Transform>()->velocity = -getEntity()->getComponent<Transform>()->velocity;
					std::cout << "Collision has occured!" << std::endl;
					return true;
				}
			}
		}

		return false;
	}
}