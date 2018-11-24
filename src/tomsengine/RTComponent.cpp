#include "RTComponent.h"
#include "Shader.h"
#include "RenderTexture.h"

#define WINDOW_WIDTH 600   /// Defining window width
#define WINDOW_HEIGHT 900   /// Defining window height

namespace tomsengine
{
	void RTComponent::onInit()
	{
		lightkeyShader = std::make_shared<Shader>("../data/shaders/lightkeyShader.vert", "../data/shaders/lightkeyShader.frag");   // Initialising lightkeyShader

		nullShader = std::make_shared<Shader>("../data/shaders/nullShader.vert", "../data/shaders/nullShader.frag");   // Initialising nullShader

		blurShader = std::make_shared<Shader>("../data/shaders/blurShader.vert", "../data/shaders/blurShader.frag");   // Initialising blurShader

		mergeShader = std::make_shared<Shader>("../data/shaders/mergeShader.vert", "../data/shaders/mergeShader.frag");   // Initialising mergeShader

		// Creating render texture objects using window width and window height

		rt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);

		lightkeyRt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);

		blurRt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);

		blur2Rt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);

		blur3Rt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);

		mergeRt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	void RTComponent::onPostReveal()
	{
		rt->clear();   /// Clear the render texture

		glEnable(GL_CULL_FACE);   /// Enable cull faces
		glEnable(GL_DEPTH_TEST);   /// Enable depth test so it knows what to draw first and last

		lightkeyShader->setUniform("in_Texture", rt);   // Set the lightkeyShader uniform
		lightkeyShader->draw(lightkeyRt);   /// Draw the lightkeyShader to the rt on top of the screen

		blurShader->setUniform("in_Texture", lightkeyRt);
		blurShader->draw(blurRt);   /// Draw the blurShader to the rt on top of the screen

		blurShader->setUniform("in_Texture", blurRt);
		blurShader->draw(blur2Rt);   /// Draw the blurShader to the rt on top of the screen

		blurShader->setUniform("in_Texture", blur2Rt);
		blurShader->draw(blur3Rt);   /// Draw the blurShader to the rt on top of the screen

		mergeShader->setUniform("in_TextureA", rt);
		mergeShader->setUniform("in_TextureB", blur3Rt);
		mergeShader->draw(mergeRt);   /// Draw the mergeShader to the rt on top of the screen

		nullShader->setViewport(glm::vec4(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));   // Simple null shader setting the viewport to window width and height
		nullShader->setUniform("in_Texture", rt);   // Setting uniform for null shader
		nullShader->draw();   /// Drawing null shader to the 'simple shape'
	}
}