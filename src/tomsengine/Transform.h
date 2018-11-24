#include "Component.h"

#include <GL/glew.h>   // Allows for the use of GLM
#define GLM_FORCE_CTOR_INIT   // Forces vectors to be empty
#include <glm/gtc/matrix_transform.hpp>
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

		void Rotate(float x2, float y2, float z2);

		void Scale(float x3, float y3, float z3);

		glm::mat4 getModelMatrix();

		glm::mat4 getViewMatrix();

		glm::vec3 getPosition() { return position; }
		void setPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; }   // Used for setting default position of Entity

		glm::vec3 getRotation() { return rotation; }
		void setRotation(float x2, float y2, float z2) { rotation.x = x2; rotation.y = y2; rotation.z = z2; }   // Used for setting default rotation of Entity

		glm::vec3 getScale() { return scale; }
		void setScale(float x3, float y3, float z3) { scale.x = x3; scale.y = y3; scale.z = z3; }   // Used for setting default scale of Entity

		void setVelocity(float _velocity) { velocity = _velocity; }

		float velocity;

	private:

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::mat4 modelMatrix;
		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 rotationMatrix2;
		glm::mat4 rotationMatrix3;
		glm::mat4 scaleMatrix;
	};
}