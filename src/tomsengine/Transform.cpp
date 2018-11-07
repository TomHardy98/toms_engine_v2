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
		rotation += glm::vec3(x2, y2, z2);
	}

	void Transform::Scale(float x3, float y3, float z3)
	{
		scale += glm::vec3(x3, y3, z3);
	}

	glm::mat4 Transform::getModelMatrix()
	{
		translationMatrix = glm::translate(glm::mat4(1.f), position);
		rotationMatrix = glm::rotate(glm::mat4(1.f), (glm::mediump_float)rotation.x, glm::vec3(0, 1, 0));
		rotationMatrix2 = glm::rotate(glm::mat4(1.f), (glm::mediump_float)rotation.y, glm::vec3(1, 0, 0));
		rotationMatrix3 = glm::rotate(glm::mat4(1.f), (glm::mediump_float)rotation.z, glm::vec3(0, 0, 1));
		scaleMatrix = glm::scale(glm::mat4(1.f), glm::vec3(scale.x, scale.y, scale.z));

		modelMatrix = translationMatrix * rotationMatrix * rotationMatrix2 * rotationMatrix3 * scaleMatrix;

		return modelMatrix;
	}
}