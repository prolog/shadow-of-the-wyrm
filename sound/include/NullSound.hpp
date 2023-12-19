#pragma once
#include "Sound.hpp"

class NullSound : public Sound
{
	public:
		NullSound();
		~NullSound();

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};