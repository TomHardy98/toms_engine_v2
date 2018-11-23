#include <memory>   // Allows for the use of pointers (shared, weak, etc)
#include <exception>   // Allows for the use of exceptions to be thrown
#include <iostream>   // Allows for the use of text output to the console

#include <tomsengine/tomsengine.h>   // Allows for a cleaner include directory as all local includes are provided in here

#define shared std::shared_ptr   // Define what a shared pointer is, just use the word 'shared'
#define weak std::weak_ptr   // Define what a weak pointer is, just use the word 'weak'

using namespace tomsengine;

void safe_main()
{
	// Creating core
	shared<Core> core = std::make_shared<Core>();   // Initialize the engine (SDL) and name it 'core'
	std::shared_ptr<Core> ptr = core->getPtrToThis();   // Setting cores 'self'
	core->self = ptr;   // Setting cores 'self'

	// Creating main render texture object to draw scene
	//shared<Entity> renderTextureObject = core->addEntity();
	//renderTextureObject->addComponent<RTComponent>();

	// Creating main camera
	shared<Entity> mainCam = core->addEntity();
	mainCam->addComponent<Camera>();
	mainCam->getComponent<Transform>()->Translate(0.0f, 0.0f, 10.0f);

	// Creating cube (Every entity with a box collider automatically moves up and down)
	shared<Entity> cube = core->addEntity();

	shared<MeshRenderer> cubeMr = cube->addComponent<MeshRenderer>();
	cubeMr->chooseCube();
	cubeMr->chooseTexture("../data/textures/box.jpg");

	cube->addComponent<BoxCollider>();
	cube->getComponent<Transform>()->Scale(-0.5f, -0.5f, -0.5f);
	cube->getComponent<Transform>()->Translate(4.0f, 0.0f, 0.0f);

	// Creating cube2 (Every entity with a box collider automatically moves up and down)
	shared<Entity> cube2 = core->addEntity();

	shared<MeshRenderer> cubeMr2 = cube2->addComponent<MeshRenderer>();
	cubeMr2->chooseCube();
	cubeMr2->chooseTexture("../data/textures/box.jpg");

	cube2->addComponent<BoxCollider>();
	cube2->getComponent<Transform>()->Scale(-0.5f, -0.5f, -0.5f);
	cube2->getComponent<Transform>()->Translate(-3.0f, 0.0f, 0.0f);


	shared<Audio> au = std::make_shared<Audio>("../data/audio/dixie_horn.ogg");   // Add an audio clip

	au->play();   // Play the audio clip

	core->Start(mainCam);
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