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
		if (getEntity()->getComponent<Transform>()->getPosition().x <= (otherEntity->getComponent<Transform>()->getPosition().x + otherEntity->getComponent<Transform>()->getScale().x / 0.5f)
			&& getEntity()->getComponent<Transform>()->getPosition().x >= (otherEntity->getComponent<Transform>()->getPosition().x - otherEntity->getComponent<Transform>()->getScale().x / 0.5f))
		{
			if (getEntity()->getComponent<Transform>()->getPosition().y <= (otherEntity->getComponent<Transform>()->getPosition().y + otherEntity->getComponent<Transform>()->getScale().y / 0.5f)
				&& getEntity()->getComponent<Transform>()->getPosition().y >= (otherEntity->getComponent<Transform>()->getPosition().y - otherEntity->getComponent<Transform>()->getScale().y / 0.5f))
			{
				if (getEntity()->getComponent<Transform>()->getPosition().z <= (otherEntity->getComponent<Transform>()->getPosition().z + otherEntity->getComponent<Transform>()->getScale().z / 0.5f)
					&& getEntity()->getComponent<Transform>()->getPosition().z >= (otherEntity->getComponent<Transform>()->getPosition().z - otherEntity->getComponent<Transform>()->getScale().z / 0.5f))
				{
					getEntity()->getComponent<Transform>()->velocity = -getEntity()->getComponent<Transform>()->velocity;

					return true;
				}
			}
		}

		return false;
	}
}