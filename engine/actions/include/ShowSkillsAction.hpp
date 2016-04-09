#pragma once
#include <map>
#include "IActionManager.hpp"

class ShowSkillsAction : public IActionManager
{
  public:
    ShowSkillsAction();
    bool operator==(const ShowSkillsAction& ssa) const;

    ActionCostValue show_skills(CreaturePtr creature);
    ActionCostValue show_general_skills(CreaturePtr creature);
    ActionCostValue show_melee_weapon_skills(CreaturePtr creature);
    ActionCostValue show_ranged_weapon_skills(CreaturePtr creature);
    ActionCostValue show_magic_skills(CreaturePtr creature);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    SkillCategory category;
};
