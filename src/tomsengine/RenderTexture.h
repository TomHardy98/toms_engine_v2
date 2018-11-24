#ifndef RENDERTEXTURE_H
#define RENDERTEXTURE_H

#include "Texture.h"

namespace tomsengine
{
	class RenderTexture : public Texture   /// Inherits from texture class
	{
	public:

		RenderTexture(int width, int height);   // RenderTexture function

		GLuint getFbId();   /// Used to get fbo from private
		void clear();   // Function declaration to clear render texture

	private:

		GLuint fbo;   /// Used to identify fbo

	};
}

#endif