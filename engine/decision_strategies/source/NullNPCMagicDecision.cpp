#include "NullNPCMagicDecision.hpp"

bool NullNPCMagicDecision::decide(CreaturePtr caster, MapPtr view_map, const Spell& spell) const
{
  return false;
}

