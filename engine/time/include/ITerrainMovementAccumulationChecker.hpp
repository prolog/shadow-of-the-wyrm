#pragma once
#include <memory>
#include "Creature.hpp"
#include "SkillManager.hpp"

class ITerrainMovementAccumulationChecker
{
  public:
    virtual ~ITerrainMovementAccumulationChecker() {};

    virtual void check(CreaturePtr creature) = 0;
    
  protected:
    SkillManager sm;
};

typedef std::shared_ptr<ITerrainMovementAccumulationChecker> ITerrainMovementAccumulationCheckerPtr;
