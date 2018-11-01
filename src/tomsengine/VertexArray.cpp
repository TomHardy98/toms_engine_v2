#include "VertexArray.h"
#include "VertexBuffer.h"

#include <fstream>   // Allows for the use of reading external files
#include <iostream>   // Allows for the use of the command console

namespace tomsengine
{
	void VertexArray::splitStringWhitespace(std::string& input, std::vector<std::string>& output)   // VertexArray splitStringWhiteSpace function
	{
		std::string curr;   // Create string called curr

		output.clear();   // Clear the output

		for (size_t i = 0; i < input.length(); i++)   // Loop through the input vector
		{
			if (input.at(i) == ' ' ||   // If there is a space or end of line
				input.at(i) == '\r' ||   // If there is a space or end of line
				input.at(i) == '\n' ||   // If there is a space or end of line
				input.at(i) == '\t')   // If there is a space or end of line
			{
				if (curr.length() > 0)   // If curr length is greater than 0
				{
					output.push_back(curr);   // Push back curr to output vector
					curr = "";   // Set curr
				}
			}
			else
			{
				curr += input.at(i);   // add and set curr to input at i
			}
		}

		if (curr.length() > 0)   // If curr length is greater than 0
		{
			output.push_back(curr);   // Push back curr to output vector
		}
	}

	void VertexArray::splitString(std::string& input, char splitter, std::vector<std::string>& output)   // VertexArray splitString function
	{
		std::string curr;   // Create string called curr

		output.clear();   // Clear the output

		for (size_t i = 0; i < input.length(); i++)   // Loop through the input vector
		{
			if (input.at(i) == splitter)   // If input at i equals splitter
			{
				output.push_back(curr);   // Push back curr to output vector
				curr = "";   // Set curr
			}
			else
			{
				curr += input.at(i);   // add and set curr to input at i
			}
		}

		if (curr.length() > 0)   // If curr length is greater than 0
		{
			output.push_back(curr);   // Push back curr to output vector
		}
	}

