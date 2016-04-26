#pragma once
#include "SkillProcessor.hpp"

class MountaineeringSkillProcessor : public SkillProcessor
{
  public:
    ActionCostValue process(CreaturePtr creature, MapPtr map /* Unused by MountaineeringSkillProcessor */);
};
