#pragma once
#include "IDeityDecisionStrategyHandler.hpp"

class FullAPDeityDecisionStrategyHandler : public IDeityDecisionStrategyHandler
{
  public:
    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature) override;
    std::string get_message_sid() const override;

  protected:
    int get_piety_loss() const override;
};
