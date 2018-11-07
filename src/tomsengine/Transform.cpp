#include "Transform.h"

#include <glm/ext.hpp>   // Allows for the use of GLM
#include <memory>

namespace tomsengine
{
	Transform::Transform()
	{

	}

	Transform::~Transform()
	{

	}

	void Transform::Translate(float x, float y, float z)
	{
		position += glm::vec3(x, y, z);
	}

	void Transform::Rotate(float x2, float y2, float z2)
	{
		// NEED ROTATION FUNCTION
	}

	void Transform::Scale(float x3, float y3, float z3)
	{
		// NEED SCALE FUNCTION
	}

	glm::mat4 Transform::getModelMatrix()
	{
		return glm::translate(glm::mat4(1.0f), position);
	}
}