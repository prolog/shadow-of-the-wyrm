#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"

class FallingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;
};
