#include <iomanip>
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
#include "CreatureProperties.hpp"
#include "CreatureTranslator.hpp"
#include "DateTextKeys.hpp"
#include "DeathDumper.hpp"
#include "Environment.hpp"
#include "EquipmentDumper.hpp"
#include "FormattingConstants.hpp"
#include "Game.hpp"
#include "InventoryDumper.hpp"
#include "MembershipsDumper.hpp"
#include "Metadata.hpp"
#include "MessageBufferDumper.hpp"
#include "MessageManagerFactory.hpp"
#include "ModifiersDumper.hpp"
#include "MortuaryDumper.hpp"
#include "PartyTextKeys.hpp"
#include "QuestDumper.hpp"
#include "RaceManager.hpp"
#include "ReligionManager.hpp"
#include "ResistancesDumper.hpp"
#include "Setting.hpp"
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
  
  string name_title_user = TextMessages::get_name_and_title(creature);
  string user = Environment::get_user_name();

  if (!user.empty())
  {
    name_title_user += " (" + user + ")";
  }

  ss << String::centre(name_title_user, num_cols) << endl;
  ss << get_synopsis() << endl << endl;
  ss << get_vital_statistics();
    
  StatsDumper stats_dumper(creature, num_cols);
  ss << stats_dumper.str() << endl << endl;

  ResistancesDumper res_dumper(creature, num_cols);
  ss << res_dumper.str() << endl << endl;

  ModifiersDumper mod_dumper(creature, num_cols);
  ss << mod_dumper.str() << endl << endl;

  bool narrative_mode = Game::instance().get_settings_ref().get_setting_as_bool(Setting::NARRATIVE_MODE);
  DeathDumper death_dumper(creature, narrative_mode, num_cols);

  string death = death_dumper.str();

  if (!death.empty())
  {
    ss << death << endl << endl;
  }

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

  MembershipsDumper memberships_dumper(creature, num_cols);
  ss << memberships_dumper.str() << endl << endl;
    
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

  ss << get_carrying_capacity() << endl << endl;

  ArtifactDumper artifact_dumper(game.get_items_ref(), game.get_item_generation_values_ref(), num_cols);
  ss << artifact_dumper.str() << endl << endl;

  AttackDumper attack_dumper(creature, num_cols);
  ss << attack_dumper.str() << endl << endl;

  MessageBufferDumper mbd(MM::instance(), num_cols);
  ss << mbd.str() << endl << endl;

  MortuaryDumper mortuary_dumper(creature, num_cols);
  ss << mortuary_dumper.str() << endl << endl;

  ss << get_party() << endl << endl;

  ss << StringTable::get(TextKeys::MAXIMUM_DEPTH_REACHED) << ": " << creature->get_max_depth_reached().str(true) << endl << endl;

  string p_character_started = creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_CHARACTER_STARTED);
  string p_game_date = creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_GAME_DATE);

  if (!p_character_started.empty() && !p_game_date.empty())
  {
    Date st_date(p_character_started);
    Date cur_date(p_game_date);

    ss << StringTable::get(TextKeys::CHARACTER_STARTED) << ": " << DateTextKeys::get_date_time_message(st_date, false) << endl;
    ss << StringTable::get(TextKeys::GAME_DATE) << ": " << DateTextKeys::get_date_time_message(cur_date, false) << endl << endl;
  }

  string game_started = creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_GAME_STARTED);

  if (!game_started.empty())
  {
    struct std::tm t;
    std::time_t cur_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    localtime_s(&t, &cur_time);

    ss << StringTable::get(TextKeys::GAME_STARTED) << ": " << game_started << std::endl;
    ss << StringTable::get(TextKeys::CURRENT_DATE) << ": " << std::put_time(&t, FormattingConstants::DATETIME_DEFAULT_FORMAT.c_str()) << endl;
  }

  ss << StringTable::get(TextKeys::TURNS) << ": " << creature->get_turns() << endl << endl;

  double seconds = game.get_total_elapsed_game_time(std::chrono::system_clock::now());
  ulonglong secs = static_cast<ulonglong>(seconds) % 60;
  ulonglong minutes = (static_cast<ulonglong>(seconds) / 60) % 60;
  ulonglong hours = static_cast<ulonglong>(seconds) / 3600;
  ss << StringTable::get(TextKeys::TOTAL_ELAPSED_TIME) << ": " << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << secs << endl << endl;
 
  return ss.str();
}

