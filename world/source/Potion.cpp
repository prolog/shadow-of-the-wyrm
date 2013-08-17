#include "Potion.hpp"
#include "Serialize.hpp"

using namespace std;

// Potions will provide a bit of nutrition.
Potion::Potion()
: Consumable(50), has_damage(false)
{
  type = ITEM_TYPE_POTION;
  symbol = '!';
}

Potion::~Potion()
{
}

bool Potion::operator==(const Potion& p) const
{
  bool result = Consumable::operator==(p);

  result = result && (has_damage == p.has_damage);
  result = result && (damage == p.damage);

  return result;
}

ItemType Potion::get_type() const
{
  return ITEM_TYPE_POTION;
}

Item* Potion::clone()
{
  return new Potion(*this);
}

void Potion::set_has_damage(const bool new_has_damage)
{
  has_damage = new_has_damage;
}

bool Potion::get_has_damage() const
{
  return has_damage;
}

void Potion::set_damage(const Damage& new_damage)
{
  damage = new_damage;
}

Damage Potion::get_damage() const
{
  return damage;
}

bool Potion::serialize(std::ostream& stream)
{
  Consumable::serialize(stream);
  Serialize::write_bool(stream, has_damage);
  damage.serialize(stream);

  return true;
}

bool Potion::deserialize(std::istream& stream)
{
  Consumable::deserialize(stream);
  Serialize::read_bool(stream, has_damage);
  damage.deserialize(stream);

  return true;
}

ClassIdentifier Potion::internal_class_identifier() const
{
  return CLASS_ID_POTION;
}

#ifdef UNIT_TESTS
#include "unit_tests/Potion_test.cpp"
#endif

