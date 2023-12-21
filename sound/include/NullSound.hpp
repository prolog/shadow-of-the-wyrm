#pragma once
#include "Sound.hpp"

class NullSound : public Sound
{
	public:
		NullSound();
		~NullSound();

		virtual void set_effects(const std::map<std::string, std::string>& new_effects) override;
		virtual void play(const std::string& id) override;

	private:
		virtual ClassIdentifier internal_class_identifier() const override;
};