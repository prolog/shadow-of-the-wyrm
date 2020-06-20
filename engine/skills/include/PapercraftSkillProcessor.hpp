#pragma once
#include "SkillProcessor.hpp"
#include "MessageManagerFactory.hpp"

class PapercraftSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
    virtual SkillProcessorPtr clone() override;

  protected:
    bool check_for_equipment(CreaturePtr creature, IMessageManager& manager);
    bool check_pulp_weight(ItemPtr blank_scroll, ItemPtr pulp, IMessageManager& manager);
    ItemPtr select_pulp_pile(CreaturePtr creature);
    void add_blank_scrolls_to_creature_tile(CreaturePtr creature, MapPtr map, const Weight& blank_scroll_weight, const Weight& pulp_weight);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

