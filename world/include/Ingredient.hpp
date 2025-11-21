#pragma once
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"

class Ingredient : public ISerializable
{
	public:
		Ingredient();
		Ingredient(const std::string& new_randomization_property, const std::string& new_id, const uint new_quantity);
		virtual ~Ingredient() = default;

		bool operator==(const Ingredient& rhs) const;
		
		void set_randomization_property(const std::string& new_randomization_property);
		std::string get_randomization_property() const;

		void set_id(const std::string& new_id);
		std::string get_id() const;

		void set_quantity(const uint new_quantity);
		uint get_quantity() const;

		bool serialize(std::ostream& stream) const override;
		bool deserialize(std::istream& stream) override;

	protected:
		std::string randomization_property;
		std::string id;
		uint quantity;

	private:
		ClassIdentifier internal_class_identifier() const;
};