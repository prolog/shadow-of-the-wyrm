#pragma once
#include "IDeityDecisionStrategy.hpp"

// Concrete implementation of the deity decision strategy.  Right now,
// this is used for all deities - once the actual differentiation begins,
// there will be multiple concrete implementations handled by the
// factory.
class DeityDecisionStrategy : public IDeityDecisionStrategy
{
  public:
    DeityDecisionType get_decision(CreaturePtr creature);
};
