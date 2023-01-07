#pragma once
#include "ITerrainMovementAccumulationChecker.hpp"
#include "MountainClimbingCalculator.hpp"
#include "MountainLoreSkillProcessor.hpp"
#include "SkillManager.hpp"

class MountainClimbingMovementAccumulationChecker : public ITerrainMovementAccumulationChecker
{
  public:
    void check(CreaturePtr creature) override;
    
  protected:
    MountainClimbingCalculator mcc;
    MountainLoreSkillProcessor mountain_lore;
    SkillManager sm;
};
