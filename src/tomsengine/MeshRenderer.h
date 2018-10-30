#include "Component.h"
#include "Texture.h"

#include <memory>

namespace tomsengine
{
	class VertexArray;
	class Shader;

	class MeshRenderer : public Component
	{
	public:
		void onInit();

	private:
		void onReveal();

		std::shared_ptr<VertexArray> shape;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Texture> tex;
	};
}