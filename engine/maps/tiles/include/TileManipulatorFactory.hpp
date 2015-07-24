#pragma once
#include "ITileManipulator.hpp"

class TileManipulatorFactory
{
  public:
    ITileManipulatorPtr create_tile_manipulator(TilePtr tile);
};

