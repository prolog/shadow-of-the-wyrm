#pragma once
#include "SkillProcessor.hpp"

class FishingSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
};

