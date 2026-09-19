#pragma once
#include "Command.hpp"
#include "Creature.hpp"
#include "Map.hpp"

class NPCDropDecisionStrategy
{
  public:
    CommandPtr decide(CreaturePtr creature, MapPtr map);

  protected:
    CommandPtr get_drop_decision_overburdened(CreaturePtr creature, MapPtr map);
    CommandPtr get_drop_decision(CreaturePtr creature, MapPtr map);
};
