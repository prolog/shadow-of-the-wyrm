#pragma once
#include <Map.hpp>

class AmbientSoundProbability
{
	public:
		AmbientSoundProbability(const int new_turn_mod_trigger, const std::pair<int, int>& new_x_in_y);

		int get_turn_mod_trigger() const;
		std::pair<int, int> get_x_in_y() const;

	protected:
		int turn_mod_trigger;
		std::pair<int, int> x_in_y;
};

class AmbientSound
{
	public:
		AmbientSound();
		virtual ~AmbientSound() = default;

		std::string get_sound_effect(MapPtr map, const ulonglong turn_number, const bool override_probability = false) const;

	protected:
		std::string ambient_underground_handler(MapPtr map, const ulonglong turn_number, const bool override_probability) const;
		bool should_trigger(MapPtr map, const ulonglong turn_number, const AmbientSoundProbability& asp, const bool override_probability) const;

		std::map<MapType, AmbientSoundProbability> ambient_sound_probabilities;
		std::map<MapType, std::vector<std::string>> ambient_sound_effects;
};
