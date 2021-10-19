#pragma once
#include "DeityDecisionStrategyHandler.hpp"

class RestoreStatusDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    RestoreStatusDeityDecisionStrategyHandler(const std::string& new_deity_id);

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;

    std::string get_message_sid() const override;

    virtual std::unique_ptr<DeityDecisionStrategyHandler> clone() override;

  protected:
    void initialize_watched_statuses();
    void uncurse_equipment_with_negative_statuses(CreaturePtr creature);

    int get_piety_amount() const override;

    int piety_loss;
    std::vector<std::string> watched_statuses;
};
