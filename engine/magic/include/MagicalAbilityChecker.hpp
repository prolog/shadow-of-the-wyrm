#pragma once
#include "Creature.hpp"

// A class to check whether a creature has sufficient magical resources to
// cast spells, or even any magical abilities at all.
class MagicalAbilityChecker
{
  public:
    bool has_magical_knowledge(CreaturePtr creature) const;
};

