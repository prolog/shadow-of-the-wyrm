#pragma once
#include "Sound.hpp"

class SDLSound : public Sound
{
	public:
		SDLSound();
		virtual ~SDLSound();

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};