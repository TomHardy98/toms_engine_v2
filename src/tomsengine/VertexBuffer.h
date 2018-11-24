#include <GL/glew.h>   // Allows for the use of GLM
#define GLM_FORCE_CTOR_INIT   /// Forces vectors to be empty
#include <glm/glm.hpp>
#include <vector>   /// Allows for the use of vectors

namespace tomsengine
{
	class VertexBuffer
	{
	public:

		VertexBuffer();   /// Constructor of VertexBuffer
		void add(glm::vec2 value);   // Declaring add function taking a vec2
		void add(glm::vec3 value);   // Declaring add function taking a vec3
		void add(glm::vec4 value);   // Declaring add function taking a vec4
		int getComponents();   // Declaring getComponents function
		int getDataSize();   // Declaring getDataSize function
		GLuint getId();   // Declaring getId function

	private:

		GLuint id;   // Declaring GLuint variable called id
		int components;   // Declaring int variable called components
		std::vector<GLfloat> data;   // Declaring vector of GLfloat called data
		bool dirty;   // Declaring bool called dirty
	};
}