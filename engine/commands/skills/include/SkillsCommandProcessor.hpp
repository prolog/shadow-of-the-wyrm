#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

class SkillsCommandProcessor
{
  public:
    static ActionCostValue process(CreaturePtr creature, CommandPtr command, MapPtr map, const SkillType st);

  protected:
    SkillsCommandProcessor();
    ~SkillsCommandProcessor();
};
