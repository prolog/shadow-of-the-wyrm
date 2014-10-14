#pragma once
#include "DeityDecisionStrategyHandler.hpp"
#include "Deity.hpp"

class DislikeDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    DislikeDeityDecisionStrategyHandler(const std::string& deity_id);
    DislikeDeityDecisionStrategyHandler(DeityPtr deity);

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;

  protected:
    int get_piety_loss() const override;
    std::string get_message_sid() const override;
    DeityPtr deity;
};
