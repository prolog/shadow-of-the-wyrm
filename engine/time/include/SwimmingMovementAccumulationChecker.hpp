#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"
#include "SwimmingCalculator.hpp"

class SwimmingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature);
    
  protected:
    void drown(CreaturePtr creature);
    
    SwimmingCalculator sc;
};
