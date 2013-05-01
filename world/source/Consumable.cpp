#include "Consumable.hpp"
#include "Serialize.hpp"

using namespace std;

Consumable::Consumable()
: nutrition(0)
{
}

Consumable::Consumable(const int nutr)
: nutrition(nutr)
{
}

Consumable::~Consumable()
{
}

bool Consumable::operator==(const Consumable& consumable) const
{
  bool result = true;

  result = result && Item::operator==(consumable);
  result = result && (nutrition == consumable.nutrition);

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

bool Consumable::serialize(ostream& stream)
{
  Item::serialize(stream);
  Serialize::write_int(stream, nutrition);

  return true;
}

bool Consumable::deserialize(istream& stream)
{
  Item::deserialize(stream);
  Serialize::read_int(stream, nutrition);

  return true;
}
