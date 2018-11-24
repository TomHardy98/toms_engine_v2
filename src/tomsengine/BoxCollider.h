#include "Component.h"

#include <memory>
#include <iostream>

namespace tomsengine
{
	class BoxCollider : public Component   // Inherits from component
	{
	public:

		~BoxCollider();   /// Deconstructor for BoxCollider

		bool checkCollisions(std::shared_ptr<Entity> otherEntity);   /// Check collisions function for BoxCollider component
	};
}