#pragma once
#include "ISkillsCommandProcessor.hpp"

class GainSkillsCommandProcessor : public ISkillsCommandProcessor
{
  public:
    bool can_process(CreaturePtr creature) override;
    ActionCostValue process(CreaturePtr creature, Command* command, MapPtr map, const SkillType st) override;
};
