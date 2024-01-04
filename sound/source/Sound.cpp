#include "Sound.hpp"
#include "Serialize.hpp"

using namespace std;

Sound::~Sound()
{
}

const map<string, string>& Sound::get_effect_regex_cref() const
{
	return effect_regex;
}

bool Sound::serialize(std::ostream& stream) const
{
	Serialize::write_string_map(stream, effect_regex);

	return true;
}

bool Sound::deserialize(std::istream& stream)
{
	effect_regex.clear();
	Serialize::read_string_map(stream, effect_regex);

	return true;
}
