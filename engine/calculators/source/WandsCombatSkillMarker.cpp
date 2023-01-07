#include "WandsCombatSkillMarker.hpp"

using namespace std;

// Ranged combat trains archery and the appropriate weapon skill.
vector<SkillType> WandsCombatSkillMarker::get_marked_skills(CreaturePtr creature) const
{
  return {SkillType::SKILL_GENERAL_WANDCRAFT};
}
