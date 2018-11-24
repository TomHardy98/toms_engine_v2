#include <GL/glew.h>  // Allows for the use of GLM
#define GLM_FORCE_CTOR_INIT   // Forces vectors to be empty
#include <glm/glm.hpp>

#include <string>   // Allows for the use of strings
#include <vector>   // Allows for the use of vectors

namespace tomsengine
{
	class VertexArray;   // Gives access to the VertexArray class
	class Texture;   // Gives access to the Texture class
	class RenderTexture;

	struct Sampler   /// Creating a struct called Sampler
	{
		GLint id;   /// Declaring GLint variable called id
		std::shared_ptr<Texture> texture;   /// Declaring shared pointer of texture called texture
	};

	class Shader
	{
		GLuint id;   // Declaring GLint variable called id
		std::vector<Sampler> samplers;   // Declaring a vector of sampler called samplers
		glm::vec4 viewport;   // Creating a vec4 called viewport
		std::shared_ptr<VertexArray> simpleShape;   /// Creating a vertex array called simple shape to draw across whole screen

	public:

		Shader(std::string vert, std::string frag);   /// Shader constructor taking two variables
		void draw();
		void draw(std::shared_ptr<RenderTexture> renderTexture);
		void draw(std::shared_ptr<VertexArray> vertexArray);   // Declaring draw function taking a variable
		void draw(std::shared_ptr<RenderTexture> renderTexture, std::shared_ptr<VertexArray> vertexArray);   /// Declaring draw function to take a 'shape' and rendertexture
		void setUniform(std::string uniform, glm::vec4 value);   // Declaring a set uniform function taking a vec4
		void setUniform(std::string uniform, float value);   // Declaring a set uniform function taking a float
		void setUniform(std::string uniform, int value);
		void setUniform(std::string uniform, glm::mat4 value);   // Declaring a set uniform function taking a mat4
		void setUniform(std::string uniform, std::shared_ptr<Texture> texture);   // Declaring a set uniform function taking a texture
		GLuint getId();   // Declaring a getId function
		void setViewport(glm::vec4 viewport);   // Declaring function to set viewport
	};
}