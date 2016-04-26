#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"
#include "MountainClimbingCalculator.hpp"
#include "MountaineeringSkillProcessor.hpp"
#include "SkillManager.hpp"

class MountainClimbingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;
    
  protected:
    MountainClimbingCalculator mcc;
    MountaineeringSkillProcessor mountaineering;
    SkillManager sm;
};
