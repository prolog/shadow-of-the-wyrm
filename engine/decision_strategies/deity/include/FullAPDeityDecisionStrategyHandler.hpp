#pragma once
#include "DeityDecisionStrategyHandler.hpp"

class FullAPDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;
    std::string get_message_sid() const override;

  protected:
    int get_piety_loss() const override;
};
