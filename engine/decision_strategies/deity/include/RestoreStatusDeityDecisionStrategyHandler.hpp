#pragma once
#include "IDeityDecisionStrategyHandler.hpp"

class RestoreStatusDeityDecisionStrategyHandler : public IDeityDecisionStrategyHandler
{
  public:
    RestoreStatusDeityDecisionStrategyHandler();

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature) override;

    std::string get_message_sid() const override;

  protected:
    void initialize_watched_statuses();

    int get_piety_loss() const override;

    int piety_loss;
    std::vector<std::string> watched_statuses;
};
