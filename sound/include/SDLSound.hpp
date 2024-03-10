#pragma once
#ifdef ENABLE_SDL
#include <map>
#include <set>
#include "SDLInit.hpp"
#include "Sound.hpp"

class SDLSound : public Sound
{
	public:
		SDLSound();
		virtual ~SDLSound();

		virtual void set_effects(const std::map<std::pair<std::string, std::string>, std::string>& new_effects) override;
		virtual void set_music(const Music& new_music);
		virtual void set_disabled_sound_ids(const std::string& new_disabled_ids_csv) override;

		virtual void toggle_music(const bool new_val) override;

		virtual void play(const std::string& path) override;

		virtual void play_music(MapPtr map) override;
		virtual void stop_music() override;

	protected:
		virtual void tear_down();
		virtual void clear_effects();

		std::map<std::string, Mix_Chunk*> effects;
		Music music;
		std::set<std::string> disabled_sound_ids;
		Mix_Music* cur_music;

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};

#endif