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

	shared<Entity> entity = core->addEntity();   // Create an in-game object (entity with a transform component) and add it to the core

	shared<MeshRenderer> mr = entity->addComponent<MeshRenderer>();   // Add a mesh renderer to the 'entity' inside 'core'

	shared<Entity> entity2 = core->addEntity();   // Create an in-game object (entity with a transform component) and add it to the core

	shared<MeshRenderer> mr2 = entity2->addComponent<MeshRenderer>();   // Add a mesh renderer to the 'entity' inside 'core'

	shared<Audio> au = std::make_shared<Audio>("../data/audio/dixie_horn.ogg");   // Add an audio clip

	au->play();   // Play the audio clip

	entity->getComponent<Transform>()->Translate(-3.0f, -2.5f, 0.0f);   // Move entity component using transform component
	entity->getComponent<Transform>()->Rotate(-10.0f, 0.0f, 0.0f);   // Rotate entity component using transform component
	//entity->getComponent<Transform>()->Scale(0.5f, 0.5f, 0.5f);   // Scale entity component using transform component

	entity2->getComponent<Transform>()->Translate(3.0f, -2.5f, 0.0f);
	entity2->getComponent<Transform>()->Rotate(-10.0f, 0.0f, 0.0f);

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