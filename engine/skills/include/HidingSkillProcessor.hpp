#pragma once
#include "SkillProcessor.hpp"

class HidingSkillProcessor : public SkillProcessor
{
  public:
    ActionCostValue process(CreaturePtr creature, MapPtr map);
};

