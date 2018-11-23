#include "MeshRenderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Transform.h"
#include "Entity.h"
#include "Camera.h"
#include "Core.h"
#include "Texture.h"
#include "RTComponent.h"

#include <iostream>   // Allows for the use of output to the command console
#include <glm/ext.hpp>   // Allows for the use of GLM

namespace tomsengine
{
	void MeshRenderer::onInit()   // MeshRenderer onInit function
	{
		shader = std::make_shared<Shader>("../data/shaders/vertexShader.vert", "../data/shaders/fragmentShader.frag");   // Set shaders using txt files in data/shaders/ folder

		shape = std::make_shared<VertexArray>("../data/meshes/cube.obj");   // Sets default shape to a cube

		tex = std::make_shared<Texture>("../data/textures/default_texture.jpg");   // Set default texture to entity
	}

	void MeshRenderer::onReveal()   // MeshRenderer onReveal function
	{
		shader->setUniform("in_Model", getEntity()->getComponent<Transform>()->getModelMatrix());   // Set the model matrix
		
		shader->setUniform("in_Projection", getCore()->getCurrCam()->getProjMatrix());   // Set the projection matrix
		
		shader->setUniform("in_View", getCore()->getCurrCam()->getEntity()->getComponent<Transform>()->getViewMatrix());	  // Set the view matrix
		
		shader->setUniform("in_Texture", tex);   // Set the texture

		if (getEntity()->hasComponent<RTComponent>() == true)
		{
			tempRt = getEntity()->getComponent<RTComponent>()->rt;
			shader->draw(tempRt, shape);
		}
		else
		{
			shader->draw(shape);
		}
	}

	void MeshRenderer::chooseCube()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/cube.obj");
	}

	void MeshRenderer::chooseCone()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/cone.obj");
	}

	void MeshRenderer::choosePlane()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/plane.obj");
	}

	void MeshRenderer::chooseSphere()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/sphere.obj");
	}

	void MeshRenderer::chooseCylinder()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/cylinder.obj");
	}

	void MeshRenderer::chooseCustomMesh(const std::string& _mesh)
	{
		shape = std::make_shared<VertexArray>(_mesh);
	}

	void MeshRenderer::chooseTexture(const std::string& _texture)
	{
		tex = std::make_shared<Texture>(_texture);
	}
}