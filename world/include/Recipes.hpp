#pragma once
#include <map>
#include <vector>
#include "Creature.hpp"
#include "ISerializable.hpp"
#include "Recipe.hpp"

using RecipesType = std::map<SkillType, std::map<int, std::map<std::string, Recipe>>>;

class Recipes : public ISerializable
{
	public:
		Recipes();
		Recipes(const RecipesType& new_rt);
		virtual ~Recipes();

		bool operator==(const Recipes& r2) const;

		void add(const Recipe& r);
		std::vector<Recipe> get_recipes(CreaturePtr creature = nullptr) const;
		RecipesType& get_recipes_ref();

		bool serialize(std::ostream& stream) const override;
		bool deserialize(std::istream& stream) override;

	protected:
		RecipesType recipes;

private:
			ClassIdentifier internal_class_identifier() const override;
};