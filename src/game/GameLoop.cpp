#include "GameLoop.h"
#include <iostream>
#include <ctime>   // Allows for the use of srand

#define shared std::shared_ptr   // Define what a shared pointer is, just use the word 'shared'
#define weak std::weak_ptr   // Define what a weak pointer is, just use the word 'weak'

using namespace tomsengine;   // Allows for the use of tomsengine classes

void GameLoop::Start()
{
	float randNum = 0.0f;
	float randScale = 0.0f;
	int randMax = 5;
	int randScaleMax = 4;

	srand(time(NULL));   // Initialises srand by using every second since 1970

	/// Creating core
	shared<Core> core = std::make_shared<Core>();   /// Initialize the engine (SDL) and name it 'core'
	std::shared_ptr<Core> ptr = core->getPtrToThis();   /// Setting cores 'self'
	core->self = ptr;   /// Setting cores 'self'

	/// Creating main camera
	shared<Entity> mainCam = core->addEntity();   /// Adding entity to the core
	mainCam->addComponent<Camera>();   /// Adding camera component to entity
	mainCam->getComponent<Transform>()->Translate(0.0f, -6.5f, 12.0f);   /// Accessing transform component to translate the entity

	shared<Entity> background = core->addEntity();  // Adding entity to the core
	shared<MeshRenderer> backgroundMr = background->addComponent<MeshRenderer>();   /// Adding a mesh renderer component to the entity
	backgroundMr->chooseCube();   /// Choosing the cube preset for the desired mesh
	backgroundMr->chooseTexture("../data/textures/space.jpg");   /// Choosing a custom texture
	background->getComponent<Transform>()->Translate(0.0f, 5.0f, -10.0f);  // Translating to correct position
	background->getComponent<Transform>()->Rotate(110.0f, 0.0f, 0.0f);   // Rotating to the correct direction
	background->getComponent<Transform>()->Scale(20.0f, 20.0f, 0.0f);   // Scaling to the right size

	/// Creating player
	shared<Entity> player = core->addEntity();   // Adding entity to the core

	shared<MeshRenderer> playerMr = player->addComponent<MeshRenderer>();   // Adding mesh renderer component to entity
	playerMr->chooseCustomMesh("../data/meshes/ufo.obj");   // Choosing custom mesh
	playerMr->chooseTexture("../data/textures/ufo.png");   // Choosing custom texture

	player->addComponent<Player>();   /// Adding player component to entity to use as a 'tag' to find player later in entities vector
	player->addComponent<BoxCollider>();   // Adding box collider component
	player->getComponent<Transform>()->Translate(0.0f, -6.5f, 0.0f);   // Translating entity
	player->getComponent<Transform>()->Rotate(0.0f, 55.0f, 0.0f);   // Rotating entity


	/// Creating enemies on right side
	for (float i = -4.0f; i < 17.0f; i+= 2.0f)   // Making a preset amount of enemies for the scene
	{
		randNum = (rand() % randMax + 1);   // Generating a random value
		randNum = randNum / 100;   // Making the random value a float

		randScale = (rand() % randScaleMax + 3);   // Generating a random value
		randScale = randScale / 10;   // Making the random value a float

		shared<Entity> cube = core->addEntity();   // Adding entity to the core

		shared<MeshRenderer> cubeMr = cube->addComponent<MeshRenderer>();   // Adding mesh renderer
		cubeMr->chooseCustomMesh("../data/meshes/meteor.obj");   // Choosing custom mesh
		cubeMr->chooseTexture("../data/textures/asteroid.jpg");   // Choosing custom texture

		cube->addComponent<Enemy>();   /// Adding enemy component to entity to use as a 'tag' to find enemies later in the entities vector
		cube->addComponent<BoxCollider>();   // Adding box collider
		cube->getComponent<Transform>()->setVelocity(randNum);   /// Setting enemies velocities at random
		cube->getComponent<Transform>()->Scale(-randScale, -randScale, -randScale);   /// Setting enemies size at random
		cube->getComponent<Transform>()->Translate(0.0f, i, 0.0f);   /// Setting enemies positions at iterations of 2
	}

	/// Creating enemies on left side
	for (float i = -3.5f; i < 17.0f; i += 2.0f)
	{
		randNum = (rand() % randMax + 1);
		randNum = randNum / 100;

		randScale = (rand() % randScaleMax + 1);
		randScale = randScale / 10;

		shared<Entity> cube2 = core->addEntity();

		shared<MeshRenderer> cubeMr2 = cube2->addComponent<MeshRenderer>();
		cubeMr2->chooseCustomMesh("../data/meshes/meteor.obj");
		cubeMr2->chooseTexture("../data/textures/asteroid.jpg");

		cube2->addComponent<Enemy>();
		cube2->addComponent<BoxCollider>();
		cube2->getComponent<Transform>()->setVelocity(randNum);
		cube2->getComponent<Transform>()->Scale(-randScale, -randScale, -randScale);
		cube2->getComponent<Transform>()->Translate(-3.0f, i, 0.0f);
	}

	shared<Audio> au = std::make_shared<Audio>("../data/audio/space_invaders.ogg");   /// Add an audio clip

	au->play();   /// Play the audio clip

	core->Start(mainCam);   /// Starting the engine and passing in main camera for movement
}