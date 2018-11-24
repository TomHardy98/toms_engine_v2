#include "Camera.h"
#include "Transform.h"

#define WINDOW_WIDTH 600   /// Defining window width
#define WINDOW_HEIGHT 900   /// Defining window height

namespace tomsengine
{
	glm::mat4 Camera::getProjMatrix()
	{
		return glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);   /// Returns the camera projection matrix
	}
}