#include "SkillProcessor.hpp"

bool SkillProcessor::is_skill_implemented() const
{
  return true;
}

ActionCostValue SkillProcessor::get_default_skill_action_cost_value(CreaturePtr /*creature*/) const
{
  return 1;
}

