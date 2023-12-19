#include "SDLSound.hpp"

SDLSound::SDLSound()
{
}

SDLSound::~SDLSound()
{
}

ClassIdentifier SDLSound::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_SDL_SOUND;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLSound_test.cpp"
#endif