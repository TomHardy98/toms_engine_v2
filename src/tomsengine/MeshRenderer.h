#include "Component.h"
#include "Texture.h"
#include "NonCopyable.h"

#include <memory>   // Allows for the use of pointers

namespace tomsengine
{
	class VertexArray;   // Gives access to the VertexArray class
	class Shader;   // Gives access to the Shader class

	class MeshRenderer : public Component, private NonCopyable   // MeshRenderer class inherits from Component
	{
	public:
		void onInit();   // Defining onInit function

	private:
		void onReveal();   // Defining onReveal function

		std::shared_ptr<VertexArray> shape;   // Creating a shared pointer of vertex array called shape
		std::shared_ptr<Shader> shader;   // Creating a shared pointer of shader called shader
		std::shared_ptr<Texture> tex;   // Creating a shared pointer of texture called tex
	};
}