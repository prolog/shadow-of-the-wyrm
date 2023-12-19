#pragma once
#include <string>
#include "Sound.hpp"

class SoundID
{
	public:
		static const std::string SOUND_SDL;

	private:
		SoundID();
		~SoundID();
};

class SoundFactory
{
	public:
		SoundPtr create_sound(const std::string& sound_id);
		SoundPtr create_sound(const ClassIdentifier sound_ci);
};