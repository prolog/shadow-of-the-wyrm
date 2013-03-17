#pragma once
#include "IDeityDecisionStrategyHandler.hpp"

class DislikeDeityDecisionStrategyHandler : public IDeityDecisionStrategyHandler
{
  public:
    DeityDecisionImplications handle_decision(CreaturePtr creature);

  protected:
    int get_piety_loss() const;
    std::string get_message_sid() const;

    static const int PIETY_LOSS;
};
