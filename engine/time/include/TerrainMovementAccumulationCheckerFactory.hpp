#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"

class TerrainMovementAccumulationCheckerFactory
{
  public:
    static ITerrainMovementAccumulationCheckerPtr create_terrain_movement_accumulation_checker(const MovementAccumulation& accumulation);

  protected:
    TerrainMovementAccumulationCheckerFactory();
    ~TerrainMovementAccumulationCheckerFactory();
};
