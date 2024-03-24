#pragma once
#include "Sound.hpp"

class NullSound : public Sound
{
	public:
		NullSound();
		~NullSound();

		virtual void set_effects(const std::map<std::pair<std::string, std::string>, std::string>& new_effects) override;
		virtual void set_music(const Music& new_music) override;
		virtual Music get_music() const override;
		virtual void set_disabled_sound_ids(const std::string& new_disabled_ids_csv) override;

		virtual void toggle_music(const bool new_val) override;

		virtual void play(const std::string& id) override;
		
		virtual void play_music_for_event(const std::string& event, const bool = true) override;
		virtual void play_music(MapPtr map, const bool loop = true) override;
		virtual void play_music_location(const std::string& location, const bool loop = true) override;
		virtual void stop_music(const bool fade = false) override;
		virtual std::string get_playing_music_location() const override;

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};