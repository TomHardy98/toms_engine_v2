#include "Component.h"

namespace tomsengine
{
	class Shader;   // Can access shader class
	class RenderTexture;   // Can access render texture class

	class RTComponent : public Component   /// Inherits from component class
	{
	public:

		std::shared_ptr<RenderTexture> rt;   // Creates a shared pointer of render texture named 'rt'

		void onInit();   /// Overriden onInit function declaration

		void onPostReveal();   /// Overriden onPostReveal function declaration

	private:

		std::shared_ptr<Shader> lightkeyShader;   /// Shared pointer of shader variables
		std::shared_ptr<Shader> nullShader;
		std::shared_ptr<Shader> blurShader;
		std::shared_ptr<Shader> mergeShader;

		std::shared_ptr<RenderTexture> lightkeyRt;   /// Shared pointer of render texture variables
		std::shared_ptr<RenderTexture> blurRt;
		std::shared_ptr<RenderTexture> blur2Rt;
		std::shared_ptr<RenderTexture> blur3Rt;
		std::shared_ptr<RenderTexture> mergeRt;
	};
}