#include "Sound.hpp"
#include "Serialize.hpp"

using namespace std;

Sound::Sound()
: enable_sound(true), enable_sound_effects(true), enable_ambient_sound_effects(true), enable_music(true)
{
}

Sound::~Sound()
{
}

void Sound::set_enable_sound(const bool new_enable_sound)
{
	enable_sound = new_enable_sound;
	toggle_music(enable_sound);
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

void Sound::set_enable_ambient_sound_effects(const bool new_enable_ambient_sound_effects)
{
	enable_ambient_sound_effects = new_enable_ambient_sound_effects;
}

bool Sound::get_enable_ambient_sound_effects() const
{
	return enable_ambient_sound_effects;
}

void Sound::set_enable_music(const bool new_enable_music)
{
	enable_music = new_enable_music;
	toggle_music(enable_music);
}

bool Sound::get_enable_music() const
{
	return enable_music;
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
	Serialize::write_bool(stream, enable_ambient_sound_effects);
	Serialize::write_bool(stream, enable_music);

	return true;
}

bool Sound::deserialize(std::istream& stream)
{
	effect_regex.clear();
	Serialize::read_string_map(stream, effect_regex);
	Serialize::read_bool(stream, enable_sound);
	Serialize::read_bool(stream, enable_sound_effects);
	Serialize::read_bool(stream, enable_ambient_sound_effects);
	Serialize::read_bool(stream, enable_music);

	return true;
}
