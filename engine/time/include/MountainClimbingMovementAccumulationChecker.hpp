#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"

class MountainClimbingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature);
};
