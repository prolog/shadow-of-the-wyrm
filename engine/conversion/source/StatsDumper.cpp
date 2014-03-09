#include <sstream>
#include "Conversion.hpp"
#include "StatsDumper.hpp"
#include "TextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

StatsDumper::StatsDumper(CreaturePtr new_creature, const uint new_max_cols)
: creature(new_creature), num_cols(new_max_cols)
{
}

string StatsDumper::str() const
{
  return get_stats();
}

// Get the creature's stats as a string.
// First column: str, dex, agi, hea, int, will, cha.
// Second column: HP, AP, val, spi, spd, eva, soa
string StatsDumper::get_stats() const
{
  ostringstream ss;

  // First column
  string strength      = StringTable::get(TextKeys::STRENGTH)      + ": " + Integer::to_string(creature->get_strength().get_current());
  string dexterity     = StringTable::get(TextKeys::DEXTERITY)     + ": " + Integer::to_string(creature->get_dexterity().get_current());
  string agility       = StringTable::get(TextKeys::AGILITY)       + ": " + Integer::to_string(creature->get_agility().get_current());
  string health        = StringTable::get(TextKeys::HEALTH)        + ": " + Integer::to_string(creature->get_health().get_current());
  string intelligence  = StringTable::get(TextKeys::INTELLIGENCE)  + ": " + Integer::to_string(creature->get_intelligence().get_current());
  string willpower     = StringTable::get(TextKeys::WILLPOWER)     + ": " + Integer::to_string(creature->get_willpower().get_current());
  string charisma      = StringTable::get(TextKeys::CHARISMA)      + ": " + Integer::to_string(creature->get_charisma().get_current());
  
  // Second column
  Statistic hp         = creature->get_hit_points();
  Statistic ap         = creature->get_arcana_points(); 
  string hit_points    = StringTable::get(TextKeys::HIT_POINTS)    + ": " + Integer::to_string(hp.get_current()) + "/" + Integer::to_string(hp.get_base());
  string arcana_points = StringTable::get(TextKeys::ARCANA_POINTS) + ": " + Integer::to_string(ap.get_current()) + "/" + Integer::to_string(ap.get_base());
  string speed         = StringTable::get(TextKeys::SPEED)         + ": " + Integer::to_string(creature->get_speed().get_current());
  string evade         = StringTable::get(TextKeys::EVADE)         + ": " + Integer::to_string(creature->get_evade().get_current());
  string soak          = StringTable::get(TextKeys::SOAK)          + ": " + Integer::to_string(creature->get_soak().get_current());

  string current_line;
  current_line = String::add_trailing_spaces(current_line, num_cols);
  current_line.replace(0, strength.size(), strength);
  current_line.replace(30, hit_points.size(), hit_points);
  ss << current_line << endl;
  String::reset_and_pad(current_line, num_cols);
  
  current_line.replace(0, dexterity.size(), dexterity);
  current_line.replace(30, arcana_points.size(), arcana_points);
  ss << current_line << endl;
  String::reset_and_pad(current_line, num_cols);
  
  current_line.replace(0, agility.size(), agility);
  current_line.replace(30, speed.size(), speed);
  ss << current_line << endl;
  String::reset_and_pad(current_line, num_cols);
  
  current_line.replace(0, health.size(), health);
  current_line.replace(30, evade.size(), evade);
  ss << current_line << endl;
  String::reset_and_pad(current_line, num_cols);
  
  current_line.replace(0, intelligence.size(), intelligence);
  current_line.replace(30, soak.size(), soak);
  ss << current_line << endl;
  String::reset_and_pad(current_line, num_cols);
  
  current_line.replace(0, willpower.size(), willpower);
  ss << current_line << endl;
  String::reset_and_pad(current_line, num_cols);
  
  current_line.replace(0, charisma.size(), charisma);
  ss << current_line << endl;
  
  return ss.str();
}
