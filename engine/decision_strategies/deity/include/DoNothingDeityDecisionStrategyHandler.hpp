#pragma once
#include "IDeityDecisionStrategyHandler.hpp"

class DoNothingDeityDecisionStrategyHandler : public IDeityDecisionStrategyHandler
{
  public:
    bool decide(CreaturePtr creature);
    DeityDecisionImplications handle_decision(CreaturePtr creature);

  protected:
    int get_piety_loss() const;
    std::string get_message_sid() const;
    
    static const int DO_NOTHING_PIETY_LOSS;
};
