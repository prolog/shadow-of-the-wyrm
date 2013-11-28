#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"

class BoatingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;
};
