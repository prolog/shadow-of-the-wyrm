#include "Spell.hpp"

using namespace std;

Spell::Spell()
: magic_category(SKILL_MAGIC_ARCANE), ap_cost(0), speed(1), range(0)
{
}

bool Spell::operator==(const Spell& spell)
{
  bool result = true;

  result = result && (spell_id == spell.spell_id);
  result = result && (spell_name_sid == spell.spell_name_sid);
  result = result && (magic_category == spell.magic_category);
  result = result && (ap_cost == spell.ap_cost);
  result = result && (speed == spell.speed);
  result = result && (range == spell.range);

  return result;
}

void Spell::set_spell_id(const string& new_spell_id)
{
  spell_id = new_spell_id;
}

string Spell::get_spell_id() const
{
  return spell_id;
}

void Spell::set_spell_name_sid(const string& new_spell_name_sid)
{
  spell_name_sid = new_spell_name_sid;
}

string Spell::get_spell_name_sid() const
{
  return spell_name_sid;
}

void Spell::set_magic_category(const SkillType new_magic_category)
{
  magic_category = new_magic_category;
}

SkillType Spell::get_magic_category() const
{
  return magic_category;
}

void Spell::set_ap_cost(const uint new_ap_cost)
{
  ap_cost = new_ap_cost;
}

uint Spell::get_ap_cost() const
{
  return ap_cost;
}

void Spell::set_speed(const int new_speed)
{
  speed = new_speed;
}

int Spell::get_speed() const
{
  return speed;
}

void Spell::set_range(const uint new_range)
{
  range = new_range;
}

uint Spell::get_range() const
{
  return range;
}

#ifdef UNIT_TESTS
#include "unit_tests/Spell_test.cpp"
#endif