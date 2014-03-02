#include "Consumable.hpp"
#include "Serialize.hpp"

using namespace std;

Consumable::Consumable()
: nutrition(0), standard_drinks(0.0f), food_type(FOOD_TYPE_OTHER)
{
}

Consumable::Consumable(const int nutr, const float std_drinks)
: nutrition(nutr), standard_drinks(std_drinks), food_type(FOOD_TYPE_OTHER)
{
}

bool Consumable::operator==(const Consumable& consumable) const
{
  bool result = true;

  result = result && Item::operator==(consumable);
  result = result && (nutrition == consumable.nutrition);
  result = result && (standard_drinks == consumable.standard_drinks);
  result = result && (food_type == consumable.food_type);

  return result;
}

void Consumable::set_food_type(const FoodType new_food_type)
{
  food_type = new_food_type;
}

FoodType Consumable::get_food_type() const
{
  return food_type;
}

void Consumable::set_nutrition(const int new_nutrition)
{
  nutrition = new_nutrition;
}

int Consumable::get_nutrition() const
{
  return nutrition;
}

void Consumable::set_standard_drinks(const float new_standard_drinks)
{
  standard_drinks = new_standard_drinks;
}

float Consumable::get_standard_drinks() const
{
  return standard_drinks;
}

// Food becomes more or less nutritious, based on whether the enchantment's BUC
// status.
void Consumable::do_enchant_item(const int points)
{
  nutrition *= points;
}

bool Consumable::serialize(ostream& stream) const
{
  Item::serialize(stream);
  Serialize::write_int(stream, nutrition);
  Serialize::write_float(stream, standard_drinks);
  Serialize::write_enum(stream, food_type);

  return true;
}

bool Consumable::deserialize(istream& stream)
{
  Item::deserialize(stream);
  Serialize::read_int(stream, nutrition);
  Serialize::read_float(stream, standard_drinks);
  Serialize::read_enum(stream, food_type);

  return true;
}
