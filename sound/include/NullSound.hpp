#pragma once
#include "Sound.hpp"

class NullSound : public Sound
{
	public:
		NullSound();
		~NullSound();

		virtual void set_effects(const std::map<std::pair<std::string, std::string>, std::string>& new_effects) override;
		virtual void set_music(const Music& new_music);
		virtual void set_disabled_sound_ids(const std::string& new_disabled_ids_csv) override;

		virtual void play(const std::string& id) override;
		
		virtual void play_music(MapPtr map) override;
		virtual void stop_music() override;

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};