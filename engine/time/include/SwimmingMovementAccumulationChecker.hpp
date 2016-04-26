#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"
#include "SwimmingSkillProcessor.hpp"

class SwimmingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;
    
  protected:
    SwimmingSkillProcessor swim;
};
