#include "Recipe.hpp"
#include "Serialize.hpp"

using namespace std;

Recipe::Recipe()
: skill(SkillType::SKILL_UNDEFINED), skill_required(1)
{
}

Recipe::Recipe(const string& new_id, const Ingredients& new_ingredients, const SkillType new_skill, const uint new_skill_required, const string& new_item_id, const map<string, string>& new_properties)
: id(new_id), ingredients(new_ingredients), skill(new_skill), skill_required(new_skill_required), item_id(new_item_id), properties(new_properties)
{
}

bool Recipe::operator==(const Recipe& r) const
{
	bool result = true;

	result = result && (id == r.id);
	result = result && (ingredients == r.ingredients);
	result = result && (skill == r.skill);
	result = result && (skill_required == r.skill_required);
	result = result && (item_id == r.item_id);
	result = result && (properties == r.properties);

	return result;
}

string Recipe::get_id() const
{
	return id;
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

map<string, string> Recipe::get_properties() const
{
	return properties;
}

bool Recipe::serialize(std::ostream& stream) const
{
	Serialize::write_string(stream, id);
	Serialize::write_size_t(stream, ingredients.size());
	
	for (const auto& ingr : ingredients)
	{
		ingr.serialize(stream);
	}

	Serialize::write_enum(stream, skill);
	Serialize::write_uint(stream, skill_required);
	Serialize::write_string(stream, item_id);
	Serialize::write_string_map(stream, properties);

	return true;
}

bool Recipe::deserialize(std::istream& stream)
{
	Serialize::read_string(stream, id);

	size_t num_ingr = 0;
	Serialize::read_size_t(stream, num_ingr);
	ingredients.clear();

	for (size_t i = 0; i < num_ingr; i++)
	{
		Ingredient ingr;

		ingr.deserialize(stream);
		ingredients.push_back(ingr);
	}

	Serialize::read_enum(stream, skill);
	Serialize::read_uint(stream, skill_required);
	Serialize::read_string(stream, item_id);
	Serialize::read_string_map(stream, properties);

	return true;
}

ClassIdentifier Recipe::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_RECIPE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Recipe_test.cpp"
#endif
