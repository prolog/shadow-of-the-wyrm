#pragma once
#include <memory>
#include "ActionCost.hpp"
#include "Map.hpp"

// Implementing classes should return:
// -1, if the skill does not advance the clock.
// >= 1, if the skill advances the clock.
class SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) = 0;

  protected:
    virtual ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const;
};

using SkillProcessorPtr = std::shared_ptr<SkillProcessor>;

