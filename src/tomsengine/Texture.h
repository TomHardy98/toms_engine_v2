#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

namespace tomsengine
{
	class Texture
	{
		GLuint id;
		glm::vec2 size;

	public:

		Texture(std::string path);
		glm::vec2 getSize();
		GLuint getId();
	};
}

#endif