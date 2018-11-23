#include "Component.h"

namespace tomsengine
{
	class Shader;
	class RenderTexture;

	class RTComponent : public Component
	{
	public:

		std::shared_ptr<RenderTexture> rt;

		void onInit();

		void onPostReveal();

	private:

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