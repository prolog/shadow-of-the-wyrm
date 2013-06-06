#include "SevereSpellFailureConsequences.hpp"
#include "SpellFailureTextKeys.hpp"

using namespace std;

float SevereSpellFailureConsequences::get_damage_pct() const
{
  return 0.8f;
}

string SevereSpellFailureConsequences::get_damage_message_sid() const
{
  return SpellFailureTextKeys::SPELL_FAILURE_DAMAGE_SEVERE;
}

// Severe spell failure summons two single major undead creatures
pair<Dice, vector<string>> SevereSpellFailureConsequences::get_summoned_creature_details() const
{
  Dice num_creatures(2, 1, 0);
  vector<string> creature_ids;

  creature_ids.push_back("lich");
  creature_ids.push_back("skeletal_dragon");
  creature_ids.push_back("reaper");

  pair<Dice, vector<string>> summoned_creature_details(num_creatures, creature_ids);
  return summoned_creature_details;
}