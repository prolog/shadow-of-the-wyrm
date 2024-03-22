#ifdef ENABLE_SDL
#include <sstream>
#include "SDLSound.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "MapProperties.hpp"
#include "Setting.hpp"

using namespace std;

const int SDLSound::FADE_MS = 750;

SDLSound::SDLSound()
{
	cur_music = NULL;
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

void SDLSound::set_music(const Music& new_music)
{
	music = new_music;
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

void SDLSound::toggle_music(const bool new_val)
{
	if (new_val)
	{
		MapPtr map = Game::instance().get_current_map();
		play_music(map);
	}
	else
	{
		stop_music();
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

// Play music for the map.
//
// Order checked:
// - the MAP_PROPERTIES_SONG_LOCATION map property
// - the ID specified in the game configuration
// - the map type specified in the game configuration
void SDLSound::play_music(MapPtr map)
{
	if (enable_sound && enable_music)
	{
		if (map != nullptr)
		{
			string id = map->get_map_id();
			TileType tt = map->get_terrain_type();
			MapType mt = map->get_map_type();
			string location = map->get_property(MapProperties::MAP_PROPERTIES_SONG_LOCATION);

			if (location.empty())
			{
				location = music.get_song(id);
			}

			if (location.empty())
			{
				location = music.get_song(tt);
			}

			if (location.empty())
			{
				location = music.get_song(mt);
			}

			if (cur_music != NULL)
			{
				Mix_FadeOutMusic(FADE_MS);
				Mix_FreeMusic(cur_music);
				cur_music = NULL;
			}

			if (!location.empty())
			{
				cur_music = Mix_LoadMUS(location.c_str());

				if (cur_music != NULL)
				{
					Mix_PlayMusic(cur_music, -1);
				}
				else
				{
					string err = Mix_GetError();
					Log::instance().error("Could not play music: " + err);
				}
			}
		}
	}
}

void SDLSound::stop_music(const bool fade)
{
	if (cur_music != NULL)
	{
		if (fade)
		{
			Mix_FadeOutMusic(FADE_MS);
		}
		else
		{
			Mix_HaltMusic();
		}

		Mix_FreeMusic(cur_music);
		cur_music = NULL;
	}
}

void SDLSound::tear_down()
{
	if (cur_music != NULL)
	{
		Mix_FreeMusic(cur_music);
	}

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