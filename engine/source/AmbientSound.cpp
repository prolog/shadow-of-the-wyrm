#include "AmbientSound.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "MapProperties.hpp"
#include "RNG.hpp"
#include "Setting.hpp"
#include "SoundEffectID.hpp"

using namespace std;

// Ambient Sound Probability
AmbientSoundProbability::AmbientSoundProbability(const int new_turn_mod_trigger, const pair<int, int>& new_x_in_y)
: turn_mod_trigger(new_turn_mod_trigger), x_in_y(new_x_in_y)
{
}

int AmbientSoundProbability::get_turn_mod_trigger() const
{
	return turn_mod_trigger;
}

pair<int, int> AmbientSoundProbability::get_x_in_y() const
{
	return x_in_y;
}

// Ambient Sound
AmbientSound::AmbientSound()
: ambient_sound_probabilities({ {MapType::MAP_TYPE_UNDERWORLD, {10, {1, 10}}} })
, ambient_sound_effects({ {MapType::MAP_TYPE_UNDERWORLD, {SoundEffectID::DRIP3} } })
{
}

string AmbientSound::get_sound_effect(MapPtr map, const ulonglong turn_number, const bool override_probability) const
{
	string effect_id;
	SoundPtr sound = Game::instance().get_sound();
	bool ambient_enabled = sound ? sound->get_enable_ambient_sound_effects() : true;

	if (ambient_enabled && map != nullptr)
	{
		MapType mt = map->get_map_type();

		if (mt == MapType::MAP_TYPE_UNDERWORLD)
		{
			effect_id = ambient_underground_handler(map, turn_number, override_probability);
		}
	}

	return effect_id;
}

string AmbientSound::ambient_underground_handler(MapPtr map, const ulonglong turn_number, const bool override_probability) const
{
	string sound_effect_id;
	MapType mt = map->get_map_type();
	auto a_it = ambient_sound_probabilities.find(mt);

	if (a_it != ambient_sound_probabilities.end())
	{
		bool wet = String::to_bool(map->get_property(MapProperties::MAP_PROPERTIES_WET));

		if (wet && should_trigger(map, turn_number, a_it->second, override_probability))
		{ 
			auto ase_it = ambient_sound_effects.find(mt);

			if (ase_it != ambient_sound_effects.end())
			{
				vector<string> effect_ids = ase_it->second;

				if (!effect_ids.empty())
				{
					sound_effect_id = effect_ids.at(RNG::range(0, effect_ids.size() - 1));
				}
			}
		}
	}

	return sound_effect_id;
}

bool AmbientSound::should_trigger(MapPtr /*map*/, const ulonglong turn_number, const AmbientSoundProbability& asp, const bool override_probability) const
{
	bool trigger = false;
	auto xy = asp.get_x_in_y();

	if (turn_number % asp.get_turn_mod_trigger() == 0 && 
		 (override_probability || RNG::x_in_y_chance(xy.first, xy.second)))
	{
		trigger = true;
	}

	return trigger;
}

#ifdef UNIT_TESTS
#include "unit_tests/AmbientSound_test.cpp"
#endif