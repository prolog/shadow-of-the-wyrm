#pragma once
#include "IDeityDecisionStrategyHandler.hpp"

class DoNothingDeityDecisionStrategyHandler : public IDeityDecisionStrategyHandler
{
  public:
    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature) override;

  protected:
    int get_piety_loss() const override;
    std::string get_message_sid() const override;
};
