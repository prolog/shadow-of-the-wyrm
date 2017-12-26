#pragma once
#include "SkillProcessor.hpp"

class StealthSkillProcessor : public SkillProcessor
{
  public:
    ActionCostValue process(CreaturePtr creature, MapPtr map);
};

