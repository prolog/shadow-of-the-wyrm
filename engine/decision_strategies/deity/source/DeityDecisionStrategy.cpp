#include "DeityDecisionConstants.hpp"
#include "DeityDecisionStrategy.hpp"

// Right now, always do nothing (test).
DeityDecisionType DeityDecisionStrategy::get_decision(CreaturePtr creature)
{
  DeityDecisionType decision_type = DEITY_DECISION_NOTHING;

  if (creature)
  {
    Statistic hp = creature->get_hit_points();
    
    // Only heal the creature if the creature is hurting a little bit.
    if (hp.get_current() < (hp.get_base() * DeityDecisionConstants::HEAL_HP_MAX_PCT))
    {
      decision_type = DEITY_DECISION_FULL_HP;
    }
  }

  return decision_type;
}
