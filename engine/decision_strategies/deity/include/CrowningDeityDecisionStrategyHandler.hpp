#pragma once
#include "DeityDecisionStrategyHandler.hpp"
#include "Deity.hpp"

class CrowningDeityDecisionStrategyHandler : public DeityDecisionStrategyHandler
{
  public:
    CrowningDeityDecisionStrategyHandler(const std::string& deity_id);

    bool decide(CreaturePtr creature) override;
    DeityDecisionImplications handle_decision(CreaturePtr creature, TilePtr tile) override;

    virtual std::unique_ptr<DeityDecisionStrategyHandler> clone() override;

  protected:
    void crown_champion(CreaturePtr creature);
    void fortify_champion(CreaturePtr creature);
    void add_crowning_gift(CreaturePtr creature, TilePtr tile);
    std::vector<std::string> select_crowning_gifts(CreaturePtr creature, Deity* deity);

    int get_piety_amount() const override;
    std::string get_message_sid() const override;
    bool get_add_message_with_pause() const override;
    bool get_reload_map_music() const override;
    std::map<AlignmentRange, std::string> alignment_crowning_events;
};
