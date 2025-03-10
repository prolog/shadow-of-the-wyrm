#include "global_prototypes.hpp"
#include "Consumable.hpp"
#include "ConsumableConstants.hpp"
#include "Conversion.hpp"
#include "ItemProperties.hpp"
#include "Serialize.hpp"

using namespace std;

Consumable::Consumable()
: nutrition(0), standard_drinks(0.0f), food_type(FoodType::FOOD_TYPE_OTHER), poisoned(false)
{
}

Consumable::Consumable(const int nutr, const float std_drinks)
: nutrition(nutr), standard_drinks(std_drinks), food_type(FoodType::FOOD_TYPE_OTHER), poisoned(false)
{
}

bool Consumable::operator==(const Consumable& consumable) const
{
  bool result = true;

  result = result && Item::operator==(consumable);
  result = result && consumable_properties_match(consumable);

  return result;
}

bool Consumable::is_corpse() const
{
  bool corpse = false;

  auto c_it_desc = additional_properties.find(ConsumableConstants::CORPSE_DESCRIPTION_SID);
  auto c_it_rid = additional_properties.find(ConsumableConstants::CORPSE_RACE_ID);
  auto c_it_short = additional_properties.find(ConsumableConstants::CORPSE_SHORT_DESCRIPTION_SID);

  if (c_it_desc != additional_properties.end() || c_it_rid != additional_properties.end() || c_it_short != additional_properties.end())
  {
    corpse = true;
  }

  return corpse;
}

void Consumable::set_metabolizes_alcohol(const bool new_metabolizes_alcohol)
{
  set_additional_property(ItemProperties::ITEM_PROPERTIES_METABOLIZES_ALCOHOL, std::to_string(new_metabolizes_alcohol));
}

bool Consumable::get_metabolizes_alcohol() const
{
  bool metabolizes = false;

  string prop = get_additional_property(ItemProperties::ITEM_PROPERTIES_METABOLIZES_ALCOHOL);
  if (!prop.empty())
  {
    metabolizes = String::to_bool(prop);
  }

  return metabolizes;
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

void Consumable::set_poisoned(const bool new_poisoned)
{
  poisoned = new_poisoned;
}

bool Consumable::get_poisoned() const
{
  return poisoned;
}

bool Consumable::additional_item_attributes_match(ItemPtr item) const
{
  bool match = false;
  ConsumablePtr consumable = dynamic_pointer_cast<Consumable>(item);

  if (consumable != nullptr)
  {
    match = consumable_properties_match(*consumable);
  }

  return match;
}

bool Consumable::consumable_properties_match(const Consumable& cons) const
{
  bool result = true;
  
  result = (nutrition == cons.nutrition);
  result = result && fequal(standard_drinks, cons.standard_drinks);
  result = result && (food_type == cons.food_type);
  result = result && (poisoned == cons.poisoned);
  result = result && (get_additional_property(ItemProperties::ITEM_PROPERTIES_METABOLIZES_ALCOHOL) == cons.get_additional_property(ItemProperties::ITEM_PROPERTIES_METABOLIZES_ALCOHOL));

  return result;
}

// Any poison is removed when an item is enchanted.
void Consumable::do_enchant_item(const int points)
{
  if (points > 0)
  {
    poisoned = false;
  }
}

// Consumables don't vary in price with enchantments.
void Consumable::increase_value(const int /*num_points*/)
{
}

int Consumable::get_score() const
{
  return nutrition;
}

bool Consumable::serialize(ostream& stream) const
{
  Item::serialize(stream);
  Serialize::write_int(stream, nutrition);
  Serialize::write_float(stream, standard_drinks);
  Serialize::write_enum(stream, food_type);
  Serialize::write_bool(stream, poisoned);

  return true;
}

bool Consumable::deserialize(istream& stream)
{
  Item::deserialize(stream);
  Serialize::read_int(stream, nutrition);
  Serialize::read_float(stream, standard_drinks);
  Serialize::read_enum(stream, food_type);
  Serialize::read_bool(stream, poisoned);

  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/Consumable_test.cpp"
#endif