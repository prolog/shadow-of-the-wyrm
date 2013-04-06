#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"

// This class checks to see if the targetted tile is in range for the
// creature, given the attack type.
class TileSelectionRangeChecker
{
  public:
    bool is_selected_tile_in_range(CreaturePtr creature, const AttackType attack_type);
};
