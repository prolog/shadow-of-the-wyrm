#pragma once
#include <memory>
#include "Map.hpp"

// Interface for a general tile manipulator: allows digging, etc.
class ITileManipulator
{
  public:
    virtual bool dig(CreaturePtr creature, MapPtr map, TilePtr tile) = 0;
};

using ITileManipulatorPtr = std::shared_ptr<ITileManipulator>;
