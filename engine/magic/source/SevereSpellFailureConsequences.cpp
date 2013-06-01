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

