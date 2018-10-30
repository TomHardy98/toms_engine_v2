#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace tomsengine
{
	class VertexArray;
	class Texture;

	struct Sampler
	{
		GLint id;
		std::shared_ptr<Texture> texture;
	};

	class Shader
	{
		GLuint id;
		std::vector<Sampler> samplers;

	public:

		Shader(std::string vert, std::string frag);
		void draw(std::shared_ptr<VertexArray> vertexArray);
		void setUniform(std::string uniform, glm::vec4 value);
		void setUniform(std::string uniform, float value);
		void setUniform(std::string uniform, glm::mat4 value);
		void setUniform(std::string uniform, std::shared_ptr<Texture> texture);
		GLuint getId();
	};
}