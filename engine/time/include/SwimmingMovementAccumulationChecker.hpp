#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"
#include "Swimming.hpp"

class SwimmingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;
    
  protected:
    Swimming swim;
};
