#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>   // Allows for the use of GLM
#include <glm/glm.hpp>

#include <string>   // Allows for the use of strings

namespace tomsengine
{
	class Texture
	{
		GLuint id;   // Declaring GLuint variable called id
		glm::vec2 size;   // Declaring vec2 variable called size

	public:

		Texture(std::string path);   // Declaring constructor taking one variable
		glm::vec2 getSize();   // Declaring vec2 getSize function
		GLuint getId();   // Declaring getId function
	};
}

#endif