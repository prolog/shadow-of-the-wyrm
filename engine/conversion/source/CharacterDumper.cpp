#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "global_prototypes.hpp"
#include "ArtifactDumper.hpp"
#include "AttackDumper.hpp"
#include "CharacterDumper.hpp"
#include "ClassManager.hpp"
#include "ColourTextKeys.hpp"
#include "ConductsDumper.hpp"
#include "Conversion.hpp"
#include "CreatureTranslator.hpp"
#include "EquipmentDumper.hpp"
#include "Game.hpp"
#include "InventoryDumper.hpp"
#include "Metadata.hpp"
#include "MessageBufferDumper.hpp"
#include "MessageManagerFactory.hpp"
#include "MortuaryDumper.hpp"
#include "QuestDumper.hpp"
#include "ReligionManager.hpp"
#include "ResistancesDumper.hpp"
#include "SizeTextKeys.hpp"
#include "SkillsDumper.hpp"
#include "SpellsDumper.hpp"
#include "StatsDumper.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "VictoryDumper.hpp"

using namespace std;
using namespace boost::algorithm;

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
  
  Game& game = Game::instance();
  Metadata meta;
  string version = meta.get_game_version_synopsis();
  ss << String::centre(version, num_cols) << endl << endl;
  ss << String::centre(TextMessages::get_name_and_title(creature), num_cols) << endl;
  ss << get_synopsis() << endl << endl;
  ss << get_vital_statistics();
    
  StatsDumper stats_dumper(creature, num_cols);
  ss << stats_dumper.str() << endl << endl;

  ResistancesDumper res_dumper(creature, num_cols);
  ss << res_dumper.str() << endl << endl;

  VictoryDumper victory_dumper(creature, num_cols);
  string victory = victory_dumper.str();

  // Most characters won't be winners - don't add extra newlines to those 
  // that aren't.
  if (!victory.empty())
  {
    ss << victory << endl << endl;
  }

  ConductsDumper conducts_dumper(creature, num_cols);
  ss << conducts_dumper.str() << endl << endl;
    
  SkillsDumper skills_dumper(creature, num_cols);
  ss << skills_dumper.str() << endl << endl;

  SpellsDumper spells_dumper(creature, num_cols);
  ss << spells_dumper.str() << endl << endl;

  QuestDumper quest_dumper(creature, num_cols);
  ss << quest_dumper.str() << endl << endl;
    
  EquipmentDumper equipment_dumper(creature, num_cols);
  ss << equipment_dumper.str() << endl << endl;
    
  InventoryDumper inventory_dumper(creature, num_cols);
  ss << inventory_dumper.str() << endl << endl;

  ArtifactDumper artifact_dumper(game.get_items_ref(), game.get_item_generation_values_ref(), num_cols);
  ss << artifact_dumper.str() << endl << endl;

  AttackDumper attack_dumper(creature, num_cols);
  ss << attack_dumper.str() << endl << endl;

  MessageBufferDumper mbd(MM::instance(), num_cols);
  ss << mbd.str() << endl << endl;

  MortuaryDumper mortuary_dumper(creature, num_cols);
  ss << mortuary_dumper.str() << endl << endl;

  ss << StringTable::get(TextKeys::TURNS) << ": " << creature->get_turns() << endl << endl;

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
      
    string character_synopsis = "L" + std::to_string(creature->get_level().get_current()) + " " + race_name + " " + class_name;
    ss << String::centre(character_synopsis, num_cols);
  }

  return ss.str();
}

// Get the creature's vital statistics: age, sex, size, hair, eyes,
// and things like str, dex, evade, etc.
string CharacterDumper::get_vital_statistics() const
{
  ostringstream ss;
  vector<string> vl(10);
  
  // First, pad the lines:
  for (string& s : vl)
  {
    s = String::add_trailing_spaces(s, num_cols);
  }
  
  // First line
  string age  = StringTable::get(TextKeys::AGE) + ": " + std::to_string(creature->get_age().get_current());
  string sex  = StringTable::get(TextKeys::SEX) + ": " + TextMessages::get_sex(creature->get_sex());
  string size = StringTable::get(SizeTextKeys::SIZE) + ": " + StringTable::get(SizeTextKeys::get_size_sid_from_creature_size(creature->get_size()));
  
  vl.at(0).replace(0, age.size(), age);
  vl.at(0).replace(30, sex.size(), sex);
  vl.at(0).replace(60, size.size(), size);

  // Second line
  ReligionManager rm;
  string deity_id = creature->get_religion().get_active_deity_id();
  string deity = StringTable::get(TextKeys::DEITY) + ": " + StringTable::get(rm.get_deity_name_sid(deity_id));
  string hair_colour = StringTable::get(TextKeys::HAIR_COLOUR) + ": " + StringTable::get(ColourTextKeys::get_colour_sid_from_hair_colour(creature->get_hair_colour()));
  string eye_colour  = StringTable::get(TextKeys::EYE_COLOUR)  + ": " + StringTable::get(ColourTextKeys::get_colour_sid_from_eye_colour(creature->get_eye_colour()));
  
  vl.at(1).replace(0, deity.size(), deity);
  vl.at(1).replace(30, hair_colour.size(), hair_colour);
  vl.at(1).replace(60, eye_colour.size(), eye_colour);

  // Third Line
  Alignment a;
  string alignment = StringTable::get(TextKeys::ALIGNMENT) + ": " + StringTable::get(a.get_alignment_sid(creature->get_alignment().get_alignment_range()));

  vl.at(2).replace(0, alignment.size(), alignment);

  for (string& s : vl)
  {
    trim_right(s);
    if (!s.empty())
    {
      ss << s << endl;
    }
  }

  ss << endl;

  return ss.str();
}

