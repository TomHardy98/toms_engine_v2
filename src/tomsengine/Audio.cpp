#include <AL/al.h>   // Allows for the use of audio functions
#include <iostream>   // Allows for the use of command console output
#include <vorbis/vorbisfile.h>
#include <vector>   // Allows for the use of vectors

#include "Audio.h"

namespace tomsengine
{
	struct AudioImpl
	{
		ALuint id;   // Create ALuint variable called id

		~AudioImpl()   // Destructor for AudioImpl
		{
			alDeleteBuffers(1, &id);   // Delete all audio buffers
		}

		void load_ogg(std::string fileName, std::vector<char> &buffer,
			ALenum &format, ALsizei &freq)   // Declaring load_ogg function
		{
			int endian = 0;
			int bitStream = 0;
			long bytes = 0;
			char array[2048] = { 0 };
			vorbis_info *pInfo = NULL;
			OggVorbis_File oggFile = { 0 };

			if (ov_fopen(fileName.c_str(), &oggFile) != 0)   /// Use the inbuilt fopen to create a file descriptor
			{
				std::cout << "Failed to open file '" << fileName << "' for decoding" << std::endl;
				throw std::exception();
			}

			pInfo = ov_info(&oggFile, -1);   /// Extract information from the file header

			if (pInfo->channels == 1)   /// Record the format required by OpenAL
			{
				format = AL_FORMAT_MONO16;
			}
			else
			{
				format = AL_FORMAT_STEREO16;
			}

			freq = pInfo->rate;   /// Record the sample rate required by OpenAL

			while (true)   /// Keep reading bytes from the file to populate the output buffer
			{
				bytes = ov_read(&oggFile, array, 2048, endian, 2, 1, &bitStream);   /// Read bytes into temporary array

				if (bytes < 0)   // If there are negative bytes output error
				{
					ov_clear(&oggFile);
					std::cout << "Failed to decode file '" << fileName << "'." << std::endl;
					throw std::exception();
				}
				else if (bytes == 0)   // If all bytes have been read, break
				{
					break;
				}

				buffer.insert(buffer.end(), array, array + bytes);   /// Copy from temporary array into output buffer
			}

			ov_clear(&oggFile);   // Clean up and close the file
		}
	};

	Audio::Audio() { }

	Audio::Audio(std::string path)   /// Audio constructor
	{
		load(path);   // Call load function
	}

	void Audio::load(std::string path)   // Audio load function
	{
		impl = std::make_shared<AudioImpl>();

		ALenum format = 0;
		ALsizei freq = 0;
		std::vector<char> bufferData;

		alGenBuffers(1, &impl->id);   // Set Buffers

		impl->load_ogg(path.c_str(), bufferData, format, freq);   // Call load_ogg function using variables

		alBufferData(impl->id, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);   /// Fill the buffers with data
	}

	void Audio::play()   // Audio play function
	{
		ALuint sid = 0;
		alGenSources(1, &sid);   /// Generate number of sources required
		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSourcei(sid, AL_BUFFER, impl->id);
		alSourcePlay(sid);
	}

	void Audio::play(float vol, float varMin, float varMax)   // Audio play function using passed variables
	{
		varMin *= 1000.0f;   ///For better rand resolution
		varMax *= 1000.0f;   ///For better rand resolution
		float variance = (std::rand() % ((int)varMin + 1 - (int)varMax) + (int)varMin) / 1000.0f;

		ALuint sid = 0;
		alGenSources(1, &sid);   /// Generate number of sources required
		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSourcei(sid, AL_BUFFER, impl->id);
		alSourcef(sid, AL_PITCH, variance);
		alSourcef(sid, AL_GAIN, vol);
		alSourcePlay(sid);
	}
}