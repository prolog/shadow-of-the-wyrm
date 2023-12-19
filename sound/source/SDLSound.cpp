#include <sstream>
#include "SDLSound.hpp"
#include "Log.hpp"
#include "SDLInit.hpp"

using namespace std;

SDLSound::SDLSound()
{
	gScratch = NULL;
	gScratch = Mix_LoadWAV("assets/sound/effects/hit.wav");

	if (gScratch == NULL)
	{
		ostringstream ss;
		ss << "Failed to load scratch sound effect! " << Mix_GetError();
		string foo = ss.str();
		int x = 1;
	}
}

SDLSound::~SDLSound()
{
	tear_down();
}

void SDLSound::play(const string& path)
{
	Mix_PlayChannel(-1, gScratch, 0);
}

void SDLSound::tear_down()
{
	Mix_FreeChunk(gScratch);
	gScratch = NULL;
}

ClassIdentifier SDLSound::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_SDL_SOUND;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLSound_test.cpp"
#endif