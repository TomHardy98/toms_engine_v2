#include "Component.h"

#include <glm/ext.hpp>   // Allows for the use of GLM

namespace tomsengine
{
	class Camera : public Component   /// Inherits from component
	{
	public:

		glm::mat4 getProjMatrix();   /// Get projection matrix function
	};
}