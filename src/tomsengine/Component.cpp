#include "Component.h"
#include "Entity.h"

namespace tomsengine
{

	Component::~Component() { }
	void Component::onInit() { }
	void Component::onBegin() { }
	void Component::onTick() { }
	void Component::onReveal() { }

	std::shared_ptr<Entity> Component::getEntity()
	{
		return entity.lock();
	}

	std::shared_ptr<Core> Component::getCore()
	{
		return getEntity()->getCore();
	}

}