#include "Component.h"

#include <GL/glew.h>   // Allows for the use of GLM
#define GLM_FORCE_CTOR_INIT   // Forces vectors to be empty
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

		void Rotate(float x2, float y2, float z2);
		void Rotate(glm::vec3 &direction);

		void Scale(float x3, float y3, float z3);
		void Scale(glm::vec3 &scaleVal);

		glm::mat4 getModelMatrix();

		glm::vec3 getPosition() { return position; }
		void setPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; }

		glm::vec3 getRotation() { return rotation; }
		void setRotation(float x2, float y2, float z2) { rotation.x = x2; rotation.y = y2; rotation.z = z2; }

		glm::vec3 getScale() { return scale; }
		void setScale(float x3, float y3, float z3) { scale.x = x3; scale.y = y3; scale.z = z3; }

	private:

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}