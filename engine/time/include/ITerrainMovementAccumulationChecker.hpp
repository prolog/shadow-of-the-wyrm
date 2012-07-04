#pragma once
#include <boost/shared_ptr.hpp>
#include "Creature.hpp"

class ITerrainMovementAccumulationChecker
{
  public:
    virtual void check(CreaturePtr creature) = 0;
};

typedef boost::shared_ptr<ITerrainMovementAccumulationChecker> ITerrainMovementAccumulationCheckerPtr;
