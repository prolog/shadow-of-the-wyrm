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
vector<SkillType> MeleeCombatSkillMarker::get_marked_skills(CreaturePtr creature) const
{
  vector<SkillType> marked_skills{SKILL_GENERAL_COMBAT};
  WeaponManager wm;

  WeaponStyle ws = wm.get_style(attack_type);  
  SkillType weapon_skill = wm.get_skill_type(creature, attack_type);

  marked_skills.push_back(weapon_skill);

  return marked_skills;
}

