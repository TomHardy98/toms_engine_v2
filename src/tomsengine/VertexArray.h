#include <GL/glew.h>   // Allows for the use of GLM
#define GLM_FORCE_CTOR_INIT   /// Forces vectors to be empty
#include <glm/glm.hpp>
#include <vector>   /// Allows for the use of vectors
#include <string>   /// Allows for the use of strings
#include <memory>   /// Allows for the use of pointers

namespace tomsengine
{
	class VertexBuffer;   /// Gives access to the VertexBuffer class

	class VertexArray
	{
	public:

		VertexArray();   // Declaring constructor for VertexArray
		VertexArray(std::string path);   // Declaring VertexArray constructor taking one variable
		void setBuffer(std::string attribute, VertexBuffer *buffer);   // Declaring setBuffer function taking two variables
		int getVertexCount();   // Declaring getVertexCount function
		GLuint getId();   // Declaring getId function

	private:

		GLuint id;   // Declaring GLuint variable called id
		bool dirty;   // Declaring bool called dirty
		std::vector<VertexBuffer *> buffers;   // Declaring a pointer to a vector of VertexBuffer called buffers

		void splitStringWhitespace(std::string& input, std::vector<std::string>& output);   /// Declaring function to take white spaces in strings
		void splitString(std::string& input, char splitter, std::vector<std::string>& output);   /// Declaring function to take no white spaces in strings
	};
}