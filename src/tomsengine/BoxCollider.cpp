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
		std::cout << "Checking collisiosn between two objects with a box collider" << std::endl;

		return false;
	}
}