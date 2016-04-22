#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"
#include "SwimmingProcessor.hpp"

class SwimmingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;
    
  protected:
    SwimmingProcessor swim;
};
