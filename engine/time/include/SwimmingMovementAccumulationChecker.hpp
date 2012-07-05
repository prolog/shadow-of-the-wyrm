#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"

class SwimmingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature);
};
