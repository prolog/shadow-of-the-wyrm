#pragma once
#include <memory>
#include "Tile.hpp"

// Interface for a general tile manipulator: allows digging, etc.
class ITileManipulator
{
  public:
    virtual bool dig(CreaturePtr creature, TilePtr tile) = 0;
};

typedef std::shared_ptr<ITileManipulator> ITileManipulatorPtr;
