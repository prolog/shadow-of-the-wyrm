#include "RNG.hpp"
#include "SkillManager.hpp"

const int SkillManager::PERCENT_CHANCE_TO_MARK_SKILL_ON_FAILURE = 20;

bool SkillManager::check_skill(CreaturePtr creature, const SkillType skill_type)
{
  int skill_value = get_skill_value(creature, skill_type);  
  bool skill_check = RNG::percent_chance(skill_value);
  
  mark_skill(creature, skill_type, skill_check);
  
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

// Successful usage of a skill will mark that skill.
// An unsuccessful usage will mark that skill with some probability.
void SkillManager::mark_skill(CreaturePtr creature, const SkillType skill_type, const bool skill_check_result)
{
  if (skill_check_result || RNG::percent_chance(SkillManager::PERCENT_CHANCE_TO_MARK_SKILL_ON_FAILURE))
  {
    Skills& skills = creature->get_skills();
    Skill skill    = skills.get_skill(skill_type);
    
    skill.increment_marks();
    
    skills.set_skill(skill_type, skill);
  }
}
