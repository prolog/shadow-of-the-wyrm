#pragma once
#include "Sound.hpp"

class SDLSound : public Sound
{
	public:
		SDLSound();
		virtual ~SDLSound();

		void play(const std::string& path) override;

	protected:
		virtual void tear_down();

		Mix_Chunk* gScratch;

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};