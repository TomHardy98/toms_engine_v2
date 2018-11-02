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

	void Transform::Translate(glm::vec3 &direction)
	{
		position += direction;
	}

	void Transform::Rotate(float x, float y, float z)
	{
		// NEED ROTATION FUNCTION
	}

	void Transform::Rotate(glm::vec3 &direction)
	{
		rotation += direction;
	}

	void Transform::Scale(float x, float y, float z)
	{
		// NEED SCALE FUNCTION
	}

	void Transform::Scale(glm::vec3 &scaleVal)
	{
		scale += scaleVal;
	}

	glm::mat4 Transform::getModelMatrix()
	{
		return glm::translate(glm::mat4(1.0f), position);
	}
}