#include "Sound.hpp"

Sound::~Sound()
{
}

bool Sound::serialize(std::ostream& stream) const
{
	return true;
}

bool Sound::deserialize(std::istream& stream)
{
	return true;
}
