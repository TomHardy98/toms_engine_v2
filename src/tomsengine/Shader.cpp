#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "RenderTexture.h"

#include <glm/ext.hpp>   // Allows for the use of GLM

#include <vector>   // Allows for the use of vectors
#include <fstream>   // Allows for the use of accessing external files
#include <iostream>   // Allows for the use of the command console

namespace tomsengine
{
	Shader::Shader(std::string vert, std::string frag)   // Shaders constructor
	{
		std::ifstream file(vert.c_str());   // Open vertex shader file
		std::string vertSrc;   // Create a string called vertSrc

		if (!file.is_open())   // If file didnt open
		{
			throw std::exception();   // Throw exception
		}

		while (!file.eof())   // While the end of the file hasnt been reached
		{
			std::string line;   // Create a string called line
			std::getline(file, line);   // Get the line its currently on
			vertSrc += line + "\n";   // Add line to vertSrc till the end of line is reached
		}

		file.close();   // Close file
		file.open(frag.c_str());   // Open fragment shader file
		std::string fragSrc;   // Create string called fragSrc

		if (!file.is_open())   // If file didnt open
		{
			throw std::exception();   // Throw exception
		}

		while (!file.eof())   // While the end of the file hasnt been reached
		{
			std::string line;   // Create a string called line
			std::getline(file, line);   // Get the line its currently on
			fragSrc += line + "\n";   // Add line to fragSrc till the end of line is reached
		}

		const GLchar *vs = vertSrc.c_str();   // Set a pointer to vs using the vertSrc string
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);   // Set vertexShaderId
		glShaderSource(vertexShaderId, 1, &vs, NULL);   // Set the shader source using id and vertSrc
		glCompileShader(vertexShaderId);   // Compile shader using id
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);   // Checks if shader has compiled correctly

		if (!success)   // If shader hasnt compiled correctly
		{
			throw std::exception();   // Throw exception
		}

		const GLchar *fs = fragSrc.c_str();   // Set a pointer to fs using the fragSrc string
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);   // Set fragmentShaderId
		glShaderSource(fragmentShaderId, 1, &fs, NULL);   // Set the shader source using id and fragSrc
		glCompileShader(fragmentShaderId);   // Compile shader using id
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);   // Checks if shader has compiled correctly

		if (!success)   // If shader hasnt compiled correctly
		{
			throw std::exception();   // Throw exception
		}

		id = glCreateProgram();   // Set id to glCreateProgram function
		glAttachShader(id, vertexShaderId);   // Create vertexShader program
		glAttachShader(id, fragmentShaderId);   // Create fragmentShader program
		glBindAttribLocation(id, 0, "in_Position");   // Associate 0 index with in position variable
		glBindAttribLocation(id, 1, "in_Color");   // Associate 1 index with in colour variable
		glBindAttribLocation(id, 2, "in_TexCoord");   // Associate 2 index with in texcoord variable
		glBindAttribLocation(id, 3, "in_Normal");   // Associate 3 index with in normal variable

		if (glGetError() != GL_NO_ERROR)   // If there is a GL error
		{
			throw std::exception();   // Throw exception
		}

		glLinkProgram(id);   // Link program using id
		glGetProgramiv(id, GL_LINK_STATUS, &success);   // Get shader program

		if (!success)   // If it fails to get shader program
		{
			throw std::exception();   // Throw exception
		}

		glDetachShader(id, vertexShaderId);   // Detach vertexShader
		glDeleteShader(vertexShaderId);   // Delete vertexShader
		glDetachShader(id, fragmentShaderId);   // Detach fragmentShader
		glDeleteShader(fragmentShaderId);   // Delete fragmentShader

		VertexBuffer *positions = new VertexBuffer();
		positions->add(glm::vec2(-1.0f, 1.0f));
		positions->add(glm::vec2(-1.0f, -1.0f));
		positions->add(glm::vec2(1.0f, -1.0f));
		positions->add(glm::vec2(1.0f, -1.0f));
		positions->add(glm::vec2(1.0f, 1.0f));
		positions->add(glm::vec2(-1.0f, 1.0f));

		VertexBuffer *texCoords = new VertexBuffer();
		texCoords->add(glm::vec2(0.0f, 0.0f));
		texCoords->add(glm::vec2(0.0f, -1.0f));
		texCoords->add(glm::vec2(1.0f, -1.0f));
		texCoords->add(glm::vec2(1.0f, -1.0f));
		texCoords->add(glm::vec2(1.0f, 0.0f));
		texCoords->add(glm::vec2(0.0f, 0.0f));

		simpleShape = std::make_shared<VertexArray>();
		simpleShape->setBuffer("in_Position", positions);
		simpleShape->setBuffer("in_TexCoord", texCoords);

	}

	void Shader::draw(std::shared_ptr<RenderTexture> renderTexture, std::shared_ptr<VertexArray> vertexArray)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, renderTexture->getFbId());
		glm::vec4 lastViewport = viewport;
		viewport = glm::vec4(0, 0, renderTexture->getSize().x, renderTexture->getSize().y);
		draw(vertexArray);
		viewport = lastViewport;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Shader::draw(std::shared_ptr<RenderTexture> renderTexture)
	{
		draw(renderTexture, simpleShape);
	}

	void Shader::draw()
	{
		draw(simpleShape);
	}

	void Shader::draw(std::shared_ptr<VertexArray> vertexArray)   // Shader draw function
	{
		//glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
		glUseProgram(id);   // Use program using id
		glBindVertexArray(vertexArray->getId());   // Bind the vertexArray shader

		for (size_t i = 0; i < samplers.size(); ++i)   // For the sampler vector size
		{
			glActiveTexture(GL_TEXTURE0 + i);   // Active texture at each sample

			if (samplers.at(i).texture)   // Get the texture at each sample
			{
				glBindTexture(GL_TEXTURE_2D, samplers.at(i).texture->getId());   // Bind the texture
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, 0);   // Else bind the texture at 0
			}
		}

		glDrawArrays(GL_TRIANGLES, 0, vertexArray->getVertexCount());   // Draw the object using vertexArray

		for (size_t i = 0; i < samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glBindVertexArray(0);   // Unbind vertexArray
		glUseProgram(0);   // Stop using program
	}

	void Shader::setUniform(std::string uniform, glm::vec4 value)   // Set uniform using vec4 function
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());   // Set uniformId

		if (uniformId == -1)   // If uniformId failed to set
		{
			throw std::exception();   // Throw exception
		}

		glUseProgram(id);   // Use program using id
		glUniform4f(uniformId, value.x, value.y, value.z, value.w);   // Set uniform
		glUseProgram(0);   // Stop using program
	}

	void Shader::setUniform(std::string uniform, float value)   // Set uniform using float function
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());   // Set uniformId

		if (uniformId == -1)   // If uniformId failed to set
		{
			throw std::exception();   // Throw exception
		}

		glUseProgram(id);   // Use program using id
		glUniform1f(uniformId, value);   // Set uniform
		glUseProgram(0);   // Stop using program
	}

	void Shader::setUniform(std::string uniform, int value)
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());

		if (uniformId == -1)
		{
			throw std::exception();
		}

		glUseProgram(id);
		glUniform1i(uniformId, value);
		glUseProgram(0);
	}

	void Shader::setUniform(std::string uniform, glm::mat4 value)   // Set uniform using mat4 function
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());   // Set uniformId

		if (uniformId == -1)   // If uniformId failed to set
		{
			throw std::exception();   // Throw exception
		}

		glUseProgram(id);   // Use program using id
		glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(value));   // Set uniform
		glUseProgram(0);   // Stop using program
	}

	void Shader::setUniform(std::string uniform, std::shared_ptr<Texture> texture)   // Set uniform using texture function
	{
		GLint uniformId = glGetUniformLocation(id, uniform.c_str());   // Set uniformId

		if (uniformId == -1)   // If uniformId failed to set
		{
			throw std::exception();   // Throw exception
		}

		for (size_t i = 0; i < samplers.size(); i++)   // Loop through samplers vector
		{
			if (samplers.at(i).id == uniformId)   // If sampler at i has same id as uniform id
			{
				samplers.at(i).texture = texture;   // Set sampler at i's texture to texture

				glUseProgram(id);   // Use program using id
				glUniform1i(uniformId, i);   // Set uniform
				glUseProgram(0);   // Stop using program
				return;
			}
		}

		Sampler s;   // Create a sampler called s
		s.id = uniformId;   // Set s id to uniformId
		s.texture = texture;   // Set s texture to texture
		samplers.push_back(s);   // Put s into samplers vector

		glUseProgram(id);   // Use program using id
		glUniform1i(uniformId, samplers.size() - 1);   // Set uniform
		glUseProgram(0);   // Stop using program
	}

	GLuint Shader::getId()   // Shader getId function
	{
		return id;   // Return id
	}

	void Shader::setViewport(glm::vec4 viewport)
	{
		this->viewport = viewport;
	}
}