#pragma once
#include "DeityDecisionStrategyHandler.hpp"
#include "Deity.hpp"

class CrowningDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    CrowningDeityDecisionStrategyHandler(const std::string& deity_id);

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;

  protected:
    void crown_champion(CreaturePtr creature);
    void fortify_champion(CreaturePtr creature);
    void add_crowning_gift(CreaturePtr creature, TilePtr tile);
    std::vector<std::string> select_crowning_gifts(CreaturePtr creature, DeityPtr deity);

    int get_piety_loss() const override;
    std::string get_message_sid() const override;
};
