#include <memory>   // Allows for the use of pointers (shared, weak, etc)
#include <exception>   // Allows for the use of exceptions to be thrown
#include <iostream>   // Allows for the use of text output to the console

#include <tomsengine/tomsengine.h>   // Allows for a cleaner include directory as all local includes are provided in here

#define shared std::shared_ptr   // Define what a shared pointer is, just use the word 'shared'
#define weak std::weak_ptr   // Define what a weak pointer is, just use the word 'weak'

using namespace tomsengine;

void safe_main()
{
	shared<Core> core = std::make_shared<Core>();   // Initialize the engine (SDL) and name it 'core'

	shared<Entity> entity = core->addEntity();   // Create an in-game object (entity) and add it to the core

	shared<MeshRenderer> mr = entity->addComponent<MeshRenderer>();   // Add a mesh renderer to the 'entity' inside 'core'

	shared<Audio> au = std::make_shared<Audio>("../data/audio/dixie_horn.ogg");   // Add an audio clip

	au->play();   // Play the audio clip

	core->Start();   // Start the main engine loop
}

int main()
{
	safe_main();   // Call safe_main function

	/*try
	{
		safe_main();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}*/

	return 0;
}