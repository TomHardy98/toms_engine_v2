#include <tomsengine/tomsengine.h>
#include <memory>

#define shared std::shared_ptr
#define weak std::weak_ptr

using namespace tomsengine;

int main()
{
	// Initialize the engine
	shared<Core> core = Core::initialize();

    // Create an in-game object
	shared<Entity> entity = core->addEntity();
	
	// Add a simple component to it
	weak<TestScreen> testScreen = entity->addComponent<TestScreen>();

	// Start the engine loop
	core->start();

	return 0;
}