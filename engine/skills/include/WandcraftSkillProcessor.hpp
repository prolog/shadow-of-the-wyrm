#pragma once
#include "SkillProcessor.hpp"
#include "WaterTypes.hpp"

class WandcraftSkillProcessor : public SkillProcessor
{
  public:
    WandcraftSkillProcessor();

    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool check_for_components(CreaturePtr creature);
    bool check_for_spells(CreaturePtr creature);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

