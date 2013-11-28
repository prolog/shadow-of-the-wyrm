#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"

class NullMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;
};
