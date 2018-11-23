#include "Component.h"
#include "Entity.h"
#include "Transform.h"

namespace tomsengine
{
	Component::~Component()   // Declaring Component destructor
	{

	}

	void Component::onInit()   // Declaring Component onInit function
	{ 

	}

	void Component::onBegin()   // Declaring Component onBegin function
	{ 
		
	}
	
	void Component::onTick()   // onTick function or update function
	{
		
	}

	void Component::onReveal()   // Declaring Component onReveal function
	{ 

	}

	void Component::onPostReveal()
	{

	}

	std::shared_ptr<Entity> Component::getEntity()   // getEntity function declaration
	{
		return entity.lock();   // Return a shared pointer of Entity
	}

	std::shared_ptr<Core> Component::getCore()   // getCore function declaration
	{
		return getEntity()->getCore();   // Return a shared pointer of Core
	}
}