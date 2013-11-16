#pragma once
#include <boost/shared_ptr.hpp>
#include "Creature.hpp"
#include "DeityDecisionImplications.hpp"

class IDeityDecisionStrategyHandler
{
  public:
    // Should this strategy be considered, based on the current state
    // of the creature?
    virtual bool decide(CreaturePtr creature) = 0;

    // Returns the base piety loss as a result of handling the decision.
    virtual DeityDecisionImplications handle_decision(CreaturePtr creature) = 0;
    virtual std::string get_message_sid() const = 0;

  protected:
    virtual DeityDecisionImplications get_deity_decision_implications() const;

    virtual int get_piety_loss() const = 0;
};

typedef boost::shared_ptr<IDeityDecisionStrategyHandler> IDeityDecisionStrategyHandlerPtr;
