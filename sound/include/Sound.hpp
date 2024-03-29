#pragma once
#include <map>
#include <memory>
#include <string>
#include "Creature.hpp"
#include "SoundEffectID.hpp"

class Sound : public ISerializable
{
	public:
		Sound();
		virtual ~Sound();

		virtual void set_enable_sound(const bool new_enable_sound);
		virtual bool get_enable_sound() const;

		virtual void set_enable_sound_effects(const bool new_enable_sound_effects);
		virtual bool get_enable_sound_effects() const;

		virtual void set_effects(const std::map<std::pair<std::string, std::string>, std::string>& new_effects) = 0;
		virtual void set_disabled_sound_ids(const std::string& new_disabled_ids_csv) = 0;
		virtual const std::map<std::string, std::string>& get_effect_regex_cref() const;

		virtual void play(const std::string& id) = 0;

		virtual bool serialize(std::ostream& stream) const override;
		virtual bool deserialize(std::istream& stream) override;

	protected:
		std::map<std::string, std::string> effect_regex;
		bool enable_sound;
		bool enable_sound_effects;

	private:
		virtual ClassIdentifier internal_class_identifier() const override = 0;
};

using SoundPtr = std::shared_ptr<Sound>;
