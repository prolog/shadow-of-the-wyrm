#pragma once
#include "TileSafetyCondition.hpp"

// A class used to determine if an Air tile is safe.
class AirSafetyCondition : public TileSafetyCondition
{
  protected:
    bool is_tile_safe(CreaturePtr creature, TilePtr tile) const override;
};

