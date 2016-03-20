#include "MeleeCombatSkillMarker.hpp"
#include "WeaponManager.hpp"
#include "SkillTypes.hpp"

using namespace std;

MeleeCombatSkillMarker::MeleeCombatSkillMarker(const AttackType at)
: attack_type(at)
{
}

// For melee combat, add the Combat skill, as well as the appropriate
// weapon skill.
//
// If this is a secondary attack, and the creature already has skill
// in Dual Wield, mark that also.
vector<SkillType> MeleeCombatSkillMarker::get_marked_skills(CreaturePtr creature) const
{
  vector<SkillType> marked_skills{SkillType::SKILL_GENERAL_COMBAT};
  WeaponManager wm;

  WeaponStyle ws = wm.get_style(attack_type);  
  SkillType weapon_skill = wm.get_skill_type(creature, attack_type);

  marked_skills.push_back(weapon_skill);

  if (attack_type == AttackType::ATTACK_TYPE_MELEE_SECONDARY)
  {
    if (creature != nullptr)
    {
      SkillType dual_wield = SkillType::SKILL_GENERAL_DUAL_WIELD;

      if (creature->get_skills().get_value(dual_wield) > 0)
      {
        marked_skills.push_back(dual_wield);
      }
    }
  }

  return marked_skills;
}

