#include "Sound.hpp"
#include "Serialize.hpp"

using namespace std;

Sound::Sound()
: enable_sound(true), enable_sound_effects(true)
{
}

Sound::~Sound()
{
}

void Sound::set_enable_sound(const bool new_enable_sound)
{
	enable_sound = new_enable_sound;
}

bool Sound::get_enable_sound() const
{
	return enable_sound;
}

void Sound::set_enable_sound_effects(const bool new_enable_sound_effects)
{
	enable_sound_effects = new_enable_sound_effects;
}

bool Sound::get_enable_sound_effects() const
{
	return enable_sound_effects;
}

const map<string, string>& Sound::get_effect_regex_cref() const
{
	return effect_regex;
}

bool Sound::serialize(std::ostream& stream) const
{
	Serialize::write_string_map(stream, effect_regex);
	Serialize::write_bool(stream, enable_sound);
	Serialize::write_bool(stream, enable_sound_effects);

	return true;
}

bool Sound::deserialize(std::istream& stream)
{
	effect_regex.clear();
	Serialize::read_string_map(stream, effect_regex);
	Serialize::read_bool(stream, enable_sound);
	Serialize::read_bool(stream, enable_sound_effects);

	return true;
}
