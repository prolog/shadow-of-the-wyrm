#pragma once
#include "DeityDecisionStrategyHandler.hpp"
#include "Deity.hpp"

class LikeDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    LikeDeityDecisionStrategyHandler(const std::string& deity_id);
    LikeDeityDecisionStrategyHandler(Deity* deity);

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;

    virtual std::unique_ptr<DeityDecisionStrategyHandler> clone() override;
    int get_piety_amount() const override;

  protected:
    std::string get_message_sid() const override;
    Deity* deity;

    static const int LIKE_DECISION_PIETY;
};
