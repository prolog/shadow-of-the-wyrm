#pragma once
#include <memory>
#include "ActionCost.hpp"
#include "Map.hpp"

// Implementing classes should return:
// -1, if the skill does not advance the clock.
// >= 1, if the skill advances the clock.
class ISkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) = 0;
};

using ISkillProcessorPtr = std::shared_ptr<ISkillProcessor>;

