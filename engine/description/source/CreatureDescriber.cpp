#include <sstream>
#include "ActionTextKeys.hpp"
#include "CreatureDifficulty.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureProperties.hpp"
#include "CreatureTranslator.hpp"
#include "Conversion.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "OrderTextKeys.hpp"
#include "RaceManager.hpp"
#include "ClassManager.hpp"
#include "StringTable.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"

using namespace std;

CreatureDescriber::CreatureDescriber(CreaturePtr pov_creature, CreaturePtr new_creature)
: viewing_creature(pov_creature), creature(new_creature), short_description(false)
{
}

CreatureDescriber::CreatureDescriber(CreaturePtr pov_creature, CreaturePtr new_creature, bool s_desc)
: viewing_creature(pov_creature), creature(new_creature), short_description(s_desc)
{
}

string CreatureDescriber::describe() const
{
  ostringstream ss;

  if (creature)
  {
    string creature_desc;

    if (creature->get_is_player())
    {
      creature_desc = TextMessages::get_player_description(creature->get_name());
    }
    else
    {
      CurrentCreatureAbilities cca;

      if (!cca.can_see(viewing_creature))
      {
        creature_desc = StringTable::get(TextKeys::SOMETHING);
        return creature_desc;
      }
      else
      {
        creature_desc = StringTable::get(creature->get_description_sid());
      }
    }

    ss << creature_desc;
    
    string race_class_desc = describe_race_and_class();
    string status_description = describe_statuses();

    // If the "short description" option is set (basically used only for
    // combat), don't display the additional details
    if (!race_class_desc.empty() && !short_description)
    {
      ss << " " << race_class_desc;
    }
    if (!status_description.empty() && !short_description)
    {
      ss << " " << status_description;
    }

    bool pacified = String::to_bool(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_PACIFIED));

    if (pacified && !short_description)
    {
      ss << " " << StringTable::get(TextKeys::PACIFIED);
    }

    bool tamed = String::to_bool(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_TAMED));

    if (tamed && !short_description)
    {
      ss << " " << StringTable::get(TextKeys::TAMED);
    }
  }

  return ss.str();
}

string CreatureDescriber::describe_race_and_class() const
{
  ostringstream ss;

  if (creature != nullptr)
  {
    string race_id = creature->get_race_id();
    string class_id = creature->get_class_id();

    RaceManager rm;
    ClassManager cm;


    if (!race_id.empty() && !class_id.empty())
    {
      Race* race = rm.get_race(race_id);
      Class* cur_class = cm.get_class(class_id);

      if (race != nullptr && cur_class != nullptr)
      {
        ss << "(" << StringTable::get(race->get_race_name_sid()) << " " << StringTable::get(cur_class->get_class_name_sid()) << ")";
      }
    }
  }

  return ss.str();
}

string CreatureDescriber::describe_for_tile_selection() const
{
  ostringstream ss;
  string creature_description = describe();
  
  if (!creature_description.empty())
  {
    CreatureDifficulty cd;

    string difficulty = cd.get_difficulty_text_sid(viewing_creature, creature);
    string hp_ind = cd.get_health_indicator_sid(creature);
    bool hostile_to_viewer = creature->hostile_to(viewing_creature->get_id());

    ss << creature_description << " (";

    // If the creature is one of the viewing creature's followers,
    // add a flag, and give their current orders.
    if (viewing_creature->is_leader(creature) && !hostile_to_viewer)
    {
      ss << StringTable::get(TextKeys::FOLLOWER) << ", " << StringTable::get(OrderTextKeys::ORDER_ORDERS) << ": " << StringTable::get(creature->get_decision_strategy()->get_orders_description_sid()) << "; ";
    }

    // If the creature is friendly, be sure to note that!
    if (!creature->is(viewing_creature) && !hostile_to_viewer)
    {
      ss << StringTable::get(TextKeys::FRIENDLY) << "; ";
    }

    // The player should have a way of knowing if a creature has been
    // backstabbed, as these creatures will block automatic hiding.
    if (creature->has_additional_property(CreatureProperties::CREATURE_PROPERTIES_BACKSTABBED))
    {
      ss << StringTable::get(TextKeys::BACKSTABBED) << "; ";
    }

    ss << StringTable::get(difficulty) << "; " << StringTable::get(hp_ind) << "; " << StringTable::get(ActionTextKeys::ACTION_BESTIARY_DISPLAY_COMMAND_FOR_TILE_SELECTION) << ")";
  }

  return ss.str();
}

// Get a short synopsis of the form "Foo, L12 Wood Elf Wizard" for the save file.
// This gets displayed when viewing the list of saved games for a particular user.
string CreatureDescriber::describe_for_save_file() const
{
  ostringstream ss;
  RaceManager rm;
  ClassManager cm;

  if (creature)
  {
    ss << creature->get_name();
    ss << ", L" << creature->get_level().get_current() << " ";
    ss << StringTable::get(rm.get_race(creature->get_race_id())->get_race_name_sid()) << " ";
    ss << StringTable::get(cm.get_class(creature->get_class_id())->get_class_name_sid());
  }

  return ss.str();
}

// If the creature has any statuses, describe them within parentheses to use
// within the returned description.
string CreatureDescriber::describe_statuses() const
{
  ostringstream ss;

  if (creature && viewing_creature)
  {
    vector<pair<string, Colour>> statuses = CreatureTranslator::get_display_status_ailments(creature);

    if (!statuses.empty())
    {
      ss << "[ ";

      for (const auto& status_pair : statuses)
      {
        ss << status_pair.first << " ";
      }

      ss << "]";
    }
  }

  return ss.str();
}