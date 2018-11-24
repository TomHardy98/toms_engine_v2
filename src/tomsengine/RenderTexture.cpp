#include "RenderTexture.h"

namespace tomsengine
{
	RenderTexture::RenderTexture(int width, int height) : Texture(width, height)
	{
		glGenFramebuffers(1, &fbo);   /// Generating a frame buffer at location 1 and tagging with fbo
		if (!fbo) throw std::exception();   // If fbo doesnt exist throw an exception
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);   /// Bind the frame buffer using the created buffer

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);   /// Attach a texture image to the framebuffer

		GLuint rbo = 0;
		glGenRenderbuffers(1, &rbo);   /// Generating a render buffer at location 1 and tagging with rbo
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);   // Bind the render buffer using the created buffer
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);   /// Create and initialise the render buffer data store
		glBindRenderbuffer(GL_RENDERBUFFER, 0);   // Bind the render buffer to 0
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);   /// Attach the render buffer to the frame buffer

		glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Bind the frame buffer back to 0
	}

	GLuint RenderTexture::getFbId()
	{
		return fbo;
	}

	void RenderTexture::clear()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);   /// Bind the frame buffer with the fbo
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Clear the colour screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   /// Clear the bit buffer and the depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Bind the frame buffer back to 0
	}
}