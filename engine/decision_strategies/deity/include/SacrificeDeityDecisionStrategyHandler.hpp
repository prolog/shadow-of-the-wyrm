#pragma once
#include "DeityDecisionStrategyHandler.hpp"

class SacrificeDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    SacrificeDeityDecisionStrategyHandler(const std::string& new_deity_id);
    SacrificeDeityDecisionStrategyHandler(const std::string& new_deity_id, CreaturePtr sacrificing_creature, ItemPtr sacrificed_item);

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;

    virtual std::unique_ptr<DeityDecisionStrategyHandler> clone() override;

  protected:
    int get_piety_amount() const override;
    std::string get_message_sid() const override;

    CreaturePtr creature;
    ItemPtr sac_item;
};

