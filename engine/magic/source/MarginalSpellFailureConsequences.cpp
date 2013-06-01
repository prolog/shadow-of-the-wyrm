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
