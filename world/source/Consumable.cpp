#include "Consumable.hpp"
#include "Serialize.hpp"

using namespace std;

Consumable::Consumable()
: nutrition(0), standard_drinks(0.0f)
{
}

Consumable::Consumable(const int nutr, const float std_drinks)
: nutrition(nutr), standard_drinks(std_drinks)
{
}

bool Consumable::operator==(const Consumable& consumable) const
{
  bool result = true;

  result = result && Item::operator==(consumable);
  result = result && (nutrition == consumable.nutrition);
  result = result && (standard_drinks == consumable.standard_drinks);

  return result;
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

bool Consumable::serialize(ostream& stream) const
{
  Item::serialize(stream);
  Serialize::write_int(stream, nutrition);
  Serialize::write_float(stream, standard_drinks);

  return true;
}

bool Consumable::deserialize(istream& stream)
{
  Item::deserialize(stream);
  Serialize::read_int(stream, nutrition);
  Serialize::read_float(stream, standard_drinks);

  return true;
}
