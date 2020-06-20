#pragma once
#include "DeityDecisionStrategyHandler.hpp"

class AltarDropDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    AltarDropDeityDecisionStrategyHandler(const std::string& new_deity_id);
    AltarDropDeityDecisionStrategyHandler(const std::string& new_deity_id, CreaturePtr dropping_creature, FeaturePtr feature, ItemPtr dropped_item);

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;

    virtual std::unique_ptr<DeityDecisionStrategyHandler> clone() override;

protected:
    int get_piety_loss() const override;
    std::string get_message_sid() const override;

    CreaturePtr creature;
    FeaturePtr altar;
    ItemPtr drop_item;

    static const int PIETY_LOSS_COALIGN;
    static const int PIETY_LOSS_CROSSALIGN;
};

