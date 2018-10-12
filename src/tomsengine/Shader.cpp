#include "Shader.h"

#include <glm/ext.hpp>

#include <fstream>
#include <iostream>

Shader::Shader(std::string vert, std::string frag)
{
	std::ifstream file(vert.c_str());
	std::string vertSrc;

	if (!file.is_open())
	{
		throw std::exception();
	}

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		vertSrc += line + "\n";
	}

	file.close();
	file.open(frag.c_str());
	std::string fragSrc;

	if (!file.is_open())
	{
		throw std::exception();
	}

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		fragSrc += line + "\n";
	}

	const GLchar *vs = vertSrc.c_str();
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vs, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	const GLchar *fs = fragSrc.c_str();
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fs, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShaderId);
	glAttachShader(id, fragmentShaderId);
	glBindAttribLocation(id, 0, "in_Position");
	glBindAttribLocation(id, 1, "in_Color");

	if (glGetError() != GL_NO_ERROR)
	{
		throw std::exception();
	}

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	glDetachShader(id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

void Shader::draw()
{
	
}

GLuint Shader::getId()
{
	return id;
}