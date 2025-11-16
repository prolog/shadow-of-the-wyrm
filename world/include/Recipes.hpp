#pragma once
#include <map>
#include <vector>
#include "ISerializable.hpp"
#include "Recipe.hpp"

using RecipeType = std::map<SkillType, std::map<int, std::map<std::string, Recipe>>>;

class Recipes : public ISerializable
{
	public:
		Recipes();
		Recipes(const RecipeType& new_rt);
		virtual ~Recipes();

		bool operator==(const Recipes& r2) const;

		void add(const Recipe& r);

		bool serialize(std::ostream& stream) const override;
		bool deserialize(std::istream& stream) override;

	protected:
		RecipeType recipes;

private:
			ClassIdentifier internal_class_identifier() const override;
};