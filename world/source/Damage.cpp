#include <string>
#include "Conversion.hpp"
#include "Damage.hpp"

using std::string;

Damage::Damage()
: num_dice(0), dice_sides(0), modifier(0), damage_type(DAMAGE_TYPE_SLASH)
{
}

Damage::~Damage()
{
}

void Damage::set_num_dice(const int new_num_dice)
{
  num_dice = new_num_dice;
}

int Damage::get_num_dice() const
{
  return num_dice;
}

void Damage::set_dice_sides(const int new_dice_sides)
{
  dice_sides = new_dice_sides;
}

int Damage::get_dice_sides() const
{
  return dice_sides;
}

void Damage::set_modifier(const int new_modifier)
{
  modifier = new_modifier;
}

int Damage::get_modifier() const
{
  return modifier;
}

void Damage::set_damage_type(const DamageType new_damage_type)
{
  damage_type = new_damage_type;
}

DamageType Damage::get_damage_type() const
{
  return damage_type;
}

string Damage::str() const
{
  string damage;
  
  damage = Integer::to_string(num_dice) + "d" + Integer::to_string(dice_sides);
  
  if (modifier > -1)
  {
    damage = damage + "+";
  }
  else
  {
    damage = damage + "-";
  }
  
  damage = damage + Integer::to_string(modifier);

  return damage;
}

#ifdef UNIT_TESTS
#include "unit_tests/Damage_test.cpp"
#endif
