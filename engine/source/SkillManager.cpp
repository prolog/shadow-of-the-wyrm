#include "RNG.hpp"
#include "SkillManager.hpp"

bool SkillManager::check_skill(CreaturePtr creature, const SkillType skill_type)
{
  int skill_value = get_skill_value(creature, skill_type);  
  bool skill_check = RNG::percent_chance(skill_value);
  
  mark_skill(creature, skill_type);
  
  return skill_check;
}

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
