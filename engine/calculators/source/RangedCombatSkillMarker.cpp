#include "RangedCombatSkillMarker.hpp"
#include "SkillTypes.hpp"
#include "WeaponManager.hpp"

using namespace std;

// Ranged combat trains archery and the appropriate weapon skill.
vector<SkillType> RangedCombatSkillMarker::get_marked_skills(CreaturePtr creature) const
{
  vector<SkillType> marked_skills{SkillType::SKILL_GENERAL_ARCHERY};

  WeaponManager wm;
  SkillType weapon_skill = wm.get_skill_type(creature, AttackType::ATTACK_TYPE_RANGED);

  marked_skills.push_back(weapon_skill);

  return marked_skills;
}
