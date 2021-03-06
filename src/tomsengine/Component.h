#ifndef TOMSENGINE_COMPONENT_H
#define TOMSENGINE_COMPONENT_H

#include <memory>   // Allows for the use of shared and weak pointers

namespace tomsengine
{
	class Entity;   // Gives access to the Entity class
	class Core;   // Gives access to the Core class

	class Component
	{
		friend class Entity;

	public:

		virtual ~Component();   // Virtual deconstructor
		std::shared_ptr<Core> getCore();   // Shared pointer getCore() function declaration
		std::shared_ptr<Entity> getEntity();   // Shared pointer getEntity() function declaration

	private:

		std::weak_ptr<Entity> entity;   // Weak pointer to an entity
		bool began;   // Boolean for if core has began

		virtual void onInit();   /// onInit function declaration to be overriden
		virtual void onBegin();   /// onBegin function declaration to be overriden
		virtual void onTick();   /// onTick function declaration to be overriden
		virtual void onReveal();   /// onReveal function declaration to be overriden
		virtual void onPostReveal();   /// onPostReveal function declaration to be overriden
	};
}

#endif