#pragma once
#include "TileSafetyCondition.hpp"

// A class used to determine if a tile is safe, given that it has a super
// type of water.
class WaterSafetyCondition : public TileSafetyCondition
{
  protected:
    bool is_tile_safe(CreaturePtr creature, TilePtr tile) const override;
};

