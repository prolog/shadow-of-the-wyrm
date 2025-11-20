#pragma once
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

class Ingredient : public ISerializable
{
	public:
		Ingredient();
		Ingredient(const std::string& new_id, const uint new_quantity);
		virtual ~Ingredient() = default;

		bool operator==(const Ingredient& rhs) const;
		
		std::string get_id() const;
		uint get_quantity() const;

		bool serialize(std::ostream& stream) const override;
		bool deserialize(std::istream& stream) override;

	protected:
		std::string id;
		uint quantity;

	private:
		ClassIdentifier internal_class_identifier() const;
};