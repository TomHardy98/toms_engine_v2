#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

class Shader
{
	GLuint id;

public:
	Shader(std::string vert, std::string frag);
	void draw();
	GLuint getId();
};