#pragma once
#include <boost/shared_ptr.hpp>
#include "DeityDecisionTypes.hpp"
#include "Creature.hpp"

class IDeityDecisionStrategy
{
  public:
    virtual DeityDecisionType get_decision(CreaturePtr creature) = 0;
};

typedef boost::shared_ptr<IDeityDecisionStrategy> IDeityDecisionStrategyPtr;

