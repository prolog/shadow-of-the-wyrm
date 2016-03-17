#include "CreatureSkillIncrementer.hpp"
#include "MessageManagerFactory.hpp"
#include "Serialize.hpp"

using namespace std;

CreatureSkillIncrementer::CreatureSkillIncrementer()
: ICreatureRegeneration(),
minutes_interval(0)
{
}

CreatureSkillIncrementer::CreatureSkillIncrementer(const uint new_minutes_interval)
: ICreatureRegeneration(), 
  minutes_interval(new_minutes_interval)
{
}

void CreatureSkillIncrementer::tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature)
  {
    if (total_minutes_elapsed % minutes_interval == 0)
    {
      Skills& skills = creature->get_skills();
      map<SkillType, SkillPtr>& raw_skills = skills.get_raw_skills_ref();
      
      IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

      // If the skill has been marked enough, increment the value of the skill, display a message
      // (when the creature is the player), and then reset the number of marks back to zero.
      for (map<SkillType, SkillPtr>::iterator sk_it = raw_skills.begin(); sk_it != raw_skills.end(); sk_it++)
      {
        SkillPtr skill = sk_it->second;
        bool added_msg = update_skill_if_necessary(creature, skill, manager);

        if (added_msg)
        {
          manager.send();
        }
      }
    }
  }
}

bool CreatureSkillIncrementer::update_skill_if_necessary(CreaturePtr creature, SkillPtr skill, IMessageManager& manager)
{
  bool trained_skill = false;

  int skill_threshold = skill->get_threshold();
  int skill_marks = skill->get_marks();
  int skill_value = skill->get_value();

  // Skills aren't automatically learned when at 0 and enough success/failure occurs.  This is meant to be a model
  // similar to ADOM and not DCSS, and is absolutely intentional.  Classes matter, and the initial skill set is
  // important. 
  while (skill_marks > skill_threshold)
  {
    if ((skill_value == 0 && (skill->can_train_from_unlearned())) || (skill_value > 0))
    {
      skill_value = skill->get_value();

      // Update the value, which also updates the threshold.
      skill->set_value(skill_value + 1);

      if (creature->get_is_player())
      {
        string skill_increase_message = StringTable::get(skill->get_skill_increment_message_sid());
        manager.add_new_message(skill_increase_message);
        trained_skill = true;
      }

      skill_threshold = skill->get_threshold();
    }

    // Must decrement by at least 1 (i.e., when the skill is initially
    // at 0 points).
    skill_marks -= std::max(skill_threshold, 1);
  }

  skill->set_marks(skill_marks);
  return trained_skill;
}