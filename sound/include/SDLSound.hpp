#pragma once
#include <map>
#include "SDLInit.hpp"
#include "Sound.hpp"

class SDLSound : public Sound
{
	public:
		SDLSound();
		virtual ~SDLSound();

		virtual void set_effects(const std::map<std::string, std::string>& new_effects) override;
		virtual void play(const std::string& path) override;

	protected:
		virtual void tear_down();
		virtual void clear_effects();

		std::map<std::string, Mix_Chunk*> effects;

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};