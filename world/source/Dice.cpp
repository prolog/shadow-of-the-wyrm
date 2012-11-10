#include "Conversion.hpp"
#include "Dice.hpp"
#include "Serialize.hpp"

using namespace std;

Dice::Dice()
: num_dice(0), dice_sides(0), modifier(0)
{
}

Dice::Dice(const uint new_num_dice, const uint new_num_sides, const int new_mod)
: num_dice(new_num_dice), dice_sides(new_num_sides), modifier(new_mod)
{
}

Dice::~Dice()
{
}

int Dice::max() const
{
  return ((num_dice * dice_sides) + modifier);
}

void Dice::set_num_dice(const uint new_num_dice)
{
  num_dice = new_num_dice;
}

uint Dice::get_num_dice() const
{
  return num_dice;
}

void Dice::set_dice_sides(const uint new_dice_sides)
{
  dice_sides = new_dice_sides;
}

uint Dice::get_dice_sides() const
{
  return dice_sides;
}

void Dice::set_modifier(const int new_modifier)
{
  modifier = new_modifier;
}

int Dice::get_modifier() const
{
  return modifier;
}

string Dice::str() const
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

bool Dice::serialize(ostream& stream)
{
  Serialize::write_uint(stream, num_dice);
  Serialize::write_uint(stream, dice_sides);
  Serialize::write_int(stream, modifier);

  return true;
}

bool Dice::deserialize(istream& stream)
{
  Serialize::read_uint(stream, num_dice);
  Serialize::read_uint(stream, dice_sides);
  Serialize::read_int(stream, modifier);

  return true;
}

ClassIdentifier Dice::internal_class_identifier() const
{
  return CLASS_ID_DICE;
}

#ifdef UNIT_TESTS
#include "unit_tests/Dice_test.cpp"
#endif

