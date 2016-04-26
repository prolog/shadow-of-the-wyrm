#include "FishingSkillProcessor.hpp"

ActionCostValue FishingSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  if (creature && map)
  {
    // Are we on the world map?

    // Are we land-locked?

    // Does the creature have the necessary equipment?
  }

  return get_default_skill_action_cost_value(creature);
}

