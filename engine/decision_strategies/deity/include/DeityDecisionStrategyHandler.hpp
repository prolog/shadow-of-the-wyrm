#pragma once
#include <memory>
#include "Creature.hpp"
#include "DeityDecisionImplications.hpp"

class DeityDecisionStrategyHandler
{
  public:
    DeityDecisionStrategyHandler(const std::string& deity_id);

    // Should this strategy be considered, based on the current state
    // of the creature?
    virtual bool decide(CreaturePtr creature) = 0;

    // Returns the base piety loss as a result of handling the decision.
    virtual DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) = 0;
    virtual std::string get_message_sid() const = 0;

  protected:
    virtual DeityDecisionImplications get_deity_decision_implications(CreaturePtr creature, TilePtr tile) const;

    virtual int get_piety_loss() const = 0;

    std::string deity_id;
};

typedef std::shared_ptr<DeityDecisionStrategyHandler> DeityDecisionStrategyHandlerPtr;
