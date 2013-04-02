#include "Spell.hpp"

using namespace std;

Spell::Spell()
: magic_category(SKILL_MAGIC_ARCANE)
{
}

Spell::Spell(const string& new_spell_id, const string& new_spell_name_sid, const SkillType new_magic_category)
: spell_id(new_spell_id), spell_name_sid(new_spell_name_sid), magic_category(new_magic_category)
{
}

bool Spell::operator==(const Spell& spell)
{
  bool result = true;

  result = result && (spell_id == spell.spell_id);
  result = result && (spell_name_sid == spell.spell_name_sid);
  result = result && (magic_category == spell.magic_category);

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

#ifdef UNIT_TESTS
#include "unit_tests/Spell_test.cpp"
#endif