#include <string>
#include "Conversion.hpp"
#include "Damage.hpp"

using std::string;

Damage::Damage()
: Dice(0, 0, 0), damage_type(DAMAGE_TYPE_SLASH)
{
}

Damage::Damage(const uint dice, const uint sides, const int mod, const DamageType dtype)
: Dice(dice, sides, mod), damage_type(dtype)
{
}

Damage::~Damage()
{
}

void Damage::set_damage_type(const DamageType new_damage_type)
{
  damage_type = new_damage_type;
}

DamageType Damage::get_damage_type() const
{
  return damage_type;
}

#ifdef UNIT_TESTS
#include "unit_tests/Damage_test.cpp"
#endif
