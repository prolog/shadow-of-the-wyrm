#include "Recipe.hpp"
#include "Serialize.hpp"

using namespace std;

Recipe::Recipe()
{
}

Recipe::Recipe(const Ingredients& new_ingredients, const SkillType new_skill, const uint new_skill_required, const string& new_item_id)
: ingredients(new_ingredients), skill(new_skill), skill_required(new_skill_required), item_id(new_item_id)
{
}

bool Recipe::operator==(const Recipe& r) const
{
	bool result = true;

	result = result && (ingredients == r.ingredients);
	result = result && (skill == r.skill);
	result = result && (skill_required == r.skill_required);
	result = result && (item_id == r.item_id);

	return result;
}

Ingredients Recipe::get_ingredients() const
{
	return ingredients;
}

SkillType Recipe::get_skill() const
{
	return skill;
}

uint Recipe::get_skill_required() const
{
	return skill_required;
}

string Recipe::get_item_id() const
{
	return item_id;
}

bool Recipe::serialize(std::ostream& stream) const
{
	Serialize::write_size_t(stream, ingredients.size());
	
	for (const auto& i_pair : ingredients)
	{
		Serialize::write_string(stream, i_pair.first);
		Serialize::write_uint(stream, i_pair.second);
	}

	Serialize::write_enum(stream, skill);
	Serialize::write_uint(stream, skill_required);
	Serialize::write_string(stream, item_id);

	return true;
}

bool Recipe::deserialize(std::istream& stream)
{
	size_t num_ingr = 0;
	Serialize::read_size_t(stream, num_ingr);
	ingredients.clear();

	for (size_t i = 0; i < num_ingr; i++)
	{
		string ingr_id;
		uint quantity = 0;

		Serialize::read_string(stream, ingr_id);
		Serialize::read_uint(stream, quantity);

		ingredients.push_back({ ingr_id, quantity });
	}

	Serialize::read_enum(stream, skill);
	Serialize::read_uint(stream, skill_required);
	Serialize::read_string(stream, item_id);

	return true;
}

ClassIdentifier Recipe::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_RECIPE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Recipe_test.cpp"
#endif
