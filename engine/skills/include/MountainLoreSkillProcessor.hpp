#pragma once
#include "SkillProcessor.hpp"

class MountainLoreSkillProcessor : public SkillProcessor
{
  public:
    ActionCostValue process(CreaturePtr creature, MapPtr map /* Unused by MountainLoreSkillProcessor */);
    virtual SkillProcessorPtr clone() override;

};
