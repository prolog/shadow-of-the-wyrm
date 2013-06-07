#include "MarginalSpellFailureConsequences.hpp"
#include "SpellFailureTextKeys.hpp"

using namespace std;

float MarginalSpellFailureConsequences::get_damage_pct() const
{
  return 0;
}

string MarginalSpellFailureConsequences::get_damage_message_sid() const
{
  return SpellFailureTextKeys::SPELL_FAILURE_DAMAGE_MARGINAL;
}

pair<Dice, vector<string>> MarginalSpellFailureConsequences::get_summoned_creature_details() const
{
  Dice no_creatures;
  vector<string> no_creature_ids;
  pair<Dice, vector<string>> no_summoned_creatures(no_creatures, no_creature_ids);

  return no_summoned_creatures;
}

string MarginalSpellFailureConsequences::get_summoned_creatures_message_sid() const
{
  return SpellFailureTextKeys::SPELL_FAILURE_SUMMONED_CREATURES_MARGINAL;
}