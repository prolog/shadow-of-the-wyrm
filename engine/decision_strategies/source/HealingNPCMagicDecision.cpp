#include "HealingNPCMagicDecision.hpp"

const float HealingNPCMagicDecision::HEALING_THRESHOLD_MULTIPLIER = 0.5f;

bool HealingNPCMagicDecision::decide(CreaturePtr caster, MapPtr view_map, const Spell& spell) const
{
  bool decision = false;

  // Consider only the caster for healing magic.  View map can be ignored.
  if (caster != nullptr)
  {
    EffectType eff = spell.get_effect();

    if (eff == EffectType::EFFECT_TYPE_HEALING)
    {
      Statistic hp = caster->get_hit_points();

      if (hp.get_current() <= static_cast<int>(hp.get_base() * HEALING_THRESHOLD_MULTIPLIER)) 
      {
        decision = true;
      }
    }
    // No need to check for mute - can't cast if the creature can't speak!
    else if (eff == EffectType::EFFECT_TYPE_ANTIDOTE)
    {
      if (caster->has_status(StatusIdentifiers::STATUS_ID_POISON))
      {
        decision = true;
      }
    }
    else if (eff == EffectType::EFFECT_TYPE_UNBLINDING)
    {
      if (caster->has_status(StatusIdentifiers::STATUS_ID_BLINDED))
      {
        decision = true;
      }
    }
    else if (eff == EffectType::EFFECT_TYPE_UNSTONING)
    {
      if (caster->has_status(StatusIdentifiers::STATUS_ID_STONE))
      {
        decision = true;
      }
    }
  }

  return decision;
}
