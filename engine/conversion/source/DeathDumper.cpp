#include <sstream>
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "DeathDumper.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"

using namespace std;

DeathDumper::DeathDumper(CreaturePtr new_creature, const bool new_narrative_mode, const uint new_max_cols)
: creature(new_creature), narrative_mode(new_narrative_mode), num_cols(new_max_cols)
{
}

string DeathDumper::str() const
{
  ostringstream ss;

  if (creature != nullptr)
  {
    string killed_by_source = creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_KILLED_BY_SOURCE);
    string killed_by_depth = creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_KILLED_BY_DEPTH);
    string killed_by_map = creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_KILLED_BY_MAP);

    if (!killed_by_source.empty() && !killed_by_depth.empty() && !killed_by_map.empty())
    {
      string death_details_sid = TextKeys::DEATH_DETAILS;

      if (narrative_mode)
      {
        death_details_sid = TextKeys::DEATH_DETAILS_NARRATIVE_MODE;
      }

      ss << String::centre(StringTable::get(death_details_sid), num_cols) << endl << endl;
      ss << TextMessages::get_killed_by_message(killed_by_source) << endl;
      ss << TextMessages::get_death_depth_location_message(killed_by_depth, killed_by_map);
    }
  }

  return ss.str();
}

