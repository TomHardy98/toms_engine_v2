#include "MeshRenderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Transform.h"
#include "Entity.h"

#include <iostream>   // Allows for the use of output to the command console
#include <glm/ext.hpp>   // Allows for the use of GLM

#define WINDOW_WIDTH 1200   // Defining window width
#define WINDOW_HEIGHT 800   // Defining window height

namespace tomsengine
{
	void MeshRenderer::onInit()   // MeshRenderer onInit function
	{
		shader = std::make_shared<Shader>("../data/shaders/vertexShader.txt", "../data/shaders/fragmentShader.txt");   // Set shaders using txt files in data/shaders/ folder
		shape = std::make_shared<VertexArray>("../data/meshes/cube.obj");   // Set shape or object using obj file in data/meshes/ folder
		tex = std::make_shared<Texture>("../data/textures/dog.png");   // Set texture using png/jpg file in data/textures/ folder
	}

	void MeshRenderer::onReveal()   // MeshRenderer onReveal function
	{
		shader->setUniform("in_Model", getEntity()->getComponent<Transform>()->getModelMatrix());   // Set the model matrix
		
		shader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f));   // Set the projection matrix
		
		shader->setUniform("in_View", camera->getComponent<Transform>()->getViewMatrix());	  // Set the view matrix
		
		shader->setUniform("in_Texture", tex);   // Set the texture

		shader->draw(shape);   // Shader calls draw function using obj given
	}
}