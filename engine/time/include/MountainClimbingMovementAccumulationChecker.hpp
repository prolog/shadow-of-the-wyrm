#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"
#include "MountainClimbingCalculator.hpp"
#include "MountaineeringProcessor.hpp"
#include "SkillManager.hpp"

class MountainClimbingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;
    
  protected:
    MountainClimbingCalculator mcc;
    MountaineeringProcessor mountaineering;
    SkillManager sm;
};
