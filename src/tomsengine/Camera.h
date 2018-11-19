#include "Component.h"

#include <glm/ext.hpp>   // Allows for the use of GLM

namespace tomsengine
{
	class Camera : public Component
	{
	public:

		void onInit();

		glm::mat4 getProjMatrix();
	};
}