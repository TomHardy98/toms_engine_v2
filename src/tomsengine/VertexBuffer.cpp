#include "VertexBuffer.h"

namespace tomsengine
{
	VertexBuffer::VertexBuffer() : components(0), dirty(false)   // VertexBuffer constructor
	{
		glGenBuffers(1, &id);   // Generate a buffer to the id

		if (!id)   // If id doesnt exist
		{
			throw std::exception();   // Throw exception
		}
	}

	void VertexBuffer::add(glm::vec2 value)   // VertexBuffer add vec2 function
	{
		if (!components)   // If components doesnt exist
		{
			components = 2;   // Set components to 2
		}

		if (components != 2)   // If components isnt = to 2
		{
			throw std::exception();   // Throw exception
		}

		data.push_back(value.x);   /// Push back value x into data
		data.push_back(value.y);   /// Push back value y into data
		dirty = true;   // Set dirty to true
	}

	void VertexBuffer::add(glm::vec3 value)   // VertexBuffer add vec3 function
	{
		if (!components)   // If components doesnt exist
		{
			components = 3;   // Set components to 3
		}

		if (components != 3)   // If components isnt = to 3
		{
			throw std::exception();   // Throw exception
		}

		data.push_back(value.x);   /// Push back value x into data
		data.push_back(value.y);   /// Push back value y into data
		data.push_back(value.z);   /// Push back value z into data
		dirty = true;   // Set dirty to true
	}

	void VertexBuffer::add(glm::vec4 value)   // VertexBuffer add vec4 function
	{
		if (!components)   // If components doesnt exist
		{
			components = 4;   // Set components to 4
		}

		if (components != 4)   // If components isnt = to 4
		{
			throw std::exception();   // Throw exception
		}

		data.push_back(value.x);   /// Push back value x into data
		data.push_back(value.y);   /// Push back value y into data
		data.push_back(value.z);   /// Push back value z into data
		data.push_back(value.w);   /// Push back value w into data
		dirty = true;   // Set dirty to true
	}

	int VertexBuffer::getDataSize()   // VertexBuffer getDataSize function
	{
		return data.size();   // Return data size
	}

	int VertexBuffer::getComponents()   // VertexBuffer getComponents function
	{
		if (!components)   // If components doesnt exist
		{
			throw std::exception();   // Throw exception
		}

		return components;   // Return components
	}

	GLuint VertexBuffer::getId()   // VertexBuffer getId function
	{
		if (dirty)   // If dirty is true
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);   /// Bind array buffer to id
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.at(0), GL_STATIC_DRAW);   /// Set buffer data
			glBindBuffer(GL_ARRAY_BUFFER, 0);   /// Bind array buffer to 0
			dirty = false;   // Set dirty to false
		}

		return id;   // Return id
	}
}