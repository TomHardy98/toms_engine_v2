#include "Component.h"

#include <GL/glew.h>   // Allows for the use of GLM
#include <glm/glm.hpp>
#include <memory>   // Allows for the use of pointers

namespace tomsengine
{
	class Transform : public Component
	{
	public:

		Transform();
		~Transform();

		void Translate(float x, float y, float z);
		void Translate(glm::vec3 &direction);

		void Rotate(float x, float y, float z);
		void Rotate(glm::vec3 &direction);

		void Scale(float x, float y, float z);
		void Scale(glm::vec3 &scaleVal);

		glm::mat4 getModelMatrix();

		glm::vec3 getPosition() { return position; }
		void setPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; }

		glm::vec3 getRotation() { return rotation; }
		void setRotation(float x, float y, float z) { rotation.x = x; rotation.y = y; rotation.z = z; }

		glm::vec3 getScale() { return scale; }
		void setScale(float x, float y, float z) { scale.x = x; scale.y = y; scale.z = z; }

	private:

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}