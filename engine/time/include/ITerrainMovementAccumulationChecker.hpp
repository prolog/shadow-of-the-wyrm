#pragma once
#include <boost/shared_ptr.hpp>
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

typedef boost::shared_ptr<ITerrainMovementAccumulationChecker> ITerrainMovementAccumulationCheckerPtr;
