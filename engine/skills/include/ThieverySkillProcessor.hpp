#pragma once
#include "SkillProcessor.hpp"

class ThieverySkillProcessor : public SkillProcessor
{
  public:
    ThieverySkillProcessor();

    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool check_for_adjacent_creatures(CreaturePtr creature, MapPtr map);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

