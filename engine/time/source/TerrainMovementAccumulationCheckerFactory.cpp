#include "BoatingMovementAccumulationChecker.hpp"
#include "DefaultMovementAccumulationChecker.hpp"
#include "FallingMovementAccumulationChecker.hpp"
#include "MountainClimbingMovementAccumulationChecker.hpp"
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
  bool frozen = accumulation.get_tile_frozen();
  
  if (super_type == TileSuperType::TILE_SUPER_TYPE_WATER && !frozen)
  {
    if (movement == MovementType::MOVEMENT_TYPE_WALKING)
    {
      checker = std::make_unique<SwimmingMovementAccumulationChecker>();
    }
    else if (movement == MovementType::MOVEMENT_TYPE_BOAT)
    {
      checker = std::make_unique<BoatingMovementAccumulationChecker>();
    }
  }
  else if (super_type == TileSuperType::TILE_SUPER_TYPE_AIR && movement == MovementType::MOVEMENT_TYPE_WALKING)
  {
    checker = std::make_unique<FallingMovementAccumulationChecker>();
  }
  else if (tile_type == TileType::TILE_TYPE_MOUNTAINS && (movement == MovementType::MOVEMENT_TYPE_WALKING))
  {
    checker = std::make_unique<MountainClimbingMovementAccumulationChecker>();
  }
  else
  {
    checker = std::make_unique<DefaultMovementAccumulationChecker>();
  }
  
  return checker;
}
