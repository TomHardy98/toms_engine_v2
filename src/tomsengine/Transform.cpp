#include <glm/ext.hpp>   // Allows for the use of GLM
#include <memory>

#include "Transform.h"
#include "Entity.h"

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
		position += glm::vec3(x, y, z);   /// Add to the current position using the given x, y and z values to 'translate' object
	}

	void Transform::Rotate(float x2, float y2, float z2)
	{
		rotation += glm::vec3(x2, y2, z2);   /// Add to the current rotation using the given x, y and z values to 'rotate' object
	}

	void Transform::Scale(float x3, float y3, float z3)
	{
		scale += glm::vec3(x3, y3, z3);   /// Add to the current scale using the given x, y and z values to 'scale' object
	}

	glm::mat4 Transform::getModelMatrix()
	{
		// Creating correct rotation matrix using x, y and z values
		rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(1.0f, 0.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		modelMatrix = glm::translate(glm::mat4(1.0f), position) * rotationMatrix * glm::scale(glm::mat4(1), scale);   // Setting model matrix in correct order

		return modelMatrix;   // Returning model matrix
	}

	glm::mat4 Transform::getViewMatrix()
	{
		return glm::inverse(getModelMatrix());   // Returning inverse of model matrix (view matrix)
	}
}