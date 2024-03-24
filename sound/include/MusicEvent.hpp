#pragma once
#include <string>

class MusicEvent
{
	public:
		static const std::string MUSIC_EVENT_TITLE;

	protected:
		MusicEvent();
		~MusicEvent();
};

// For the Lua scripts
constexpr auto CMUSIC_EVENT_ARENA = "_arena";
constexpr auto CMUSIC_EVENT_ARENA_VICTORY = "_arena_victory";
constexpr auto CMUSIC_EVENT_OVERWORLD = "_overworld";
