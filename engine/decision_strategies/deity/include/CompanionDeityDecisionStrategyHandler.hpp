#pragma once
#include "DeityDecisionStrategyHandler.hpp"

class CompanionDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    CompanionDeityDecisionStrategyHandler(const std::string& new_deity_id);

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;

    virtual std::unique_ptr<DeityDecisionStrategyHandler> clone() override;

  protected:
    int get_piety_loss() const override;
    std::string get_message_sid() const override;

    static const int MIN_PIETY_FOR_COMPANION;
};
