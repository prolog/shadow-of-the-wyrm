#pragma once
#include "ISkillsCommandProcessor.hpp"

class ShowSkillsCommandProcessor : public ISkillsCommandProcessor
{
  public:
    ActionCostValue process(CreaturePtr creature, CommandPtr command, MapPtr map, const SkillType st) override;
};

