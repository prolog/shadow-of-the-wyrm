#pragma once
#include "SkillProcessor.hpp"

class PapercraftSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool check_for_equipment(CreaturePtr creature);
    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

