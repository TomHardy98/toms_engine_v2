#include "RTComponent.h"
#include "Shader.h"
#include "RenderTexture.h"

#define WINDOW_WIDTH 1200   // Defining window width
#define WINDOW_HEIGHT 800   // Defining window height

namespace tomsengine
{
	std::shared_ptr<RTComponent> grt;

	void RTComponent::onInit()
	{
		grt = std::make_shared<RTComponent>();

		lightkeyShader = std::make_shared<Shader>("../data/shaders/lightkeyShader.vert", "../data/shaders/lightkeyShader.frag");

		nullShader = std::make_shared<Shader>("../data/shaders/nullShader.vert", "../data/shaders/nullShader.frag");

		blurShader = std::make_shared<Shader>("../data/shaders/blurShader.vert", "../data/shaders/blurShader.frag");

		mergeShader = std::make_shared<Shader>("../data/shaders/mergeShader.vert", "../data/shaders/mergeShader.frag");

		rt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);

		lightkeyRt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);

		blurRt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);

		blur2Rt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);

		blur3Rt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);

		mergeRt = std::make_shared<RenderTexture>(WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	void RTComponent::onPostReveal()
	{
		rt->clear();

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);   // Enable depth test so it knows what to draw first and last

		lightkeyShader->setUniform("in_Texture", rt);
		lightkeyShader->draw(lightkeyRt);

		blurShader->setUniform("in_Texture", lightkeyRt);
		blurShader->draw(blurRt);

		blurShader->setUniform("in_Texture", blurRt);
		blurShader->draw(blur2Rt);

		blurShader->setUniform("in_Texture", blur2Rt);
		blurShader->draw(blur3Rt);

		mergeShader->setUniform("in_TextureA", rt);
		mergeShader->setUniform("in_TextureB", blur3Rt);
		mergeShader->draw(mergeRt);

		nullShader->setViewport(glm::vec4(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
		nullShader->setUniform("in_Texture", rt);
		nullShader->draw();
	}
}