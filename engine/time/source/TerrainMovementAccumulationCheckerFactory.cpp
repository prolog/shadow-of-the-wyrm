#include <boost/make_shared.hpp>
#include "BoatingMovementAccumulationChecker.hpp"
#include "MountainClimbingMovementAccumulationChecker.hpp"
#include "NullMovementAccumulationChecker.hpp"
#include "SwimmingMovementAccumulationChecker.hpp"
#include "TerrainMovementAccumulationCheckerFactory.hpp"

TerrainMovementAccumulationCheckerFactory::TerrainMovementAccumulationCheckerFactory()
{
}

TerrainMovementAccumulationCheckerFactory::~TerrainMovementAccumulationCheckerFactory()
{
}

ITerrainMovementAccumulationCheckerPtr TerrainMovementAccumulationCheckerFactory::create_terrain_movement_accumulation_checker(const MovementAccumulation& accumulation)
{
  ITerrainMovementAccumulationCheckerPtr checker;

  TileSuperType super_type = accumulation.get_tile_super_type();
  TileType tile_type = accumulation.get_tile_type();
  MovementType movement = accumulation.get_movement_type();
  
  if (super_type == TILE_SUPER_TYPE_WATER)
  {
    if (movement == MOVEMENT_TYPE_WALKING)
    {
      checker = boost::make_shared<SwimmingMovementAccumulationChecker>();
    }
    else if (movement == MOVEMENT_TYPE_BOAT)
    {
      checker = boost::make_shared<BoatingMovementAccumulationChecker>();
    }
  }
  else if (tile_type == TILE_TYPE_MOUNTAINS && (movement == MOVEMENT_TYPE_WALKING))
  {
    checker = boost::make_shared<MountainClimbingMovementAccumulationChecker>();
  }
  else
  {
    checker = boost::make_shared<NullMovementAccumulationChecker>();
  }
  
  return checker;
}
