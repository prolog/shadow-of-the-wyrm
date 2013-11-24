#include "LesserSpellFailureConsequences.hpp"
#include "SpellFailureTextKeys.hpp"

using namespace std;

float LesserSpellFailureConsequences::get_damage_pct() const
{
  return 0.25f;
}

string LesserSpellFailureConsequences::get_damage_message_sid() const
{
  return SpellFailureTextKeys::SPELL_FAILURE_DAMAGE_LESSER;
}

// Lesser summons include 2d3 undead - mostly minor undead, with the chance
// of a regular undead as well.
pair<Dice, vector<string>> LesserSpellFailureConsequences::get_summoned_creature_details() const
{
  Dice num_creatures(2, 3, 0);
  vector<string> creature_ids{"thrall", "thrall", "skeleton", "skeleton", "mummy", "shade"};

  pair<Dice, vector<string>> summoned_creature_details(num_creatures, creature_ids);
  return summoned_creature_details;
}

string LesserSpellFailureConsequences::get_summoned_creatures_message_sid() const
{
  return SpellFailureTextKeys::SPELL_FAILURE_SUMMONED_CREATURES_LESSER;
}