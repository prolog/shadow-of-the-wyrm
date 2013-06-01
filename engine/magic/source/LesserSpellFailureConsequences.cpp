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

