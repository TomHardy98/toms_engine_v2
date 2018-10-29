#include "MeshRenderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"

#include <iostream>

namespace tomsengine
{
	void MeshRenderer::onInit()
	{
		std::shared_ptr<VertexBuffer> positions = std::make_shared<VertexBuffer>();
		positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
		positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
		positions->add(glm::vec3(0.5f, -0.5f, 0.0f));

		std::shared_ptr<VertexBuffer> colors = std::make_shared<VertexBuffer>();
		colors->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		colors->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		colors->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

		shape = std::make_shared<VertexArray>();
		shape->setBuffer("in_Position", positions);
		shape->setBuffer("in_Color", colors);

		shader = std::make_shared<Shader>("../data/shaders/vertexShader.txt", "../data/shaders/fragmentShader.txt");
	}

	void MeshRenderer::onReveal()
	{
		shader->setUniform("in_Model", glm::mat4(1.0f));
		shader->setUniform("in_Projection", glm::mat4(1.0f));
		shader->draw(*shape);
	}
}