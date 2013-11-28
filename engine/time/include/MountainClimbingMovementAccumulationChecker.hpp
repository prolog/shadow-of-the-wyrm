#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"
#include "MountainClimbingCalculator.hpp"
#include "Mountaineering.hpp"
#include "SkillManager.hpp"

class MountainClimbingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;
    
  protected:
    MountainClimbingCalculator mcc;
    Mountaineering mountaineering;
    SkillManager sm;
};
