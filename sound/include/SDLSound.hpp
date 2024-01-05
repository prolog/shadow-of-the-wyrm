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
		virtual void set_disabled_sound_ids(const std::string& new_disabled_ids_csv) override;

		virtual void play(const std::string& path) override;

	protected:
		virtual void tear_down();
		virtual void clear_effects();

		std::map<std::string, Mix_Chunk*> effects;
		std::set<std::string> disabled_sound_ids;

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};

#endif