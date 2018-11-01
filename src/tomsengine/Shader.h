#include <GL/glew.h>  // Allows for the use of GLM
#include <glm/glm.hpp>

#include <string>   // Allows for the use of strings
#include <vector>   // Allows for the use of vectors

namespace tomsengine
{
	class VertexArray;   // Gives access to the VertexArray class
	class Texture;   // Gives access to the Texture class

	struct Sampler   // Creating a struct called Sampler
	{
		GLint id;   // Declaring GLint variable called id
		std::shared_ptr<Texture> texture;   // Declaring shared pointer of texture called texture
	};

	class Shader
	{
		GLuint id;   // Declaring GLint variable called id
		std::vector<Sampler> samplers;   // Declaring a vector of sampler called samplers

	public:

		Shader(std::string vert, std::string frag);   // Shader constructor taking two variables
		void draw(std::shared_ptr<VertexArray> vertexArray);   // Declaring draw function taking a variable
		void setUniform(std::string uniform, glm::vec4 value);   // Declaring a set uniform function taking a vec4
		void setUniform(std::string uniform, float value);   // Declaring a set uniform function taking a float
		void setUniform(std::string uniform, glm::mat4 value);   // Declaring a set uniform function taking a mat4
		void setUniform(std::string uniform, std::shared_ptr<Texture> texture);   // Declaring a set uniform function taking a texture
		GLuint getId();   // Declaring a getId function
	};
}