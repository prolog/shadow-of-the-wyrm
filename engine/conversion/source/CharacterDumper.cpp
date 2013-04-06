#include <sstream>
#include "global_prototypes.hpp"
#include "CharacterDumper.hpp"
#include "Conversion.hpp"
#include "EquipmentDumper.hpp"
#include "Game.hpp"
#include "InventoryDumper.hpp"
#include "Metadata.hpp"
#include "ReligionManager.hpp"
#include "SkillsDumper.hpp"
#include "StatsDumper.hpp"
#include "TextMessages.hpp"

using namespace std;

CharacterDumper::CharacterDumper(CreaturePtr new_creature, const uint new_num_cols)
: creature(new_creature), num_cols(new_num_cols)
{
}

CharacterDumper::~CharacterDumper()
{
}

string CharacterDumper::str() const
{
  ostringstream ss;
  
  Metadata meta;
  string version = meta.get_game_version_synopsis();
  ss << String::centre(version, num_cols) << endl << endl;
  ss << String::centre(creature->get_name(), num_cols) << endl;
  ss << get_synopsis() << endl << endl;
  ss << get_vital_statistics() << endl << endl;
    
  StatsDumper stats_dumper(creature, num_cols);
  ss << stats_dumper.str() << endl << endl;
    
  SkillsDumper skills_dumper(creature, num_cols);
  ss << skills_dumper.str() << endl << endl;
    
  EquipmentDumper equipment_dumper(creature, num_cols);
  ss << equipment_dumper.str() << endl << endl;
    
  InventoryDumper inventory_dumper(creature, num_cols);
  ss << inventory_dumper.str() << endl << endl;
    
  return ss.str();
}

// Helper functions
string CharacterDumper::get_synopsis() const
{
  ostringstream ss;
  Game& game = Game::instance();
  
  RaceMap races = game.get_races_ref();
  ClassMap classes = game.get_classes_ref();
  string race_id = creature->get_race_id();
  string class_id = creature->get_class_id();
    
  RacePtr race = races[race_id];
  ClassPtr char_class = classes[class_id];
    
  if (race && char_class)
  {
    string race_name = StringTable::get(race->get_race_name_sid());
    string class_name = StringTable::get(char_class->get_class_name_sid());
      
    string character_synopsis = "L" + Integer::to_string(creature->get_level().get_current()) + " " + race_name + " " + class_name;
    ss << String::centre(character_synopsis, num_cols);
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
  // JCD FIXME: Ugly, refactor
  ReligionManager rm;
  string deity_id = creature->get_religion().get_active_deity_id();
  string deity = StringTable::get(TextKeys::DEITY) + ": " + StringTable::get(rm.get_deity_name_sid(deity_id));
  string hair_colour = StringTable::get(TextKeys::HAIR_COLOUR) + ": " + StringTable::get(ColourTextKeys::get_colour_sid_from_hair_colour(creature->get_hair_colour()));
  string eye_colour  = StringTable::get(TextKeys::EYE_COLOUR)  + ": " + StringTable::get(ColourTextKeys::get_colour_sid_from_eye_colour(creature->get_eye_colour()));
  
  vitals_line_2.replace(0, deity.size(), deity);
  vitals_line_2.replace(30, hair_colour.size(), hair_colour);
  vitals_line_2.replace(60, eye_colour.size(), eye_colour);
    
  ss << vitals_line_1 << endl << vitals_line_2 << endl;
    
  return ss.str();
}

