#include <memory>   // Allows for the use of pointers (shared, weak, etc)
#include <exception>   // Allows for the use of exceptions to be thrown
#include <iostream>   // Allows for the use of text output to the console
#include <tomsengine/tomsengine.h>   /// Allows for a cleaner include directory as all local includes are provided in here

#include "GameLoop.h"

#define shared std::shared_ptr   /// Define what a shared pointer is, just use the word 'shared'
#define weak std::weak_ptr   /// Define what a weak pointer is, just use the word 'weak'

using namespace tomsengine;   // Allows for the use of tomsengine classes

void safe_main()
{
	shared<GameLoop> gameLoop = std::make_shared<GameLoop>();   // Creating a gameLoop object to call start through

	gameLoop->Start();   /// Starting the game loop
}

int main()
{
	try
	{
		safe_main();   /// Try calling safe main to avoid program crashing on start
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;   /// Return exception if error occurs
	}

	return 0;
}