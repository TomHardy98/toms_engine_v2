#include "Texture.h"

#include <stb_image/stb_image.h>   // Allows for the use of stb_image

namespace tomsengine
{
	Texture::Texture(std::string path)   // Texture constructor
	{
		int w = 0;   // Create int width
		int h = 0;   // Create int heigt
		int channels = 0;   // Create int channels

		unsigned char *data = stbi_load(path.c_str(), &w, &h, &channels, 4);   // Load texture data into *data

		if (!data)   // If data doesnt exist
		{
			throw std::exception();   // Throw exception
		}

		size.x = w;   // Set x size to w
		size.y = h;   // Set y size to h

		glGenTextures(1, &id);   // Generate texture names

		if (!id)   // If id doesnt exist
		{
			throw std::exception();   // Throw exception
		}

		glBindTexture(GL_TEXTURE_2D, id);   // Bind texture to id

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);   // Specify a 2D tex image

		free(data);   // Free the data

		glGenerateMipmap(GL_TEXTURE_2D);   // Generate mipmaps for the texture

		glBindTexture(GL_TEXTURE_2D, 0);   // Bind texture to 0
	}

	glm::vec2 Texture::getSize()   // Texture getSize function
	{
		return size;   // Return size
	}

	GLuint Texture::getId()   // Texture getId function
	{
		return id;   // Return id
	}
}