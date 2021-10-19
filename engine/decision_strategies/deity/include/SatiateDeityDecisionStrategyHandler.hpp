#pragma once
#include "DeityDecisionStrategyHandler.hpp"

class SatiateDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    SatiateDeityDecisionStrategyHandler(const std::string& new_deity_id);

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;
    std::string get_message_sid() const override;

    virtual std::unique_ptr<DeityDecisionStrategyHandler> clone() override;

  protected:
    int get_piety_amount() const override;
};
