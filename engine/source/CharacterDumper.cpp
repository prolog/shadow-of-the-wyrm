#include <sstream>
#include "global_prototypes.hpp"
#include "CharacterDumper.hpp"
#include "Conversion.hpp"
#include "Game.hpp"

using namespace std;

CharacterDumper::CharacterDumper(CreaturePtr new_creature, const int new_num_cols)
: creature(new_creature), num_cols(new_num_cols)
{
}

CharacterDumper::~CharacterDumper()
{
}

string CharacterDumper::str() const
{
  ostringstream ss;
  
  Game* game = Game::instance();
  
  if (game)
  {
    string version = get_game_version_synopsis();
    ss << centre(version) << endl << endl;
    ss << centre(creature->get_name()) << endl;
    ss << get_synopsis() << endl << endl;
    ss << get_vital_statistics() << endl << endl;
    ss << get_stats() << endl << endl;
  }
    
  return ss.str();
}

// Helper functions
string CharacterDumper::get_synopsis() const
{
  ostringstream ss;
  Game* game = Game::instance();
  
  if (game)
  {
    RaceMap races = game->get_races_ref();
    ClassMap classes = game->get_classes_ref();
    string race_id = creature->get_race_id();
    string class_id = creature->get_class_id();
    
    RacePtr race = races[race_id];
    ClassPtr char_class = classes[class_id];
    
    if (race && char_class)
    {
      string race_name = StringTable::get(race->get_race_name_sid());
      string class_name = StringTable::get(char_class->get_class_name_sid());
      
      string character_synopsis = "L" + Integer::to_string(creature->get_level().get_current()) + " " + race_name + " " + class_name;
      ss << centre(character_synopsis);
    }
  }
  
  return ss.str();
}

// Get the creature's vital statistics: age, sex, size, hair, eyes
string CharacterDumper::get_vital_statistics() const
{
  ostringstream ss;
  string vitals_line_1, vitals_line_2;
  
  // First, pad the lines:
  vitals_line_1 = String::add_trailing_spaces(vitals_line_1, num_cols);
  vitals_line_2 = String::add_trailing_spaces(vitals_line_2, num_cols);
  
  // First line
  string age  = StringTable::get(TextKeys::AGE) + ": " + Integer::to_string(creature->get_age().get_current());
  string sex  = StringTable::get(TextKeys::SEX) + ": " + TextMessages::get_sex(creature->get_sex());
  string size = StringTable::get(SizeTextKeys::SIZE) + ": " + StringTable::get(SizeTextKeys::get_size_sid_from_creature_size(creature->get_size()));
  
  vitals_line_1.replace(0, age.size(), age);
  vitals_line_1.replace(30, sex.size(), sex);
  vitals_line_1.replace(60, size.size(), size);

  // Second line
  string hair_colour = StringTable::get(TextKeys::HAIR_COLOUR) + ": " + StringTable::get(ColourTextKeys::get_colour_sid_from_hair_colour(creature->get_hair_colour()));
  string eye_colour  = StringTable::get(TextKeys::EYE_COLOUR)  + ": " + StringTable::get(ColourTextKeys::get_colour_sid_from_eye_colour(creature->get_eye_colour()));
  
  vitals_line_2.replace(0, hair_colour.size(), hair_colour);
  vitals_line_2.replace(30, eye_colour.size(), eye_colour);
  
  ss << vitals_line_1 << endl << vitals_line_2;
  return ss.str();
}

// Get the creature's stats as a string.
// First column: str, dex, agi, hea, int, will, cha.
// Second column: HP, AP, val, spi, spd, eva, soa
string CharacterDumper::get_stats() const
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
  string valour        = StringTable::get(TextKeys::VALOUR)        + ": " + Integer::to_string(creature->get_valour().get_current());
  string spirit        = StringTable::get(TextKeys::SPIRIT)        + ": " + Integer::to_string(creature->get_spirit().get_current());
  string speed         = StringTable::get(TextKeys::SPEED)         + ": " + Integer::to_string(creature->get_speed().get_current());
  string evade         = StringTable::get(TextKeys::EVADE)         + ": " + Integer::to_string(creature->get_evade().get_current());
  string soak          = StringTable::get(TextKeys::SOAK)          + ": " + Integer::to_string(creature->get_soak().get_current());

  string current_line;
  current_line = String::add_trailing_spaces(current_line, num_cols);
  current_line.replace(0, strength.size(), strength);
  current_line.replace(30, hit_points.size(), hit_points);
  ss << current_line << endl;
  reset_and_pad(current_line);
  
  current_line.replace(0, dexterity.size(), dexterity);
  current_line.replace(30, arcana_points.size(), arcana_points);
  ss << current_line << endl;
  reset_and_pad(current_line);
  
  current_line.replace(0, agility.size(), agility);
  current_line.replace(30, valour.size(), valour);
  ss << current_line << endl;
  reset_and_pad(current_line);
  
  current_line.replace(0, health.size(), health);
  current_line.replace(30, spirit.size(), spirit);
  ss << current_line << endl;
  reset_and_pad(current_line);
  
  current_line.replace(0, intelligence.size(), intelligence);
  current_line.replace(30, speed.size(), speed);
  ss << current_line << endl;
  reset_and_pad(current_line);
  
  current_line.replace(0, willpower.size(), willpower);
  current_line.replace(30, evade.size(), evade);
  ss << current_line << endl;
  reset_and_pad(current_line);
  
  current_line.replace(0, charisma.size(), charisma);
  current_line.replace(30, soak.size(), soak);
  ss << current_line << endl;
  
  return ss.str();
}

void CharacterDumper::reset_and_pad(string& s) const
{
  s = "";
  s = String::add_trailing_spaces(s, num_cols);
}

// Formatting methods

// Centre the string on the number of columns stored on the object instance
string CharacterDumper::centre(const std::string& justify_str) const
{
  ostringstream ss;
  
  for (uint i = 0; i < (num_cols/2) - (justify_str.size()/2); i++)
  {
    ss << " ";
  }
  
  ss << justify_str;
  
  return ss.str();
}

// Right-justify the string using the number of columns stored on the object instance to add left padding.
string CharacterDumper::right(const std::string& justify_str) const
{
  ostringstream ss;
  
  for (uint i = 0; i < (num_cols - justify_str.size()); i++)
  {
    ss << " "; 
  }
  
  ss << justify_str;
  
  return ss.str();
}
