#include <sstream>
#include "CodexDescriber.hpp"
#include "Conversion.hpp"
#include "ItemProperties.hpp"
#include "RaceManager.hpp"
#include "ResistancesTranslator.hpp"
#include "ResistanceTextKeys.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

CodexDescriber::CodexDescriber(ItemPtr new_item)
: item(new_item)
{
}

string CodexDescriber::describe_for_synopsis_line() const
{
  string no_synop;
  return no_synop;
}

// Get an unabbreviated, unbraced resistances description.
string CodexDescriber::describe_resistances() const
{
  ostringstream ss;

  if (item != nullptr)
  {
    ResistancesDisplayOptions rdo(false, false);
    ResistancesTranslator rt;

    string res = rt.create_description(item->get_resistances(), rdo);

    if (!res.empty())
    {
      ss << StringTable::get(ResistanceTextKeys::RESISTANCE_RESISTANCES) << ": " << res;
    }
  }

  return ss.str();
}

string CodexDescriber::describe_speed_bonus() const
{
  string no_bonus;
  return no_bonus;
}

string CodexDescriber::describe_details() const
{
  ostringstream ss;

  if (item != nullptr)
  {
    string charm_races = item->get_additional_property(ItemProperties::ITEM_PROPERTIES_MUSIC_CHARM_RACES);
    RaceManager rm;

    if (!charm_races.empty())
    {
      vector<string> races = String::create_string_vector_from_csv_string(charm_races);
      size_t cr_sz = races.size();

      ss << StringTable::get(TextKeys::CHARM_RACES) << ": ";

      for (size_t i = 0; i < cr_sz; i++)
      {
        Race* race = rm.get_race(races[i]);
        
        if (race != nullptr)
        {
          ss << StringTable::get(race->get_race_name_sid());

          if (i < cr_sz - 1)
          {
            ss << ", ";
          }
        }
      }
    }

    // Any additional properties, semi-colon separated...
  }

  return ss.str();
}

