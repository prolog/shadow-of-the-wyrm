#pragma once
#include <memory>
#include "ISerializable.hpp"

class Sound : public ISerializable
{
	public:
		virtual ~Sound();

		virtual bool serialize(std::ostream& stream) const override;
		virtual bool deserialize(std::istream& stream) override;

	private:
		virtual ClassIdentifier internal_class_identifier() const override = 0;
};

using SoundPtr = std::shared_ptr<Sound>;
