#include "Ingredient.hpp"
#include "Serialize.hpp"

using namespace std;

Ingredient::Ingredient()
: quantity(0)
{
}

Ingredient::Ingredient(const string& new_randomization_property, const std::string& new_id, const uint new_quantity)
: randomization_property(new_randomization_property), id(new_id), quantity(new_quantity)
{
}

bool Ingredient::operator==(const Ingredient& rhs) const
{
	bool result = true;

	result = result && (id == rhs.id);
	result = result && (quantity == rhs.quantity);

	return result;
}

void Ingredient::set_randomization_property(const string& new_randomization_property)
{
	randomization_property = new_randomization_property;
}

string Ingredient::get_randomization_property() const
{
	return randomization_property;
}

void Ingredient::set_id(const string& new_id)
{
	id = new_id;
}

string Ingredient::get_id() const
{
	return id;
}

void Ingredient::set_quantity(const uint new_quantity)
{
	quantity = new_quantity;
}

uint Ingredient::get_quantity() const
{
	return quantity;
}

bool Ingredient::serialize(std::ostream& stream) const
{
	Serialize::write_string(stream, randomization_property);
	Serialize::write_string(stream, id);
	Serialize::write_uint(stream, quantity);

	return true;
}

bool Ingredient::deserialize(std::istream& stream)
{
	Serialize::read_string(stream, randomization_property);
	Serialize::read_string(stream, id);
	Serialize::read_uint(stream, quantity);

	return true;
}

ClassIdentifier Ingredient::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_INGREDIENT;
}

#ifdef UNIT_TESTS
#include "unit_tests/Ingredient_test.cpp"
#endif

