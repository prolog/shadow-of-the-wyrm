#pragma once
#include "IDeityDecisionStrategyHandler.hpp"

class RestoreStatusDeityDecisionStrategyHandler : public IDeityDecisionStrategyHandler
{
  public:
    RestoreStatusDeityDecisionStrategyHandler();

    bool decide(CreaturePtr creature);
    DeityDecisionImplications handle_decision(CreaturePtr creature);

  protected:
    void initialize_watched_statuses();

    int get_piety_loss() const;
    std::string get_message_sid() const;

    int piety_loss;
    std::vector<std::string> watched_statuses;
};
