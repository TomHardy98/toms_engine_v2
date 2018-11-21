#include "MeshRenderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Transform.h"
#include "Entity.h"
#include "Camera.h"
#include "Core.h"
#include "RenderTexture.h"

#include <iostream>   // Allows for the use of output to the command console
#include <glm/ext.hpp>   // Allows for the use of GLM

#define WINDOW_WIDTH 1200   // Defining window width
#define WINDOW_HEIGHT 800   // Defining window height

namespace tomsengine
{
	void MeshRenderer::onInit()   // MeshRenderer onInit function
	{
		shader = std::make_shared<Shader>("../data/shaders/vertexShader.vert", "../data/shaders/fragmentShader.frag");   // Set shaders using txt files in data/shaders/ folder

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

		shape = std::make_shared<VertexArray>("../data/meshes/cube.obj");   // Sets default shape to a cube

		tex = std::make_shared<Texture>("../data/textures/default_texture.jpg");   // Set default texture to entity
	}

	void MeshRenderer::onReveal()   // MeshRenderer onReveal function
	{
		rt->clear();

		shader->setUniform("in_Model", getEntity()->getComponent<Transform>()->getModelMatrix());   // Set the model matrix
		
		shader->setUniform("in_Projection", getCore()->getCurrCam()->getProjMatrix());   // Set the projection matrix
		
		shader->setUniform("in_View", getCore()->getCurrCam()->getEntity()->getComponent<Transform>()->getViewMatrix());	  // Set the view matrix
		
		shader->setUniform("in_Texture", tex);   // Set the texture

		shader->draw(rt, shape);   // Shader calls draw function using obj given

		glDisable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		lightkeyShader->setUniform("in_Texture", rt);
		lightkeyShader->draw(lightkeyRt, shape);

		blurShader->setUniform("in_Texture", lightkeyRt);
		blurShader->draw(blurRt, shape);

		blurShader->setUniform("in_Texture", blurRt);
		blurShader->draw(blur2Rt, shape);

		blurShader->setUniform("in_Texture", blur2Rt);
		blurShader->draw(blur3Rt, shape);

		mergeShader->setUniform("in_TextureA", rt);
		mergeShader->setUniform("in_TextureB", blur3Rt);
		mergeShader->draw(mergeRt, shape);

		nullShader->setViewport(glm::vec4(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
		nullShader->setUniform("in_Texture", rt);
		nullShader->draw(shape);
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