#pragma once
#include "Sound.hpp"

class NullSound : public Sound
{
	public:
		NullSound();
		~NullSound();

		void play(const std::string& path) override;

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};