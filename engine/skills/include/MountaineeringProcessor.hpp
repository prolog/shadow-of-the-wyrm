#pragma once
#include "SkillProcessor.hpp"

class MountaineeringProcessor : public SkillProcessor
{
  public:
    ActionCostValue process(CreaturePtr creature, MapPtr map /* Unused by MountaineeringProcessor */);
};
