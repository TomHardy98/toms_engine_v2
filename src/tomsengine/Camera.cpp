#include "Camera.h"
#include "Transform.h"

#define WINDOW_WIDTH 1200   // Defining window width
#define WINDOW_HEIGHT 800   // Defining window height

namespace tomsengine
{
	void Camera::onInit()
	{

	}

	glm::mat4 Camera::getProjMatrix()
	{
		return glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	}
}