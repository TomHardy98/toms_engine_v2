#include "MeshRenderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Transform.h"
#include "Entity.h"
#include "Camera.h"
#include "Core.h"

#include <iostream>   // Allows for the use of output to the command console
#include <glm/ext.hpp>   // Allows for the use of GLM

namespace tomsengine
{
	void MeshRenderer::onInit()   // MeshRenderer onInit function
	{
		shader = std::make_shared<Shader>("../data/shaders/vertexShader.txt", "../data/shaders/fragmentShader.txt");   // Set shaders using txt files in data/shaders/ folder
		//shape = std::make_shared<VertexArray>("../data/meshes/cube.obj");   // Default shape
		tex = std::make_shared<Texture>("../data/textures/dog.png");   // Set texture using png/jpg file in data/textures/ folder
	}

	void MeshRenderer::onReveal()   // MeshRenderer onReveal function
	{
		shader->setUniform("in_Model", getEntity()->getComponent<Transform>()->getModelMatrix());   // Set the model matrix
		
		shader->setUniform("in_Projection", getCore()->getCurrCam()->getProjMatrix());   // Set the projection matrix
		
		shader->setUniform("in_View", getCore()->getCurrCam()->getEntity()->getComponent<Transform>()->getViewMatrix());	  // Set the view matrix
		
		shader->setUniform("in_Texture", tex);   // Set the texture

		shader->draw(shape);   // Shader calls draw function using obj given
	}

	void MeshRenderer::chooseCube()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/cube.obj");
	}

	void MeshRenderer::chooseCone()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/cone.obj");
	}
}