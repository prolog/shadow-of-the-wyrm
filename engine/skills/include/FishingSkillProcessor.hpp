#pragma once
#include "SkillProcessor.hpp"

class FishingSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool check_for_fishing_equipment(CreaturePtr creature);
    bool check_for_adjacent_water_tile(CreaturePtr creature, MapPtr map);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

