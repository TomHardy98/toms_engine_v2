#include <iostream>   // Allows for the use of output to the command console
#include <glm/ext.hpp>   // Allows for the use of GLM

#include "MeshRenderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Transform.h"
#include "Entity.h"
#include "Camera.h"
#include "Core.h"
#include "Texture.h"
#include "RTComponent.h"

namespace tomsengine
{
	void MeshRenderer::onInit()   // MeshRenderer onInit function
	{
		shader = std::make_shared<Shader>("../data/shaders/vertexShader.vert", "../data/shaders/fragmentShader.frag");   /// Set shaders using txt files in data/shaders/ folder

		shape = std::make_shared<VertexArray>("../data/meshes/cube.obj");   /// Sets default shape to a cube

		tex = std::make_shared<Texture>("../data/textures/default_texture.jpg");   /// Set default texture to entity
	}

	void MeshRenderer::onReveal()   // MeshRenderer onReveal function
	{
		if (isAlive)
		{
			shader->setUniform("in_Model", getEntity()->getComponent<Transform>()->getModelMatrix());   /// Set the model matrix

			shader->setUniform("in_Projection", getCore()->getCurrCam()->getProjMatrix());   /// Set the projection matrix

			shader->setUniform("in_View", getCore()->getCurrCam()->getEntity()->getComponent<Transform>()->getViewMatrix());   /// Set the view matrix

			shader->setUniform("in_Texture", tex);   /// Set the texture

			shader->draw(shape);   /// Call the draw function using the shape passed in
		}
	}

	void MeshRenderer::chooseCube()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/cube.obj");   // Set shape to be a cube obj loaded in
	}

	void MeshRenderer::chooseCone()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/cone.obj");   // Set shape to be a cone obj loaded in
	}

	void MeshRenderer::choosePlane()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/plane.obj");   // Set shape to be a plane obj loaded in
	}

	void MeshRenderer::chooseSphere()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/sphere.obj");   // Set shape to be a sphere obj loaded in
	}

	void MeshRenderer::chooseCylinder()
	{
		shape = std::make_shared<VertexArray>("../data/meshes/cylinder.obj");   // Set shape to be a cylinder obj loaded in
	}

	void MeshRenderer::chooseCustomMesh(const std::string& _mesh)
	{
		shape = std::make_shared<VertexArray>(_mesh);   // Set shape to be a custom obj loaded in
	}

	void MeshRenderer::chooseTexture(const std::string& _texture)
	{
		tex = std::make_shared<Texture>(_texture);   // Set texture to be a custom image loaded in
	}
}