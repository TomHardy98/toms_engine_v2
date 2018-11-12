#include "Component.h"

#include <memory>
#include <iostream>

namespace tomsengine
{
	class BoxCollider : public Component
	{
	public:

		~BoxCollider();

		bool checkCollisions(std::shared_ptr<Entity> otherEntity);

	private:


	};
}