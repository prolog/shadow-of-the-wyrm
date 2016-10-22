#pragma once
#include "SkillProcessor.hpp"

class ScribingSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    bool check_for_components(CreaturePtr creature);
    bool check_for_spells(CreaturePtr creature);

    ItemPtr create_scroll(CreaturePtr creature, const std::string& spell_id);

    ActionCostValue get_default_skill_action_cost_value(CreaturePtr creature) const override;
};

