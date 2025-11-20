#pragma once
#include "common.hpp"
#include <string>
#include <vector>
#include "ISerializable.hpp"
#include "Ingredient.hpp"
#include "Skills.hpp"

using Ingredients = std::vector<Ingredient>;

class Recipe : public ISerializable
{
	public:
		Recipe();
		Recipe(const std::string& new_id, const Ingredients& new_ingredients, const SkillType new_skill, const uint new_skill_required, const std::string& new_item_id, const std::map<std::string, std::string>& new_properties);

		bool operator==(const Recipe& r) const;

		std::string get_id() const;
		Ingredients get_ingredients() const;
		SkillType get_skill() const;
		uint get_skill_required() const;
		std::string get_item_id() const;
		std::map<std::string, std::string> get_properties() const;

		bool serialize(std::ostream& stream) const override;
		bool deserialize(std::istream& stream) override;

	protected:
		std::string id;
		Ingredients ingredients;
		SkillType skill;
		uint skill_required;
		std::string item_id;
		std::map<std::string, std::string> properties;

	private:
		ClassIdentifier internal_class_identifier() const override;
};
