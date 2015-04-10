#include "global_prototypes.hpp"
#include "MessageManagerFactory.hpp"
#include "ExperienceAction.hpp"
#include "ExperienceManager.hpp"
#include "RaceManager.hpp"
#include "ClassManager.hpp"
#include "TextMessages.hpp"

using std::string;

ExperienceAction::ExperienceAction()
{
}

ActionCostValue ExperienceAction::experience(CreaturePtr creature) const
{
  IMessageManager& manager = MessageManagerFactory::instance();
  
  if (creature != nullptr)
  {
    ExperienceManager em;
    RaceManager rm;
    ClassManager cm;

    int level = creature->get_level().get_current();
    uint experience = creature->get_experience_points();
    uint experience_needed = em.get_current_experience_needed_for_level(creature, static_cast<uint>(level+1));
    int next_level = level + 1;

    RacePtr race = rm.get_race(creature->get_race_id());
    string race_name = StringTable::get(race->get_race_name_sid());
    float race_multiplier = race->get_experience_multiplier();

    ClassPtr cls = cm.get_class(creature->get_class_id());
    string class_name = StringTable::get(cls->get_class_name_sid());
    float class_multiplier = cls->get_experience_multiplier();

    string exp_synopsis = TextMessages::get_experience_synopsis(level, experience, experience_needed, next_level, race_name, race_multiplier, class_name, class_multiplier);
    manager.add_new_message(exp_synopsis);
    manager.send();
  }
    
  CreaturePtr nullc;
  return get_action_cost_value(nullc);
}

ActionCostValue ExperienceAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}

