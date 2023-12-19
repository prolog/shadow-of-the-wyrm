#include <sstream>
#include "SDLSound.hpp"
#include "Log.hpp"
#include "SDLInit.hpp"

using namespace std;

SDLSound::SDLSound()
{
}

SDLSound::~SDLSound()
{
	tear_down();
}

void SDLSound::tear_down()
{
}

ClassIdentifier SDLSound::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_SDL_SOUND;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLSound_test.cpp"
#endif