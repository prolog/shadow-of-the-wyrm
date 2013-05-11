#include <sstream>
#include "ActionTextKeys.hpp"
#include "CreatureDescriber.hpp"
#include "Conversion.hpp"
#include "RaceManager.hpp"
#include "ClassManager.hpp"
#include "StringTable.hpp"

using namespace std;

CreatureDescriber::CreatureDescriber(CreaturePtr new_creature)
: creature(new_creature)
{
}

string CreatureDescriber::describe() const
{
  string creature_description;

  if (creature)
  {
    creature_description = StringTable::get(creature->get_description_sid());
  }

  return creature_description;
}

string CreatureDescriber::describe_for_tile_selection() const
{
  string creature_description = describe();

  if (!creature_description.empty())
  {
    creature_description = creature_description + " (" + StringTable::get(ActionTextKeys::ACTION_BESTIARY_DISPLAY_COMMAND_FOR_TILE_SELECTION) + ")";
  }

  return creature_description;
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