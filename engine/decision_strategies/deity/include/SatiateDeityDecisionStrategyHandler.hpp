#pragma once
#include "DeityDecisionStrategyHandler.hpp"

class SatiateDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    SatiateDeityDecisionStrategyHandler(const std::string& new_deity_id);

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;
    std::string get_message_sid() const override;

  protected:
    int get_piety_loss() const override;
};
