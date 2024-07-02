#pragma once
#include <string>

class MusicEvent
{
	public:
		static const std::string MUSIC_EVENT_TITLE;
		static const std::string MUSIC_EVENT_CROWNING_GOOD;
		static const std::string MUSIC_EVENT_CROWNING_NEUTRAL;
		static const std::string MUSIC_EVENT_CROWNING_EVIL;
		static const std::string MUSIC_EVENT_RESPAWN;

	protected:
		MusicEvent();
		~MusicEvent();
};

// For the Lua scripts
constexpr auto CMUSIC_EVENT_ARENA = "_arena";
constexpr auto CMUSIC_EVENT_ARENA_VICTORY = "_arena_victory";
constexpr auto CMUSIC_EVENT_OVERWORLD = "_overworld";
constexpr auto CMUSIC_EVENT_PLANETARY_TELEPORT = "_planetary_teleport";
constexpr auto CMUSIC_EVENT_RESPAWN = "_respawn";