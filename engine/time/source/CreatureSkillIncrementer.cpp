#include "CreatureSkillIncrementer.hpp"

using std::map;

CreatureSkillIncrementer::CreatureSkillIncrementer(const uint new_minutes_interval)
: ICreatureRegeneration(), 
  minutes_interval(new_minutes_interval)
{
}

void CreatureSkillIncrementer::tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature)
  {
    if (total_minutes_elapsed % minutes_interval == 0)
    {
      Skills& skills = creature->get_skills();
      map<SkillType, Skill>& raw_skills = skills.get_raw_skills();
      
      // If the skill has been marked enough, increment the value of the skill, display a message
      // (when the creature is the player), and then reset the number of marks back to zero.
      for (map<SkillType, Skill>::iterator sk_it = raw_skills.begin(); sk_it != raw_skills.end(); sk_it++)
      {
        Skill& skill = sk_it->second;
        int skill_threshold = skill.get_threshold();
        int skill_value = skill.get_value();
        
        if (skill.get_marks() > skill_threshold)
        {
          // Update the value, which also updates the threshold.
          skill.set_value(skill_value + 1);
          
          if (creature->get_is_player())
          {
            // JCD FIXME
          }
          
          skill.set_marks(0);
        }
      }
    }
  }
};