// Helper functions
string CharacterDumper::get_party() const
{
  ostringstream ss;

  ss << TextMessages::get_hirelings_hired_message(creature->get_hirelings_hired()) << endl;
  ss << TextMessages::get_adventurers_joined_message(creature->get_adventurers_joined()) << endl << endl;

  // Party info
  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();

  if (current_map != nullptr)
  {
    ss << StringTable::get(PartyTextKeys::CURRENT_PARTY) << ": ";

    if (current_map->get_map_type() == MapType::MAP_TYPE_WORLD)
    {
      ss << StringTable::get(PartyTextKeys::PARTY_IN_TRANSIT);
    }
    else
    {
      const CreatureMap& creatures = current_map->get_creatures_ref();
      vector<string> follower_descs;

      for (const auto& c_pair : creatures)
      {
        ostringstream ss2;
        CreaturePtr f = c_pair.second;
        CharacterDumper cd(f);

        if (f && f->get_leader_id() == creature->get_id())
        {
          string name = f->get_name();
          ss2 << " - ";

          if (name.empty())
          {
            ss2 << StringTable::get(f->get_short_description_sid());
          }
          else
          {
            ss2 << name;
          }

          ss2 << " " << "(" << cd.get_synopsis(false) << ")";
          follower_descs.push_back(ss2.str());
        }
      }

      if (follower_descs.empty())
      {
        ss << "-";
      }
      else
      {
        ss << endl;

        for (const string& fdesc : follower_descs)
        {
          ss << fdesc << endl;
        }
      }
    }
  }

  return ss.str();
}

string CharacterDumper::get_synopsis(const bool centre) const
{
  ostringstream ss;
  
  string race_id = creature->get_race_id();
  string class_id = creature->get_class_id();

  ClassManager cm;
  RaceManager rm;
  Race* race = rm.get_race(race_id);
  Class* char_class = cm.get_class(class_id);
    
  if (race && char_class)
  {
    string race_name = StringTable::get(race->get_race_name_sid());
    string class_name = StringTable::get(char_class->get_class_name_sid());
      
    string character_synopsis = "L" + std::to_string(creature->get_level().get_current()) + " " + race_name + " " + class_name;
    trim_right(character_synopsis);

    if (centre)
    {
      ss << String::centre(character_synopsis, num_cols);
    }
    else
    {
      ss << character_synopsis;
    }
  }

  return ss.str();
}

// Get the creature's vital statistics: age, sex, size, hair, eyes.
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
  Alignment a;
  string alignment = StringTable::get(TextKeys::ALIGNMENT) + ": " + StringTable::get(a.get_alignment_sid(creature->get_alignment().get_alignment_range()));
  string size = StringTable::get(SizeTextKeys::SIZE) + ": " + StringTable::get(SizeTextKeys::get_size_sid_from_creature_size(creature->get_size()));
  
  vl.at(0).replace(0, age.size(), age);
  vl.at(0).replace(30, alignment.size(), alignment);
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
  CreatureSex cs = creature->get_sex();

  if (cs != CreatureSex::CREATURE_SEX_NOT_SPECIFIED)
  {
    string sex = StringTable::get(TextKeys::SEX) + ": " + TextMessages::get_sex(cs);
    vl.at(2).replace(0, sex.size(), sex);
  }

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

string CharacterDumper::get_carrying_capacity() const
{
  ostringstream ss;

  if (creature != nullptr)
  {
    ss << StringTable::get(TextKeys::CARRYING_CAPACITY) << ": " << TextMessages::get_carrying_capacity_message(creature);
  }

  return ss.str();
}
