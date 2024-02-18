#ifdef ENABLE_SDL
#include <sstream>
#include "SDLSound.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Setting.hpp"

using namespace std;

SDLSound::SDLSound()
{
}

SDLSound::~SDLSound()
{
	tear_down();
}

void SDLSound::set_effects(const map<pair<string, string>, string>& new_effects)
{
	clear_effects();

	for (const auto& e_pair : new_effects)
	{
		string id = e_pair.first.first;
		string match = e_pair.first.second;

		if (!id.empty())
		{
			Mix_Chunk* effect = Mix_LoadWAV(e_pair.second.c_str());

			if (effect != NULL)
			{
				effects[id] = effect;

				if (!match.empty())
				{
					effect_regex[id] = match;
				}
			}
			else
			{
				ostringstream ss;
				ss << "Cannot load sound effect: " << Mix_GetError();
				string error = ss.str();
				Log::instance().error(error);
			}
		}
		else
		{
			ostringstream ss;
			ss << "Sound effect specified but no id or match parameter.";
			string error = ss.str();
			Log::instance().error(error);
		}
	}
}

void SDLSound::set_disabled_sound_ids(const string& new_disabled_sound_csv)
{
	disabled_sound_ids.clear();
	vector<string> disabled_ids = String::create_string_vector_from_csv_string(new_disabled_sound_csv);

	for (const auto& d_id : disabled_ids)
	{
		disabled_sound_ids.insert(d_id);
	}
}

void SDLSound::play(const string& id)
{
	if (enable_sound && enable_sound_effects && !id.empty())
	{
		auto e_it = effects.find(id);

		if (disabled_sound_ids.find(id) == disabled_sound_ids.end())
		{
			if (e_it != effects.end())
			{
				Mix_Chunk* effect = e_it->second;
				Mix_PlayChannel(-1, effect, 0);
			}
		}
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

#endif