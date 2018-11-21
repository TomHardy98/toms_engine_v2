#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>   // Allows for the use of GLM
#define GLM_FORCE_CTOR_INIT   // Forces vectors to be empty
#include <glm/glm.hpp>

#include <string>   // Allows for the use of strings

#include "NonCopyable.h"

namespace tomsengine
{
	class RenderTexture;

	class Texture : private NonCopyable
	{
		friend class RenderTexture;

		GLuint id;   // Declaring GLuint variable called id
		glm::vec2 size;   // Declaring vec2 variable called size

		Texture(int width, int height);

	public:

		Texture(std::string path);   // Declaring constructor taking one variable
		glm::vec2 getSize();   // Declaring vec2 getSize function
		GLuint getId();   // Declaring getId function
	};
}

#endif