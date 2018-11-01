#include <memory>   // Allows for the use of pointers
#include <string>   // Allows for the use of strings

namespace tomsengine
{
	struct AudioImpl;

	class Audio
	{
		std::shared_ptr<AudioImpl> impl;

	public:

		Audio();   // Defining the audio constructor
		Audio(std::string path);   // Defining the audio constructor with a string variable
		void load(std::string path);   // Defining the load function with a string variable
		void play(float volume, float varMin, float varMax);   // Defining the play function with three variables
		void play();   // Defining the play function
	};
}