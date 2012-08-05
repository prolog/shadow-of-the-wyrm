#include <string>
#include <sstream>
#include "Conversion.hpp"
#include "Damage.hpp"

using std::string;
using std::ostringstream;

Damage::Damage()
: Dice(0, 0, 0), damage_type(DAMAGE_TYPE_SLASH)
{
}

Damage::Damage(const uint dice, const uint sides, const int mod, const DamageType dtype)
: Dice(dice, sides, mod), damage_type(dtype)
{
}

Damage::Damage(const Damage& d)
: Dice(d.num_dice, d.dice_sides, d.modifier), damage_type(d.damage_type)
{
}

Damage& Damage::operator=(const Damage& d)
{
  if (this != &d)
  {
    num_dice   = d.num_dice;
    dice_sides = d.dice_sides;
    modifier   = d.modifier;
    damage_type= d.damage_type;
  }
  
  return *this;
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

void Damage::set_additional_damage(DamagePtr new_additional_damage)
{
  additional_damage = new_additional_damage;
}

bool Damage::has_additional_damage() const
{
  return (additional_damage);
}

DamagePtr Damage::get_additional_damage()
{
  return additional_damage;
}

string Damage::str() const
{
  ostringstream ss;
  string modifier_s;
  
  ss << num_dice << "d" << dice_sides;
  
  if (modifier > 0)
  {
    modifier_s = "+";
  }
  else if (modifier < 0)
  {
    modifier_s = "-";
  }
  
  if (!modifier_s.empty())
  {
    ss << modifier_s << modifier;
  }
  
  if (additional_damage)
  {
    ss << "+" << additional_damage->str();
  }

  return ss.str();
}

#ifdef UNIT_TESTS
#include "unit_tests/Damage_test.cpp"
#endif
