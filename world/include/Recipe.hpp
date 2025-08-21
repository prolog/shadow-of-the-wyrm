#pragma once
#include "common.hpp"
#include <string>
#include <utility>
#include <vector>
#include "ISerializable.hpp"

using Ingredients = std::vector<std::pair<std::string, uint>>;

class Recipe : public ISerializable
{
	public:
		Recipe();
		Recipe(const Ingredients& new_ingredients, const uint new_skill_required, const std::string& new_item_id);
		bool operator==(const Recipe& r) const;

		Ingredients get_ingredients() const;
		uint get_skill_required() const;
		std::string get_item_id() const;

		bool serialize(std::ostream& stream) const override;
		bool deserialize(std::istream& stream) override;

	protected:
		Ingredients ingredients;
		uint skill_required;
		std::string item_id;

	private:
		ClassIdentifier internal_class_identifier() const override;
};
