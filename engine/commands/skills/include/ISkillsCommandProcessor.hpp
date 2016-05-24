#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

class ISkillsCommandProcessor
{
  public:
    virtual bool can_process(CreaturePtr creature) = 0;
    virtual ActionCostValue process(CreaturePtr creature, CommandPtr command, MapPtr map, const SkillType st) = 0;
};

using ISkillsCommandProcessorPtr = std::shared_ptr<ISkillsCommandProcessor>;

