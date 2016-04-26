#pragma once
#include "SkillProcessor.hpp"

class SwimmingSkillProcessor : public SkillProcessor
{
  public:
    ActionCostValue process(CreaturePtr creature, MapPtr map /* unused by SwimmingSkillProcessor */) override;
};
