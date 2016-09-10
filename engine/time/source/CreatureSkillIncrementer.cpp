#include "CreatureSkillIncrementer.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
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
  Marks& marks = skill->get_marks_ref();
  int skill_value = skill->get_value();

  // Skills are automatically learned when the number of marks is greater than
  // the threshold.  When the marks are less than that, there is a percent
  // chance applied.
  while ((marks.get_value() > skill_threshold) || (RNG::percent_chance(marks.get_value())))
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
    if (skill_threshold == 0)
    {
      marks.set_value(0);
    }
    else
    {
      int skill_marks = marks.get_value();
      skill_marks -= std::max(skill_threshold, 1);
      marks.set_value(skill_marks);
    }

    marks.set_value(std::max(marks.get_value(), 0));
  }

  return trained_skill;
}
