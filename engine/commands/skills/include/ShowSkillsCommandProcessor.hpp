#pragma once
#include "ISkillsCommandProcessor.hpp"

class ShowSkillsCommandProcessor : public ISkillsCommandProcessor
{
  public:
    bool can_process(CreaturePtr creature) override;
    ActionCostValue process(CreaturePtr creature, Command* command, MapPtr map, const SkillType st) override;
};

