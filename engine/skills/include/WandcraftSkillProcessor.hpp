#pragma once
#include "SkillProcessor.hpp"
#include "WandCreationParameters.hpp"

class WandcraftSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool check_for_components(CreaturePtr creature);
    bool check_for_spells(CreaturePtr creature);

    ItemPtr create_wand(CreaturePtr creature, const WandCreationParameters& wcp);
    void remove_wand_components(CreaturePtr creature);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

