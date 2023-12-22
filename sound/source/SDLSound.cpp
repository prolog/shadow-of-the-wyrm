#include <sstream>
#include "SDLSound.hpp"
#include "Log.hpp"

using namespace std;

SDLSound::SDLSound()
{
}

SDLSound::~SDLSound()
{
	tear_down();
}

void SDLSound::set_effects(const map<string, string>& new_effects)
{
	clear_effects();

	for (const auto& e_pair : new_effects)
	{
		Mix_Chunk* effect = Mix_LoadWAV(e_pair.second.c_str());
		
		if (effect != NULL)
		{
			effects[e_pair.first] = effect;
		}
		else
		{
			ostringstream ss;
			ss << "Cannot load sound effect: " << Mix_GetError();
			string error = ss.str();
			Log::instance().error(error);
		}
	}
}

void SDLSound::play(const string& id)
{
	auto e_it = effects.find(id);

	if (e_it != effects.end())
	{
		Mix_Chunk* effect = e_it->second;
		Mix_PlayChannel(-1, effect, 0);
	}
}

void SDLSound::tear_down()
{
	clear_effects();
}

void SDLSound::clear_effects()
{
	for (const auto& e_pair : effects)
	{
		Mix_Chunk* effect = e_pair.second;

		if (effect != NULL)
		{
			Mix_FreeChunk(effect);
			effect = NULL;
		}
	}

	effects.clear();
}

ClassIdentifier SDLSound::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_SDL_SOUND;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLSound_test.cpp"
#endif