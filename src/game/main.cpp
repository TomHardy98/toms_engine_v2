#include <memory>   // Allows for the use of pointers (shared, weak, etc)
#include <exception>   // Allows for the use of exceptions to be thrown
#include <iostream>   // Allows for the use of text output to the console
#include <tomsengine/tomsengine.h>   // Allows for a cleaner include directory as all local includes are provided in here

#define shared std::shared_ptr   // Define what a shared pointer is, just use the word 'shared'
#define weak std::weak_ptr   // Define what a weak pointer is, just use the word 'weak'

using namespace tomsengine;

class TestScreen : public tomsengine::Component
{
public:
	void onInit(std::string color)
	{
		//std::cout << "Initialise " << color << std::endl;
	}

	void onBegin()
	{
		//std::cout << "Begin " << std::endl;
	}

	void onTick()
	{
		//std::cout << "Tick" << std::endl;
	}

	void onReveal()
	{
		//std::cout << "Reveal" << std::endl;
	}
};

void safe_main()
{
	shared<Core> core = std::make_shared<Core>();   // Initialize the engine (SDL) and name it 'core'

	shared<Entity> entity = core->addEntity();   // Create an in-game object (entity) and add it to the core
	
	weak<TestScreen> testScreen = entity->addComponent<TestScreen>("Green");   // Add a simple component to it

	shared<MeshRenderer> mr = entity->addComponent<MeshRenderer>();   // Add a mesh renderer to the 'entity' inside 'core'
	shared<MeshRenderer> mr2 = entity->getComponent<MeshRenderer>();   // Loop through and get the components in the 'entity'

	core->Start();   // Start the main engine loop
}

int main()
{
	safe_main();

	/*try
	{
		safe_main();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}*/

	system("PAUSE");

	return 0;
}