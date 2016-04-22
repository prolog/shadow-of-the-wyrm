#pragma once
#include "SkillProcessor.hpp"

class SwimmingProcessor : public SkillProcessor
{
  public:
    ActionCostValue process(CreaturePtr creature, MapPtr map /* unused by SwimmingProcessor */) override;
};
