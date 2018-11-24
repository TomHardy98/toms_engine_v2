#include "Component.h"
#include "NonCopyable.h"

#include <memory>   // Allows for the use of pointers
#include <string>

namespace tomsengine
{
	class VertexArray;   // Gives access to the VertexArray class
	class Shader;   // Gives access to the Shader class
	class RenderTexture;   // Gives access to the RenderTexture class
	class Texture;   // Gives access to the Texture class

	class MeshRenderer : public Component, private NonCopyable   /// MeshRenderer class inherits from Component, also NonCopyable
	{
	public:

		bool isAlive = true;   // Setting all mesh renderers to be alive or drawn

		void onInit();   // Defining onInit function

		void chooseCube();   // Defining chooseCube function
		void chooseCone();   // Defining chooseCone function
		void choosePlane();   // Defining choosePlane function
		void chooseSphere();   // Defining chooseSphere function
		void chooseCylinder();   // Defining chooseCylinder function
		void chooseCustomMesh(const std::string& _mesh);   // Defining chooseCustomMesh function

		void chooseTexture(const std::string& _texture);   // Defining chooseTexture function

		std::shared_ptr<VertexArray> shape;   // Creating a shared pointer of vertex array called shape

		std::shared_ptr<Texture> tex;   // Creating a shared pointer of texture called tex

		std::shared_ptr<RenderTexture> tempRt;   // Creating a temporary render texture

	private:

		void onReveal();   // Defining onReveal function

		std::shared_ptr<Shader> shader;   // Creating a shared pointer of shader called shader
		std::shared_ptr<Shader> lightkeyShader;   // Creating a shared pointer of shader called lightkeyShader
		std::shared_ptr<Shader> nullShader;   // Creating a shared pointer of shader called nullShader
		std::shared_ptr<Shader> blurShader;    // Creating a shared pointer of shader called blurShader
		std::shared_ptr<Shader> mergeShader;   // Creating a shared pointer of shader called mergeShader

		std::shared_ptr<RenderTexture> lightkeyRt;   // Creating a shared pointer of rendertexture called lightkeyRt
		std::shared_ptr<RenderTexture> blurRt;   // Creating a shared pointer of rendertexture called blurRt
		std::shared_ptr<RenderTexture> blur2Rt;   // Creating a shared pointer of rendertexture called blur2Rt
		std::shared_ptr<RenderTexture> blur3Rt;   // Creating a shared pointer of rendertexture called blur3Rt
		std::shared_ptr<RenderTexture> mergeRt;   // Creating a shared pointer of rendertexture called mergeRt
	};
}