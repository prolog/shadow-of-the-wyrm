#pragma once
#include <memory>
#include "Creature.hpp"
#include "DeityDecisionImplications.hpp"

class DeityDecisionStrategyHandler
{
  public:
    DeityDecisionStrategyHandler(const std::string& deity_id);
    virtual ~DeityDecisionStrategyHandler() = default;

    // Should this strategy be considered, based on the current state
    // of the creature?
    virtual bool decide(CreaturePtr creature) = 0;

    // Returns the base piety loss as a result of handling the decision.
    virtual DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) = 0;
    virtual std::string get_message_sid() const = 0;
    virtual bool get_add_message_with_pause() const;
    virtual bool get_reload_map_music() const;

    virtual std::unique_ptr<DeityDecisionStrategyHandler> clone() = 0;

  protected:
    virtual DeityDecisionImplications get_deity_decision_implications(CreaturePtr creature, TilePtr tile) const;

    virtual int get_piety_amount() const = 0;

    std::string deity_id;
};

using DeityDecisionStrategyHandlerPtr = std::unique_ptr<DeityDecisionStrategyHandler>;
