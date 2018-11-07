#include "Entity.h"
#include "Transform.h"

namespace tomsengine
{
	std::shared_ptr<Core> Entity::getCore()   // Declaring entity getCore function
	{
		return core.lock();   // Return the core
	}

	void Entity::tick()   // Declaring entity tick function
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)   // For each component
		{
			if (!(*it)->began)   // If the iterator isnt at the beginning
			{
				(*it)->onBegin();   // Call onBegin function at each component
				(*it)->began = true;   // Set began to true at each component
			}

			(*it)->onTick();   // Call onTick function at each component
		}
	}

	void Entity::reveal()   // Declaring entity reveal function
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)   // For each component
		{
			(*it)->onReveal();   // Call onReveal function at each component
		}
	}

	void Entity::setDefaultTransformPositions()   // Declaring entity set transform function
	{
		addComponent<Transform>()->setPosition(0.0f, 0.0f, -10.0f);   // Add a transform component and set default position
		getComponent<Transform>()->setRotation(0.0f, 0.0f, 0.0f);   // Access the transform component and set default rotation
		getComponent<Transform>()->setScale(1.0f, 1.0f, 1.0f);   // Access the transform component and set default scale
	}
}