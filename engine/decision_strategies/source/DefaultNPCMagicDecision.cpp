#include "DefaultNPCMagicDecision.hpp"

// Optimistic: if the creature *can* cast it, cast it!
bool DefaultNPCMagicDecision::decide(CreaturePtr caster, MapPtr view_map, const Spell& spell) const
{
  bool decision = false;

  if (caster != nullptr)
  {
    if (spell.get_ap_cost() <= static_cast<uint>(caster->get_arcana_points().get_current()))
    {
      decision = true;
    }
  }

  return decision;
}
