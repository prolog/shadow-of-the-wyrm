#pragma once
#include "ITileManipulator.hpp"

// Default tile manipulator.  Defines manipulation operations that do
// very little - if there's any tile-specific behaviour, the factory
// will instantiate a different class.
class DefaultTileManipulator : public ITileManipulator
{
  public:
    bool dig(CreaturePtr creature, TilePtr tile) override;
};

