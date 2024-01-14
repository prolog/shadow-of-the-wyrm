#include <cassert>
#include "SoundFactory.hpp"
#include "NullSound.hpp"
#include "SDLSound.hpp"

using namespace std;

const string SoundID::SOUND_SDL = "sdl";

SoundID::SoundID()
{
}

SoundID::~SoundID()
{
}

SoundPtr SoundFactory::create_null_sound()
{
	SoundPtr null_sound = create_sound("");
	return null_sound;
}

SoundPtr SoundFactory::create_sound(const string& sound_id)
{
	SoundPtr sound = std::make_shared<NullSound>();

	#ifdef ENABLE_SDL
	if (sound_id == SoundID::SOUND_SDL)
	{
		sound = std::make_shared<SDLSound>();
	}
	#endif

	return sound;
}

SoundPtr SoundFactory::create_sound(ClassIdentifier sound_ci)
{
	SoundPtr sound;

	if (sound_ci == ClassIdentifier::CLASS_ID_NULL_SOUND)
	{
		sound = std::make_shared<NullSound>();
	}
	#ifdef ENABLE_SDL
	else if (sound_ci == ClassIdentifier::CLASS_ID_SDL_SOUND)
	{
		sound = std::make_shared<SDLSound>();
	}
  #endif
	else
	{
		assert(false && "Unexpected class_id for SoundFactory::create_sound");
	}

	return sound;
}