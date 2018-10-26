#include "Component.h"

#include <memory>

namespace tomsengine
{
	class VertexArray;
	class Shader;

	class MeshRenderer : public Component
	{
	public:
		void onInitialise();

	private:
		void onDisplay();

		std::shared_ptr<VertexArray> shape;
		std::shared_ptr<Shader> shader;
	};
}