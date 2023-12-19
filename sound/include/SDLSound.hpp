#pragma once
#include "Sound.hpp"

class SDLSound : public Sound
{
	public:
		SDLSound();
		virtual ~SDLSound();

	protected:
		virtual void tear_down();

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};