#include "Component.h"

#include <memory>   // Allows for the use of shared and weak pointers
#include <vector>   // Allows for the use of vectors

// Defines the ADDCOMPONENT to create a macro for the chunk of code below
#define ADDCOMPONENT \
	std::shared_ptr<T> rtn = std::make_shared<T>(); \
	rtn->entity = self; \
	rtn->began = false; \
	components.push_back(rtn);

namespace tomsengine
{
	class Core;   // Gives access to the core class

	class Entity
	{
		friend class Core;   // Gives core access to the private and public members  

	public:

		template <typename T>   // Creating a template for getting a component
		std::shared_ptr<T> getComponent()
		{
			for (size_t i = 0; i < components.size(); i++)
			{
				std::shared_ptr<T> tst = std::dynamic_pointer_cast<T>(components.at(i));

				if (tst)
				{
					return tst;
				}
			}

			//throw std::exception();
			return false;
		}

		template <typename T>   // Creating a template for adding a component with no variables
		std::shared_ptr<T> addComponent()
		{
			ADDCOMPONENT
				rtn->onInit();

			return rtn;
		}

		template <typename T, typename A>   // Creating a template for adding a component with one variable
		std::shared_ptr<T> addComponent(A a)
		{
			ADDCOMPONENT
				rtn->onInit(a);

			return rtn;
		}

		template <typename T, typename A, typename B>   // Creating a template for adding a component with two variables
		std::shared_ptr<T> addComponent(A a, B b)
		{
			ADDCOMPONENT
				rtn->onInit(a, b);

			return rtn;
		}

		std::shared_ptr<Core> getCore();   // Defining the function for getting the core

	private:

		std::weak_ptr<Entity> self;   // Creating a weak pointer to itself
		std::weak_ptr<Core> core;   // Creating a weak pointer to the core
		std::vector<std::shared_ptr<Component> > components;   // Creating a vector to store the components

		void tick();   // Defining tick function
		void reveal();   // Defining reveal function
		void setDefaultTransformPositions();   // Defining set transform function
	};
}