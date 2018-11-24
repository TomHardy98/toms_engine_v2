#include "Component.h"
#include "NonCopyable.h"

#include <memory>   // Allows for the use of pointers
#include <string>

namespace tomsengine
{
	class VertexArray;   // Gives access to the VertexArray class
	class Shader;   // Gives access to the Shader class
	class RenderTexture;
	class Texture;

	class MeshRenderer : public Component, private NonCopyable   // MeshRenderer class inherits from Component
	{
	public:

		bool isAlive = true;

		void onInit();   // Defining onInit function

		void chooseCube();
		void chooseCone();
		void choosePlane();
		void chooseSphere();
		void chooseCylinder();
		void chooseCustomMesh(const std::string& _mesh);

		void chooseTexture(const std::string& _texture);

		std::shared_ptr<VertexArray> shape;   // Creating a shared pointer of vertex array called shape

		std::shared_ptr<Texture> tex;   // Creating a shared pointer of texture called tex

		std::shared_ptr<RenderTexture> tempRt;

	private:

		void onReveal();   // Defining onReveal function

		std::shared_ptr<Shader> shader;   // Creating a shared pointer of shader called shader
		std::shared_ptr<Shader> lightkeyShader;
		std::shared_ptr<Shader> nullShader;
		std::shared_ptr<Shader> blurShader;
		std::shared_ptr<Shader> mergeShader;

		std::shared_ptr<RenderTexture> lightkeyRt;
		std::shared_ptr<RenderTexture> blurRt;
		std::shared_ptr<RenderTexture> blur2Rt;
		std::shared_ptr<RenderTexture> blur3Rt;
		std::shared_ptr<RenderTexture> mergeRt;
	};
}