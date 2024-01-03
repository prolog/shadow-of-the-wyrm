#pragma once
#include <map>
#include <memory>
#include <string>
#include "Creature.hpp"
#include "SoundEffectID.hpp"

class Sound : public ISerializable
{
	public:
		virtual ~Sound();

		virtual void set_effects(const std::map<std::string, std::string>& new_effects) = 0;
		virtual void play(const std::string& id) = 0;

		virtual bool serialize(std::ostream& stream) const override;
		virtual bool deserialize(std::istream& stream) override;

	private:
		virtual ClassIdentifier internal_class_identifier() const override = 0;
};

using SoundPtr = std::shared_ptr<Sound>;
