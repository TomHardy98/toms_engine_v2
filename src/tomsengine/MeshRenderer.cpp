#include "MeshRenderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"

#include <iostream>
#include <glm/ext.hpp>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

namespace tomsengine
{
	void MeshRenderer::onInit()
	{
		shader = std::make_shared<Shader>("../data/shaders/vertexShader.txt", "../data/shaders/fragmentShader.txt");
		shape = std::make_shared<VertexArray>("../data/meshes/cube.obj");
		tex = std::make_shared<Texture>("../data/textures/dog.png");
	}

	void MeshRenderer::onReveal()
	{
		shader->setUniform("in_Model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)));
		
		shader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f));
		
		shader->setUniform("in_View", glm::mat4(1.0f));	
		
		shader->setUniform("in_Texture", tex);

		shader->draw(shape);
	}
}