	VertexArray::VertexArray(std::string path) : dirty(false)   // VertexArray constructor if dirty is false function
	{
		glGenVertexArrays(1, &id);   // Generate vertexArray using id

		if (!id)   //  If id doesnt exist
		{
			throw std::exception();   // Throw exception
		}

		buffers.resize(10);   // Resize buffers to 10
		std::ifstream file(path.c_str());   // Read in file using path string

		if (!file.is_open())   // If file doesnt open
		{
			throw std::exception();   // Throw exception
		}

		std::string line;   // Create string called line
		std::vector<std::string> splitLine;   // Create vector of strings called splitLine
		std::vector<glm::vec3> positions;   // Create vector of vec3's called positions
		std::vector<glm::vec2> texCoords;   // Create vector of vec2's called texCoords
		std::vector<glm::vec3> normals;   // Create vector of vec3's called normals

		VertexBuffer *positionBuffer = NULL;   // Create VertexBuffer pointer called positionBuffer set to NULL
		VertexBuffer *texCoordBuffer = NULL;   // Create VertexBuffer pointer called texCoordBuffer set to NULL
		VertexBuffer *normalBuffer = NULL;   // Create VertexBuffer pointer called normalBuffer set to NULL

		while (!file.eof())   // While end of file hasnt been reached
		{
			std::getline(file, line);   // Get line
			if (line.length() < 1) continue;   // If line is less than 1, continue
			splitStringWhitespace(line, splitLine);   // Call splitStringWhitespace function
			if (splitLine.size() < 1) continue;   // If splitLine size is less than 1, continue

			if (splitLine.at(0) == "v")   // If splitLine at 0 equals v
			{
				if (!positionBuffer) positionBuffer = new VertexBuffer();   // If positionBuffer doesnt exist, create one

				positions.push_back(glm::vec3(
					atof(splitLine.at(1).c_str()),
					atof(splitLine.at(2).c_str()),
					atof(splitLine.at(3).c_str())));   // Push back positions
			}
			else if (splitLine.at(0) == "vt")   // If splitLine at 0 equals vt
			{
				if (!texCoordBuffer) texCoordBuffer = new VertexBuffer();   // If texCoordBuffer doesnt exist, create one

				texCoords.push_back(glm::vec2(
					atof(splitLine.at(1).c_str()),
					1.0f - atof(splitLine.at(2).c_str())));   // Push back positions
			}
			else if (splitLine.at(0) == "vn")   // If splitLine at 0 equals vn
			{
				if (!normalBuffer) normalBuffer = new VertexBuffer();   // If normalBuffer doesnt exist, create one

				normals.push_back(glm::vec3(
					atof(splitLine.at(1).c_str()),
					atof(splitLine.at(2).c_str()),
					atof(splitLine.at(3).c_str())));   // Push back positions
			}
			else if (splitLine.at(0) == "f")   // If splitLine at 0 equals f
			{
				std::vector<std::string> subsplit;
				splitString(splitLine.at(1), '/', subsplit);

				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
				splitString(splitLine.at(2), '/', subsplit);
				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
				splitString(splitLine.at(3), '/', subsplit);
				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));

				if (splitLine.size() < 5) continue;
				splitString(splitLine.at(3), '/', subsplit);

				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
				splitString(splitLine.at(4), '/', subsplit);
				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
				splitString(splitLine.at(1), '/', subsplit);
				positionBuffer->add(positions.at(atoi(subsplit.at(0).c_str()) - 1));
				if (texCoordBuffer) texCoordBuffer->add(texCoords.at(atoi(subsplit.at(1).c_str()) - 1));
				if (normalBuffer) normalBuffer->add(normals.at(atoi(subsplit.at(2).c_str()) - 1));
			}
		}

		setBuffer("in_Position", positionBuffer);   // Set in_Position buffer to positionBuffer
		if (texCoordBuffer) setBuffer("in_TexCoord", texCoordBuffer);   // If texCoordBuffer exists, set it
		if (normalBuffer) setBuffer("in_Normal", normalBuffer);   // If normalBuffer exists, set it
	}

	VertexArray::VertexArray() : dirty(false)   // VertexArray constructor if dirty is false function
	{
		glGenVertexArrays(1, &id);   // Generate VertexArray using id

		if (!id)   // If id doesnt exist
		{
			throw std::exception();   // Throw exception
		}

		buffers.resize(10);   // Resize buffers vector to 10
	}

	void VertexArray::setBuffer(std::string attribute, VertexBuffer *buffer)   // VertexArray setBuffer function
	{
		if (attribute == "in_Position")   // If attribute equals in_Position
		{
			buffers.at(0) = buffer;   // Set buffer at 0 to buffer
		}
		else if (attribute == "in_Color")   // If attribute equals in_Colour
		{
			buffers.at(1) = buffer;   // Set buffer at 1 to buffer
		}
		else if (attribute == "in_TexCoord")   // If attribute equals in_TexCoord
		{
			buffers.at(2) = buffer;   // Set buffer at 2 to buffer
		}
		else if (attribute == "in_Normal")   // If attribute equals in_Normal
		{
			buffers.at(3) = buffer;   // Set buffer at 3 to buffer
		}
		else
		{
			throw std::exception();   // Throw exception
		}

		dirty = true;   // Set dirty to true
	}

	int VertexArray::getVertexCount()   // VertexArray getVertexCount function
	{
		if (!buffers.at(0))   // If there is no buffer at 0
		{
			throw std::exception();   // Throw exception
		}

		return buffers.at(0)->getDataSize() / buffers.at(0)->getComponents();   // Return buffer at 0 size and buffer at 0 components
	}

	GLuint VertexArray::getId()   // VertexArray getId function
	{
		if (dirty)   // If dirty = true
		{
			glBindVertexArray(id);   // Bind VertexArray using id

			for (size_t i = 0; i < buffers.size(); i++)   // Loop through buffers vector
			{
				if (buffers.at(i))   // If buffers at i
				{
					glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->getId());   // Bind buffer using buffers at i, id

					glVertexAttribPointer(i, buffers.at(i)->getComponents(), GL_FLOAT, GL_FALSE,
						buffers.at(i)->getComponents() * sizeof(GLfloat), (void *)0);   // Define an array of vertex attribute data

					glEnableVertexAttribArray(i);   // Enable vertex attrib array at i
				}
				else
				{
					glDisableVertexAttribArray(i);   // Disable vertex attrib array at i
				}
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);   // Bind buffer to 0
			glBindVertexArray(0);   // Bind vertex array to 0
			dirty = false;   // Set dirty to false
		}

		return id;   // Return id
	}
}