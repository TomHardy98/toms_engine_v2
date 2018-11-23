#include "GameLoop.h"
#include <iostream>

#define shared std::shared_ptr   // Define what a shared pointer is, just use the word 'shared'
#define weak std::weak_ptr   // Define what a weak pointer is, just use the word 'weak'

using namespace tomsengine;

void GameLoop::Start()
{
	// Creating core
	shared<Core> core = std::make_shared<Core>();   // Initialize the engine (SDL) and name it 'core'
	std::shared_ptr<Core> ptr = core->getPtrToThis();   // Setting cores 'self'
	core->self = ptr;   // Setting cores 'self'

	// Creating main camera
	shared<Entity> mainCam = core->addEntity();
	mainCam->addComponent<Camera>();
	mainCam->getComponent<Transform>()->Translate(0.0f, 5.0f, 10.0f);

	shared<Entity> background = core->addEntity();
	shared<MeshRenderer> backgroundMr = background->addComponent<MeshRenderer>();
	backgroundMr->chooseCube();
	backgroundMr->chooseTexture("../data/textures/skybox.png");
	background->getComponent<Transform>()->Translate(0.0f, 5.0f, -10.0f);
	background->getComponent<Transform>()->Rotate(110.0f, 0.0f, 0.0f);
	background->getComponent<Transform>()->Scale(5.0f, 5.0f, 5.0f);

	for (float i = 0.0f; i < 15.0f; i+= 2.0f)
	{
		shared<Entity> cube = core->addEntity();

		shared<MeshRenderer> cubeMr = cube->addComponent<MeshRenderer>();
		cubeMr->chooseCube();
		cubeMr->chooseTexture("../data/textures/box.jpg");

		cube->addComponent<BoxCollider>();
		cube->getComponent<Transform>()->Scale(-0.5f, -0.5f, -0.5f);
		cube->getComponent<Transform>()->Translate(0.0f, i, 0.0f);
	}

	for (float i = 0.0f; i < 15.0f; i += 2.0f)
	{
		shared<Entity> cube2 = core->addEntity();

		shared<MeshRenderer> cubeMr2 = cube2->addComponent<MeshRenderer>();
		cubeMr2->chooseCube();
		cubeMr2->chooseTexture("../data/textures/box.jpg");

		cube2->addComponent<BoxCollider>();
		cube2->getComponent<Transform>()->Scale(-0.5f, -0.5f, -0.5f);
		cube2->getComponent<Transform>()->Translate(-3.0f, i, 0.0f);
	}

	shared<Audio> au = std::make_shared<Audio>("../data/audio/dixie_horn.ogg");   // Add an audio clip

	au->play();   // Play the audio clip

	core->Start(mainCam);
}
