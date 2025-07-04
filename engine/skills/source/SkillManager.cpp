#include "RNG.hpp"
#include "SkillManager.hpp"

const int SkillManager::PERCENT_CHANCE_TO_MARK_SKILL_ON_FAILURE = 20;

bool SkillManager::check_skill(CreaturePtr creature, const SkillType skill_type, const int num_checks)
{
  int skill_value = get_skill_value(creature, skill_type);  
  bool skill_check = false;
  
  for (int i = 0; i < num_checks; i++)
  {
    skill_check = RNG::percent_chance(skill_value);

    if (skill_check)
    {
      break;
    }
  }

  mark_skill(creature, skill_type, skill_check);
  
  return skill_check;
}

int SkillManager::get_skill_value(CreaturePtr creature, const SkillType skill_type)
{
  int skill_value = 0;
  
  if (creature)
  {
    Skills& skills = creature->get_skills();
    Skill* skill   = skills.get_skill(skill_type);
    skill_value    = skill->get_value();
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
    Skill* skill   = skills.get_skill(skill_type);
 
    if (skill != nullptr)
    {
      int val = skill->get_value();

      // Don't mark skills that can't actually be improved.
      if (val > 0 || skill->can_train_from_unlearned())
      {
        if (val < Skills::MAX_SKILL_VALUE)
        {
          skill->get_marks_ref().incr();
        }
      }
    }
  }
}

void SkillManager::mark_skill_with_probability(const int pct_chance, CreaturePtr creature, const SkillType skill_type, const bool skill_check_result)
{
  if (RNG::percent_chance(pct_chance))
  {
    mark_skill(creature, skill_type, skill_check_result);
  }
}