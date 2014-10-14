#pragma once
#include "IDeityDecisionStrategy.hpp"

// Concrete implementation of the deity decision strategy.  Right now,
// this is used for all deities - once the actual differentiation begins,
// there will be multiple concrete implementations handled by the
// factory.
class DeityDecisionStrategy : public IDeityDecisionStrategy
{
  public:
    DeityDecisionStrategy(const std::string& new_deity_id);
    
    DeityDecisionStrategyHandlerPtr get_decision(CreaturePtr creature) override;
    DeityDecisionStrategyHandlerPtr get_decision_for_sacrifice(CreaturePtr creature, ItemPtr item) override;

  protected:
    // Should be initialized differently by deity.
    virtual void initialize_decisions();

    std::vector<DeityDecisionStrategyHandlerPtr> decisions;
    std::string deity_id;
};
