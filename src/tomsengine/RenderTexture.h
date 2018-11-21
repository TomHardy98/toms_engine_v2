#ifndef RENDERTEXTURE_H
#define RENDERTEXTURE_H

#include "Texture.h"

namespace tomsengine
{
	class RenderTexture : public Texture
	{
		GLuint fbo;

	public:

		RenderTexture(int width, int height);

		GLuint getFbId();
		void clear();
	};
}

#endif