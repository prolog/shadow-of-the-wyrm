#include <sstream>
#include "ActionTextKeys.hpp"
#include "CreatureDifficulty.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureTranslator.hpp"
#include "Conversion.hpp"
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
      string creature_name = creature->get_name();
      creature_desc = StringTable::get(creature->get_description_sid());

      if (!creature_name.empty())
      {
        creature_desc = creature_name + ", " + creature_desc;
      }
    }

    ss << creature_desc;
    
    string status_description = describe_statuses();

    // If the "short description" option is set (basically used only for
    // combat), don't display the additional status information.
    if (!status_description.empty() && !short_description)
    {
      ss << " " << status_description;
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
    ss << creature_description << " (" << StringTable::get(difficulty) << "; " << StringTable::get(ActionTextKeys::ACTION_BESTIARY_DISPLAY_COMMAND_FOR_TILE_SELECTION) << ")";
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
    bool hostile_to_viewer = creature->hostile_to(viewing_creature->get_id());

    if (!statuses.empty() || (!creature->is(viewing_creature) && !hostile_to_viewer))
    {
      ss << "[ ";

      for (const auto& status_pair : statuses)
      {
        ss << status_pair.first << " ";
      }

      // If the creature is friendly, be sure to note that!
      if (!creature->is(viewing_creature) && !hostile_to_viewer)
      {
        ss << StringTable::get(TextKeys::FRIENDLY) << " ";
      }

      ss << "]";
    }
  }

  return ss.str();
}