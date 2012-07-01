#include "SkillManager.hpp"

int SkillManager::get_skill_value(CreaturePtr creature, const SkillType skill_type)
{
  int skill_value = 0;
  
  if (creature)
  {
    Skills& skills = creature->get_skills();
    Skill skill    = skills.get_skill(skill_type);
    skill_value    = skill.get_value();
  }
  
  return skill_value;
}

void SkillManager::mark_skill(CreaturePtr creature, const SkillType skill_type)
{
}
