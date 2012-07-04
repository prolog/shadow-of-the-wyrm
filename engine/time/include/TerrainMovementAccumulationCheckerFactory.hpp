#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"

class TerrainMovementAccumulationCheckerFactory
{
  public:
    static ITerrainMovementAccumulationCheckerPtr create_terrain_movement_accumulation_checker();

  protected:
    TerrainMovementAccumulationCheckerFactory();
    ~TerrainMovementAccumulationCheckerFactory();
};
