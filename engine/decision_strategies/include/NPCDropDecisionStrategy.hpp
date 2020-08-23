#pragma once
#include "Command.hpp"
#include "Creature.hpp"
#include "Map.hpp"

class NPCDropDecisionStrategy
{
  public:
    CommandPtr decide(CreaturePtr creature, MapPtr map);
};
