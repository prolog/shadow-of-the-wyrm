#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

class ISkillsCommandProcessor
{
  public:
    virtual ~ISkillsCommandProcessor() = default;

    virtual bool can_process(CreaturePtr creature) = 0;
    virtual ActionCostValue process(CreaturePtr creature, Command* command, MapPtr map, const SkillType st) = 0;
};

using ISkillsCommandProcessorPtr = std::unique_ptr<ISkillsCommandProcessor>;

