#pragma once
#include <map>
#include "IActionManager.hpp"
#include "SkillTypes.hpp"

class SkillsAction : public IActionManager
{
  public:
    SkillsAction();
    bool operator==(const SkillsAction& ssa) const;

    ActionCostValue show_skills(CreaturePtr creature, const SkillsSelectionType sst);
    ActionCostValue show_general_skills(CreaturePtr creature);
    ActionCostValue show_melee_weapon_skills(CreaturePtr creature);
    ActionCostValue show_ranged_weapon_skills(CreaturePtr creature);
    ActionCostValue show_magic_skills(CreaturePtr creature);

    ActionCostValue improve_skill(CreaturePtr creature, const SkillType st);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    SkillCategory category;
};
