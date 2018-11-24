#include "GameLoop.h"
#include <iostream>
#include <ctime>

#define shared std::shared_ptr   // Define what a shared pointer is, just use the word 'shared'
#define weak std::weak_ptr   // Define what a weak pointer is, just use the word 'weak'

using namespace tomsengine;

void GameLoop::Start()
{
	float randNum = 0.0f;
	float randScale = 0.0f;
	int randMax = 5;
	int randScaleMax = 4;

	srand(time(NULL));

	// Creating core
	shared<Core> core = std::make_shared<Core>();   // Initialize the engine (SDL) and name it 'core'
	std::shared_ptr<Core> ptr = core->getPtrToThis();   // Setting cores 'self'
	core->self = ptr;   // Setting cores 'self'

	// Creating main camera
	shared<Entity> mainCam = core->addEntity();
	mainCam->addComponent<Camera>();
	mainCam->getComponent<Transform>()->Translate(0.0f, -6.5f, 12.0f);

	shared<Entity> background = core->addEntity();
	shared<MeshRenderer> backgroundMr = background->addComponent<MeshRenderer>();
	backgroundMr->chooseCube();
	backgroundMr->chooseTexture("../data/textures/space.jpg");
	background->getComponent<Transform>()->Translate(0.0f, 5.0f, -10.0f);
	background->getComponent<Transform>()->Rotate(110.0f, 0.0f, 0.0f);
	background->getComponent<Transform>()->Scale(20.0f, 20.0f, 0.0f);

	// Creating player
	shared<Entity> player = core->addEntity();

	shared<MeshRenderer> playerMr = player->addComponent<MeshRenderer>();
	playerMr->chooseCustomMesh("../data/meshes/ufo.obj");
	playerMr->chooseTexture("../data/textures/ufo.png");

	player->addComponent<Player>();
	player->addComponent<BoxCollider>();
	player->getComponent<Transform>()->Translate(0.0f, -6.5f, 0.0f);
	player->getComponent<Transform>()->Rotate(0.0f, 55.0f, 0.0f);


	// Creating enemies on right side
	for (float i = -4.0f; i < 17.0f; i+= 2.0f)
	{
		randNum = (rand() % randMax + 1);
		randNum = randNum / 100;

		randScale = (rand() % randScaleMax + 3);
		randScale = randScale / 10;

		shared<Entity> cube = core->addEntity();

		shared<MeshRenderer> cubeMr = cube->addComponent<MeshRenderer>();
		cubeMr->chooseCustomMesh("../data/meshes/meteor.obj");
		cubeMr->chooseTexture("../data/textures/asteroid.jpg");

		cube->addComponent<Enemy>();
		cube->addComponent<BoxCollider>();
		cube->getComponent<Transform>()->setVelocity(randNum);
		cube->getComponent<Transform>()->Scale(-randScale, -randScale, -randScale);
		cube->getComponent<Transform>()->Translate(0.0f, i, 0.0f);
	}

	// Creating enemies on left side
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

	shared<Audio> au = std::make_shared<Audio>("../data/audio/dixie_horn.ogg");   // Add an audio clip

	au->play();   // Play the audio clip

	core->Start(mainCam);
}
