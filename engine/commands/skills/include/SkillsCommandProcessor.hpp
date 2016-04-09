#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

class SkillsCommandProcessor
{
  public:
    static ActionCostValue process(CreaturePtr creature, CommandPtr command);

  protected:
    SkillsCommandProcessor();
    ~SkillsCommandProcessor();
};
