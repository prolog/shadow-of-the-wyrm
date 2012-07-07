#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"
#include "MountainClimbingCalculator.hpp"
#include "SkillManager.hpp"

class MountainClimbingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature);
    
  protected:
    void check_for_fall(CreaturePtr creature, const int mountaineering_skill_value);
    
    MountainClimbingCalculator mcc;
    SkillManager sm;
};
