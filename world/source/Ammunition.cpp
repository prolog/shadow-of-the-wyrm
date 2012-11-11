#include "Ammunition.hpp"
#include "Serialize.hpp"

using namespace std;

Ammunition::Ammunition()
{
  type = ITEM_TYPE_AMMUNITION;
  symbol = '/';
}

Ammunition::~Ammunition()
{
}

bool Ammunition::operator==(const Ammunition& ammo)
{
  bool result = true;

  result = result && Item::operator==(ammo);
  result = result && (requires_ranged_weapon == ammo.requires_ranged_weapon);

  return result;
}

EquipmentWornLocation Ammunition::get_worn_location() const
{
  return EQUIPMENT_WORN_AMMUNITION;
}

Item* Ammunition::clone()
{
  return new Ammunition(*this);
}

bool Ammunition::serialize(ostream& stream)
{
  RangedWeapon::serialize(stream);
  Serialize::write_bool(stream, requires_ranged_weapon);

  return true;
}

bool Ammunition::deserialize(istream& stream)
{
  RangedWeapon::deserialize(stream);
  Serialize::read_bool(stream, requires_ranged_weapon);

  return true;
}

ClassIdentifier Ammunition::internal_class_identifier() const
{
  return CLASS_ID_AMMUNITION;
}

#ifdef UNIT_TESTS
#include "unit_tests/Ammunition_test.cpp"
#endif

