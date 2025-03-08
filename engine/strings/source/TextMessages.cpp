#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>
#include "ActionTextKeys.hpp"
#include "CarryingCapacityCalculator.hpp"
#include "ClassManager.hpp"
#include "Conversion.hpp"
#include "CreatureDescriber.hpp"
#include "EntranceTextKeys.hpp"
#include "EquipmentTextKeys.hpp"
#include "Game.hpp"
#include "ItemDescriberFactory.hpp"
#include "ItemIdentifier.hpp"
#include "Naming.hpp"
#include "ReligionManager.hpp"
#include "RNG.hpp"
#include "Setting.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"

using namespace std;

TextMessages::TextMessages()
{
}

TextMessages::~TextMessages()
{
}

const string TextMessages::WELCOME_MESSAGE                    = "WELCOME_MESSAGE";
const string TextMessages::WELCOME_BACK_MESSAGE               = "WELCOME_BACK_MESSAGE";
const string TextMessages::DUMPING_CHARACTER_MESSAGE          = "DUMPING_CHARACTER_MESSAGE";
const string TextMessages::ITEM_DROP_MESSAGE                  = "ITEM_DROP_MESSAGE";
const string TextMessages::ITEM_DROP_MESSAGE_MONSTER          = "ITEM_DROP_MESSAGE_MONSTER";
const string TextMessages::BURY_MESSAGE                       = "BURY_MESSAGE";
const string TextMessages::BURY_MESSAGE_MONSTER               = "BURY_MESSAGE_MONSTER";
const string TextMessages::ITEM_PICK_UP_MESSAGE_PLAYER        = "ITEM_PICK_UP_MESSAGE_PLAYER";
const string TextMessages::ITEM_PICK_UP_MESSAGE_MONSTER       = "ITEM_PICK_UP_MESSAGE_MONSTER";
const string TextMessages::ITEM_PICK_UP_AND_MERGE_MESSAGE_PLAYER = "ITEM_PICK_UP_AND_MERGE_MESSAGE_PLAYER";
const string TextMessages::ITEM_PICK_UP_AND_MERGE_MESSAGE_MONSTER = "ITEM_PICK_UP_AND_MERGE_MESSAGE_MONSTER";
const string TextMessages::ITEM_ON_GROUND_BLIND_DESCRIPTION_MESSAGE = "ITEM_ON_GROUND_BLIND_DESCRIPTION_MESSAGE";
const string TextMessages::ITEM_ON_GROUND_DESCRIPTION_MESSAGE = "ITEM_ON_GROUND_DESCRIPTION_MESSAGE";
const string TextMessages::CURRENCY_MESSAGE_SINGLE            = "CURRENCY_MESSAGE_SINGLE";
const string TextMessages::CURRENCY_MESSAGE_MULTIPLE          = "CURRENCY_MESSAGE_MULTIPLE";
const string TextMessages::CURRENCY_OWING_MESSAGE             = "CURRENCY_OWING_MESSAGE";
const string TextMessages::NAME_TITLE_MESSAGE                 = "NAME_TITLE_MESSAGE";
const string TextMessages::EXPERIENCE_SYNOPSIS_MESSAGE        = "EXPERIENCE_SYNOPSIS_MESSAGE";
const string TextMessages::EXPERIENCE_SYNOPSIS_MAX_MESSAGE    = "EXPERIENCE_SYNOPSIS_MAX_MESSAGE";
const string TextMessages::SPECIAL_DAY_MESSAGE                = "SPECIAL_DAY_MESSAGE";
const string TextMessages::ENGRAVING_MESSAGE                  = "ENGRAVING_MESSAGE";
const string TextMessages::INSCRIPTION_MESSAGE                = "INSCRIPTION_MESSAGE";
const string TextMessages::INSCRIPTION_WORLD_MESSAGE          = "INSCRIPTION_WORLD_MESSAGE";
const string TextMessages::SLOT_MACHINE_MESSAGE               = "SLOT_MACHINE_MESSAGE";
const string TextMessages::SLOT_MACHINE_OUTCOME_MESSAGE       = "SLOT_MACHINE_OUTCOME_MESSAGE";
const string TextMessages::CARRYING_CAPACITY_MESSAGE          = "CARRYING_CAPACITY_MESSAGE";
const string TextMessages::DAMAGE_MESSAGE                     = "DAMAGE_MESSAGE";
const string TextMessages::NPC_LEVEL_MESSAGE                  = "NPC_LEVEL_MESSAGE";
const string TextMessages::NPC_EQUIP_MESSAGE                  = "NPC_EQUIP_MESSAGE";
const string TextMessages::HIRELINGS_HIRED_MESSAGE            = "HIRELINGS_HIRED_MESSAGE";
const string TextMessages::ADVENTURERS_JOINED_MESSAGE         = "ADVENTURERS_JOINED_MESSAGE";
const string TextMessages::AFFECTED_BY                        = "AFFECTED_BY";
const string TextMessages::ENDING_MESSAGE                     = "ENDING_MESSAGE";
const string TextMessages::KILLED_BY_MESSAGE                  = "KILLED_BY_MESSAGE";
const string TextMessages::DEATH_DEPTH_LOCATION_MESSAGE       = "DEATH_DEPTH_LOCATION_MESSAGE";
const string TextMessages::BUILD_MESSAGE                      = "BUILD_MESSAGE";
const string TextMessages::SELECT_AGE_MESSAGE                 = "SELECT_AGE_MESSAGE";
const string TextMessages::BURIED_TREASURE_MESSAGE            = "BURIED_TREASURE_MESSAGE";
const string TextMessages::BURIED_TREASURE_SOURCE             = "BURIED_TREASURE_SOURCE";
const string TextMessages::BURIED_TREASURE_SOURCE_ADJECTIVE   = "BURIED_TREASURE_SOURCE_ADJECTIVE";
const string TextMessages::SHIPWRECK_MESSAGE                  = "SHIPWRECK_MESSAGE";
const string TextMessages::SHIPWRECK_SHIP_NAME                = "SHIPWRECK_SHIP_NAME";
const string TextMessages::SHIPWRECK_REASON                   = "SHIPWRECK_REASON";
const string TextMessages::SHIPWRECK_SHIP_NAME_POSSESSIVE     = "SHIPWRECK_SHIP_NAME_POSSESSIVE";
const string TextMessages::SHIPWRECK_SHIP_NAME_POSSESSOR      = "SHIPWRECK_SHIP_NAME_POSSESSOR";
const string TextMessages::SHIPWRECK_SHIP_NAME_POSSESSEE      = "SHIPWRECK_SHIP_NAME_POSSESSEE";

string TextMessages::get_full_header_text(const string& header, const uint num_cols)
{
  ostringstream ss;

  size_t header_text_size = header.size();
  unsigned int header_start = (num_cols / 2) - (header_text_size / 2);
  unsigned int header_end = (num_cols / 2) - (header_text_size / 2) + header_text_size;

  for (unsigned int i = 0; i < header_start - 1; i++)
  {
    ss << "-";
  }

  ss << " " << header << " ";

  for (unsigned int i = header_end + 1; i < num_cols; i++)
  {
    ss << "-";
  }

  return ss.str();
}

string TextMessages::get_player_description(const string& player_name)
{
  string player_desc;

  player_desc = StringTable::get(TextKeys::PLAYER_DESC);
  boost::replace_first(player_desc, "%s", player_name);

  return player_desc;
}

// Public functions used to access protected members.  These are used to wrap any const strings
// that contain replaceable symbols.
string TextMessages::get_welcome_message(const string& player_name, const bool new_player)
{
  string welcome_message = StringTable::get(TextMessages::WELCOME_BACK_MESSAGE);

  if (new_player)
  {
    welcome_message = StringTable::get(TextMessages::WELCOME_MESSAGE);
  }

  boost::replace_first(welcome_message, "%s", player_name);
  return welcome_message;
}

// Gets the overall death message.  This is the deity's message plus
// "You die..." (or equivalent)
string TextMessages::get_death_message(const string& deity_death_message_sid)
{
  string deity_death_message = StringTable::get(deity_death_message_sid);
  string you_die = StringTable::get(TextKeys::DEATH_MESSAGE);
  string death_message = deity_death_message + " " + you_die;
  return death_message;
}

// Gets the "The foo escapes into the wilderness." message.
string TextMessages::get_npc_escapes_message(const string& creature_description)
{
  string escapes_message = StringTable::get(TextKeys::NPC_ESCAPES_MESSAGE);
  boost::replace_first(escapes_message, "%s", creature_description);
  escapes_message[0] = static_cast<char>(toupper(escapes_message[0]));
  return escapes_message;
}

// Get a message for a creature who has just started to flee
string TextMessages::get_npc_flees_message(const string& creature_description)
{
  string flees_message = StringTable::get(TextKeys::NPC_FLEES_MESSAGE);
  boost::replace_first(flees_message, "%s", creature_description);
  flees_message[0] = static_cast<char>(toupper(flees_message[0]));
  return flees_message;
}

string TextMessages::get_npc_turns_to_fight_message(const string& creature_description)
{
  string turns_message = StringTable::get(TextKeys::NPC_TURNS_TO_FIGHT_MESSAGE);
  boost::replace_first(turns_message, "%s", creature_description);
  turns_message[0] = static_cast<char>(toupper(turns_message[0]));
  return turns_message;
}

string TextMessages::get_npc_level_message(const string& creature_description)
{
  string level_message = StringTable::get(NPC_LEVEL_MESSAGE);
  boost::replace_first(level_message, "%s", creature_description);
  level_message[0] = static_cast<char>(toupper(level_message[0]));
  return level_message;

}

string TextMessages::get_action_not_found_message(const string& command_action)
{
  string action_message = StringTable::get(ActionTextKeys::ACTION_NOT_FOUND);
  boost::replace_first(action_message, "%s", String::clean(command_action));
  return action_message;
}

string TextMessages::get_dumping_character_message(const string& char_name, const string& dir)
{
  string dumping_message = StringTable::get(TextMessages::DUMPING_CHARACTER_MESSAGE);
  boost::replace_first(dumping_message, "%s1", char_name);
  boost::replace_first(dumping_message, "%s2", dir);
  return dumping_message;
}

string TextMessages::get_sex(const CreatureSex sex)
{
  string creature_sex;
  
  switch(sex)
  {
    case CreatureSex::CREATURE_SEX_MALE:
      creature_sex = StringTable::get(TextKeys::SEX_MALE);
      break;
    case CreatureSex::CREATURE_SEX_FEMALE:
      creature_sex = StringTable::get(TextKeys::SEX_FEMALE);
      break;
    case CreatureSex::CREATURE_SEX_NOT_SPECIFIED:
      creature_sex = StringTable::get(TextKeys::SEX_NOT_SPECIFIED);
      break;
    default:
      creature_sex = "?";
      break;
  }
  
  return creature_sex;
}

string TextMessages::get_sex_abrv(const CreatureSex sex)
{
  string creature_sex;

  switch (sex)
  {
    case CreatureSex::CREATURE_SEX_MALE:
      creature_sex = StringTable::get(TextKeys::SEX_MALE_ABRV);
      break;
    case CreatureSex::CREATURE_SEX_FEMALE:
      creature_sex = StringTable::get(TextKeys::SEX_FEMALE_ABRV);
      break;
    default:
      break;
  }

  return creature_sex;
}

string TextMessages::get_equipment_location(const EquipmentWornLocation location)
{
  string equipment_location;
  
  switch(location)
  {
    case EquipmentWornLocation::EQUIPMENT_WORN_HEAD:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_HEAD);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_NECK:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_NECK);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_RIGHT_FINGER);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_LEFT_FINGER);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_WIELDED:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_WIELDED);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_OFF_HAND);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_BODY:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_BODY);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_AROUND_BODY);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_FEET:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_FEET);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_RANGED);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_AMMUNITION);
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_NONE:
    case EquipmentWornLocation::EQUIPMENT_WORN_LAST:
    default:
      equipment_location = "?";
      break;
  }
  
  return equipment_location;
}

string TextMessages::get_confirmation_message(const string& query_or_sid)
{
  ostringstream ss;
  string query = StringTable::get(query_or_sid);

  if (query.empty())
  {
    query = query_or_sid;
  }

  string confirm_key = StringTable::get(TextKeys::DECISION_CONFIRM_KEY);
  string deny_key = StringTable::get(TextKeys::DECISION_DENY_KEY);

  if (Game::instance().get_settings_ref().get_setting_as_bool(Setting::CONFIRMATION_REQUIRE_CAPITALIZATION))
  {
    confirm_key = boost::to_upper_copy(confirm_key);
    deny_key = boost::to_upper_copy(deny_key);
  }

  ss << query;
  ss << " [";
  ss << confirm_key;
  ss << "/" << deny_key;
  ss << "] ";
  
  return ss.str();
}

string TextMessages::get_area_entrance_message_given_terrain_type(const TileType type)
{
  string entrance_message;
  
  switch(type)
  {
    case TileType::TILE_TYPE_FIELD:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_FIELD);
      break;
    case TileType::TILE_TYPE_SCRUB:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_SCRUB);
      break;
    case TileType::TILE_TYPE_DESERT:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_DESERT);
      break;
    case TileType::TILE_TYPE_MOUNTAINS:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_MOUNTAINS);
      break;
    case TileType::TILE_TYPE_SEA:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_SEA);
      break;
    case TileType::TILE_TYPE_FOREST:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_FOREST);
      break;
    case TileType::TILE_TYPE_MARSH:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_MARSH);
      break;
    case TileType::TILE_TYPE_HILLS:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_HILLS);
      break;
    case TileType::TILE_TYPE_CAVERN:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_CAVERN);
      break;
    case TileType::TILE_TYPE_VILLAGE:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_VILLAGE);
      break;
    case TileType::TILE_TYPE_DUNGEON_COMPLEX:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_DUNGEON_COMPLEX);
      break;
    case TileType::TILE_TYPE_BARRACKS:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_BARRACKS);
      break;
    case TileType::TILE_TYPE_CASTLE:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_CASTLE);
      break;
    case TileType::TILE_TYPE_CHURCH:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_CHURCH);
      break;
    case TileType::TILE_TYPE_GRAVEYARD:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_GRAVEYARD);
      break;
    case TileType::TILE_TYPE_KEEP:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_KEEP);
      break;
    case TileType::TILE_TYPE_LIBRARY:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_LIBRARY);
      break;
    case TileType::TILE_TYPE_SITE_OF_DEATH:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_SITE_OF_DEATH);
      break;
    case TileType::TILE_TYPE_TEMPLE:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_TEMPLE);
      break;
    case TileType::TILE_TYPE_SHRINE:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_SHRINE);
      break;
    case TileType::TILE_TYPE_AIR:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_AIR);
      break;
    case TileType::TILE_TYPE_UNDEFINED:
    case TileType::TILE_TYPE_WHEAT:
    case TileType::TILE_TYPE_CAIRN:
    case TileType::TILE_TYPE_TREE:
    case TileType::TILE_TYPE_ROAD:
    case TileType::TILE_TYPE_RIVER:
    case TileType::TILE_TYPE_SHOALS:
    case TileType::TILE_TYPE_DUNGEON:
    case TileType::TILE_TYPE_ROCK:
    case TileType::TILE_TYPE_GRAVE:
    case TileType::TILE_TYPE_REEDS:
    case TileType::TILE_TYPE_BEACH:
    case TileType::TILE_TYPE_BUSH:
    case TileType::TILE_TYPE_WEEDS:
    case TileType::TILE_TYPE_SPRINGS:
    case TileType::TILE_TYPE_DAIS:
    case TileType::TILE_TYPE_UP_STAIRCASE:
    case TileType::TILE_TYPE_DOWN_STAIRCASE:
    default:
      break;
  }
  
  return entrance_message;
}

string TextMessages::get_item_drop_message(CreaturePtr creature, const bool blind, ItemPtr item)
{
  bool player = creature && creature->get_is_player();
  ItemDescriberPtr id = ItemDescriberFactory::create_item_describer(player && blind, item);
  string item_message = StringTable::get(TextMessages::ITEM_DROP_MESSAGE);

  if (player)
  {
    boost::replace_first(item_message, "%s", id->describe_usage());
  }
  else
  {
    item_message = StringTable::get(TextMessages::ITEM_DROP_MESSAGE_MONSTER);

    boost::replace_first(item_message, "%s1", StringTable::get(creature->get_description_sid()));
    boost::replace_first(item_message, "%s2", id->describe_usage());
    item_message[0] = static_cast<char>(toupper(item_message[0]));
  }

  return item_message;
}

string TextMessages::get_burial_message(CreaturePtr creature)
{
  bool player = creature && creature->get_is_player();
  string bury_message = StringTable::get(TextMessages::BURY_MESSAGE);

  if (!player)
  {
    bury_message = StringTable::get(BURY_MESSAGE_MONSTER);
  }

  return bury_message;
}

string TextMessages::get_item_pick_up_message(const bool player_blind, CreaturePtr creature, ItemPtr item)
{
  ItemDescriberPtr id = ItemDescriberFactory::create_item_describer(player_blind, item);
  string item_message;

  if (creature->get_is_player())
  {
    item_message = StringTable::get(TextMessages::ITEM_PICK_UP_MESSAGE_PLAYER);
  }
  else
  {
    item_message = StringTable::get(TextMessages::ITEM_PICK_UP_MESSAGE_MONSTER);
    CreatureDescriber cd(creature, creature, true);
    boost::replace_first(item_message, "%s1", cd.describe());
  }

  boost::replace_first(item_message, "%s2", id->describe_usage());
  item_message[0] = static_cast<char>(toupper(item_message[0]));
  return item_message;
}

string TextMessages::get_item_pick_up_and_merge_message(const bool player_blind, CreaturePtr creature, ItemPtr item)
{
  ItemDescriberPtr id = ItemDescriberFactory::create_item_describer(player_blind, item);
  string item_message;

  if (creature->get_is_player())
  {
    item_message = StringTable::get(TextMessages::ITEM_PICK_UP_AND_MERGE_MESSAGE_PLAYER);
  }
  else
  {
    CreatureDescriber cd(creature, creature, true);
    item_message = StringTable::get(TextMessages::ITEM_PICK_UP_AND_MERGE_MESSAGE_MONSTER);
    boost::replace_first(item_message, "%s1", cd.describe());
  }

  boost::replace_first(item_message, "%s2", id->describe_usage());
  item_message[0] = static_cast<char>(toupper(item_message[0]));
  return item_message;
}

string TextMessages::get_item_on_ground_description_message(const bool blind, ItemPtr item)
{
  ItemDescriberPtr id = ItemDescriberFactory::create_item_describer(blind, item);
  string item_message;

  if (blind)
  {
    item_message = StringTable::get(TextMessages::ITEM_ON_GROUND_BLIND_DESCRIPTION_MESSAGE);    
  }
  else
  {
    item_message = StringTable::get(TextMessages::ITEM_ON_GROUND_DESCRIPTION_MESSAGE);
  }

  boost::replace_first(item_message, "%s", id->describe_usage());
  return item_message;
}

string TextMessages::get_currency_amount_message(const uint currency_amount)
{
  string currency_message = StringTable::get(CURRENCY_MESSAGE_SINGLE);

  if (currency_amount != 1)
  {
    currency_message = StringTable::get(CURRENCY_MESSAGE_MULTIPLE);
    boost::replace_first(currency_message, "%s", std::to_string(currency_amount));
  }
  
  return currency_message;
}

string TextMessages::get_unpaid_amount_message(const uint unpaid_amount)
{
  string currency_message = StringTable::get(CURRENCY_OWING_MESSAGE);
  boost::replace_first(currency_message, "%s", to_string(unpaid_amount));
  return currency_message;
}

string TextMessages::get_reflexive_pronoun(CreaturePtr creature)
{
  string reflexive_pronoun = StringTable::get(TextKeys::ITSELF);

  if (creature)
  {
    if (creature->get_is_player())
    {
      reflexive_pronoun = StringTable::get(TextKeys::YOURSELF);
    }
    else
    {
      CreatureSex cs = creature->get_sex();

      if (cs == CreatureSex::CREATURE_SEX_MALE)
      {
        reflexive_pronoun = StringTable::get(TextKeys::HIMSELF);
      }
      else if (cs == CreatureSex::CREATURE_SEX_FEMALE)
      {
        reflexive_pronoun = StringTable::get(TextKeys::HERSELF);
      }
      else
      {
        reflexive_pronoun = StringTable::get(TextKeys::ITSELF);
      }
    }
  }

  return reflexive_pronoun;
}

string TextMessages::get_name_and_title(CreaturePtr creature)
{
  string nt;

  if (creature)
  {
    ClassManager cm;

    nt = StringTable::get(NAME_TITLE_MESSAGE);
    boost::replace_first(nt, "%s", creature->get_name());
    boost::replace_first(nt, "%s", cm.get_title(creature));
  }

  return nt;
}

string TextMessages::get_carrying_capacity_message(CreaturePtr creature)
{
  string msg = StringTable::get(CARRYING_CAPACITY_MESSAGE);
  CarryingCapacityCalculator ccc;

  uint current_items = creature->count_items();
  uint total_items = ccc.calculate_carrying_capacity_total_items(creature);
  uint total_weight = Weight::get_lbs(creature->get_weight_carried());
  uint burdened = Weight::get_lbs(ccc.calculate_burdened_weight(creature));
  uint strained = Weight::get_lbs(ccc.calculate_strained_weight(creature));
  uint overburdened = Weight::get_lbs(ccc.calculate_overburdened_weight(creature));

  boost::replace_first(msg, "%s", to_string(current_items));
  boost::replace_first(msg, "%s", to_string(total_items));
  boost::replace_first(msg, "%s", to_string(total_weight));
  boost::replace_first(msg, "%s", to_string(burdened));
  boost::replace_first(msg, "%s", to_string(strained));
  boost::replace_first(msg, "%s", to_string(overburdened));

  return msg;
}

string TextMessages::get_experience_synopsis(const int level, const int exp, const int exp_required, const int next_level, const std::string& race_name, const float r_mult, const std::string class_name, const float c_mult)
{
  string exp_synopsis = StringTable::get(EXPERIENCE_SYNOPSIS_MESSAGE);

  if (level == static_cast<int>(CreatureConstants::MAX_CREATURE_LEVEL))
  {
    exp_synopsis = StringTable::get(EXPERIENCE_SYNOPSIS_MAX_MESSAGE);
  }


  boost::replace_first(exp_synopsis, "%s1", std::to_string(level));
  boost::replace_first(exp_synopsis, "%s2", std::to_string(exp));
  boost::replace_first(exp_synopsis, "%s3", std::to_string(exp_required));
  boost::replace_first(exp_synopsis, "%s4", std::to_string(next_level));
  boost::replace_first(exp_synopsis, "%s5", race_name);
  boost::replace_first(exp_synopsis, "%s6", Float::to_string(r_mult, 2));
  boost::replace_first(exp_synopsis, "%s7", class_name);
  boost::replace_first(exp_synopsis, "%s8", Float::to_string(c_mult, 2));

  return exp_synopsis;
}

string TextMessages::get_special_day_message(const string& name_sid, const string& desc_sid)
{
  string special_day_msg = StringTable::get(SPECIAL_DAY_MESSAGE);

  boost::replace_first(special_day_msg, "%s1", StringTable::get(name_sid));
  boost::replace_first(special_day_msg, "%s2", StringTable::get(desc_sid));

  return special_day_msg;
}

string TextMessages::get_engraving_message(const string& engraving_sid)
{
  string engraving_msg = StringTable::get(ENGRAVING_MESSAGE);

  boost::replace_first(engraving_msg, "%s", StringTable::get(engraving_sid));

  return engraving_msg;
}

string TextMessages::get_inscription_message(const string& inscription_sid, const bool is_world_map)
{
  string inscription_msg = INSCRIPTION_MESSAGE;

  if (is_world_map)
  {
    inscription_msg = INSCRIPTION_WORLD_MESSAGE;
  }

  inscription_msg = StringTable::get(inscription_msg);
  string repl = StringTable::get(inscription_sid);

  if (repl.empty() && !inscription_sid.empty())
  {
    repl = inscription_sid;
  }

  boost::replace_first(inscription_msg, "%s", repl);

  return inscription_msg;
}

string TextMessages::get_replacement_message(const string& msg, const string& replace)
{
  string replace_msg = msg;
  boost::replace_first(replace_msg, "%s", replace);

  return replace_msg;
}

string TextMessages::get_bool_sid(const bool val)
{
  if (val)
  {
    return TextKeys::BOOL_TRUE;
  }
  else
  {
    return TextKeys::BOOL_FALSE;
  }
}

string TextMessages::get_character_creation_synopsis(const CreatureSex cs, Race* race, Class* cur_class, const string& deity_id, StartingLocation* sl)
{
  vector<string> details;

  if (cs != CreatureSex::CREATURE_SEX_NOT_SPECIFIED)
  {
    details.push_back(TextMessages::get_sex(cs));
  }

  if (race != nullptr)
  {
    details.push_back(StringTable::get(race->get_race_name_sid()));
  }

  if (cur_class != nullptr)
  {
    details.push_back(StringTable::get(cur_class->get_class_name_sid()));
  }

  // Deity should always be separated from what comes before.
  if (!deity_id.empty())
  {
    ReligionManager rm;
    details.push_back("(" + StringTable::get(rm.get_deity_name_sid(deity_id)) + ")");
  }

  if (sl != nullptr)
  {
    details.push_back("- " + StringTable::get(sl->get_short_description_sid()));
  }

  ostringstream ss;

  for (const string& d : details)
  {
    ss << d << " ";
  }

  string synopsis = ss.str();
  boost::trim(synopsis);

  return synopsis;
}

string TextMessages::get_slot_machine_message(const int cost, const int pct_chance_win, const int payout_amount)
{
  string msg = StringTable::get(TextMessages::SLOT_MACHINE_MESSAGE);

  boost::replace_first(msg, "%s", to_string(cost));
  boost::replace_first(msg, "%s", to_string(pct_chance_win));
  boost::replace_first(msg, "%s", to_string(payout_amount));

  return msg;
}

string TextMessages::get_slot_machine_outcome_message(const string& first_sid, const string& second_sid, const string& third_sid)
{
  string msg = StringTable::get(TextMessages::SLOT_MACHINE_OUTCOME_MESSAGE);

  boost::replace_first(msg, "%s", StringTable::get(first_sid));
  boost::replace_first(msg, "%s", StringTable::get(second_sid));
  boost::replace_first(msg, "%s", StringTable::get(third_sid));

  return msg;
}

string TextMessages::get_damage_message(const Damage& damage)
{
  string msg = StringTable::get(TextMessages::DAMAGE_MESSAGE);

  boost::replace_first(msg, "%s", damage.str());

  return msg;
}

string TextMessages::get_equip_message(const string& creature_desc_sid, const string& item_desc)
{
  string msg = StringTable::get(TextMessages::NPC_EQUIP_MESSAGE);

  boost::replace_first(msg, "%s1", StringTable::get(creature_desc_sid));
  boost::replace_first(msg, "%s2", item_desc);

  msg[0] = static_cast<char>(toupper(msg[0]));

  return msg;
}

string TextMessages::get_hirelings_hired_message(const int hired)
{
  string msg = StringTable::get(TextMessages::HIRELINGS_HIRED_MESSAGE);
  boost::replace_first(msg, "%s", to_string(hired));

  return msg;
}

string TextMessages::get_adventurers_joined_message(const int joined)
{
  string msg = StringTable::get(TextMessages::ADVENTURERS_JOINED_MESSAGE);
  boost::replace_first(msg, "%s", to_string(joined));

  return msg;
}

string TextMessages::get_modifier_message(const string& status_or_spell_id, const Modifier& m, CreaturePtr c)
{
  ostringstream ss;
  string msg;

  if (c != nullptr)
  {
    if (!status_or_spell_id.empty())
    {
      msg = StringTable::get(AFFECTED_BY);
      string item_id = m.get_item_id();

      if (StatusIdentifiers::is_status_identifier(status_or_spell_id))
      {
        boost::replace_first(msg, "%s", StringTable::get(StatusAilmentTextKeys::get_status_for_identifier(status_or_spell_id)));
      }
      else
      {
        const SpellMap& spells = Game::instance().get_spells_ref();
        auto s_it = spells.find(status_or_spell_id);

        if (s_it != spells.end())
        {
          boost::replace_first(msg, "%s", StringTable::get(s_it->second.get_spell_name_sid()));
        }
      }

      ss << msg;

      if (!item_id.empty())
      {
        ItemPtr i = c->get_equipment().get_item_from_id(item_id);

        if (i != nullptr)
        {
          ItemIdentifier iid;
          ss << "(" << boost::trim_copy(iid.get_appropriate_description(i)) << ")";
        }
      }
    }
  }

  return ss.str();
}

string TextMessages::get_ending_message(const string& ending_time)
{
  string msg = StringTable::get(ENDING_MESSAGE);
  boost::replace_first(msg, "%s", ending_time);
  return msg;
}

string TextMessages::get_killed_by_message(const string& killed_by_source)
{
  string msg = StringTable::get(KILLED_BY_MESSAGE);
  boost::replace_first(msg, "%s1", killed_by_source);

  return msg;
}

string TextMessages::get_death_depth_location_message(const string& depth, const string& location)
{
  string msg = StringTable::get(DEATH_DEPTH_LOCATION_MESSAGE);
  boost::replace_first(msg, "%s1", depth);
  boost::replace_first(msg, "%s2", location);

  return msg;
}

string TextMessages::get_build_message(const string& thing_built)
{
  string msg = StringTable::get(BUILD_MESSAGE);
  boost::replace_first(msg, "%s", thing_built);

  return msg;
}

string TextMessages::get_select_age_message(const int min_age, const int max_age)
{
  string msg = StringTable::get(SELECT_AGE_MESSAGE);
  boost::replace_first(msg, "%s1", std::to_string(min_age));
  boost::replace_first(msg, "%s2", std::to_string(max_age));

  return msg;
}

string TextMessages::get_and_replace(const string& sid, const vector<string>& replacements)
{
  string msg = StringTable::get(sid);

  for (size_t i = 0; i < replacements.size(); i++)
  {
    size_t si = i + 1;
    string to_replace = "%s" + std::to_string(si);

    boost::replace_first(msg, to_replace, replacements.at(i));

    // We replace numerical indices, but also replace the standard %s.
    // This gives you a choice of whether to use %s or %s1.
    if (i == 0)
    {
      boost::replace_first(msg, "%s", replacements.at(i));
    }
  }

  return msg;
}

string TextMessages::get_hidden_treasure_message(const bool is_underwater)
{
  if (is_underwater)
  {
    return get_shipwreck_message();
  }
  else
  {
    return get_buried_treasure_message();
  }
}

string TextMessages::get_buried_treasure_message()
{
  string t_msg = StringTable::get(BURIED_TREASURE_MESSAGE);
  string source;

  if (RNG::percent_chance(30))
  {
    vector<string> sources = String::create_string_vector_from_csv_string(StringTable::get(BURIED_TREASURE_SOURCE_ADJECTIVE));

    if (!sources.empty())
    {
      string name = Naming::generate_name(CreatureSex::CREATURE_SEX_NOT_SPECIFIED);
      source = boost::trim_copy(sources.at(RNG::range(0, sources.size() - 1)));

      boost::replace_first(source, "%s", name);
    }
  }
  else
  {
    vector<string> sources = String::create_string_vector_from_csv_string(StringTable::get(BURIED_TREASURE_SOURCE));

    if (!sources.empty())
    {
      source = boost::trim_copy(sources.at(RNG::range(0, sources.size() - 1)));
    }
  }

  boost::replace_first(t_msg, "%s", source);
  return t_msg;
}

string TextMessages::get_shipwreck_message()
{
  string shipwreck_msg = StringTable::get(SHIPWRECK_MESSAGE);
  vector<string> ships = String::create_string_vector_from_csv_string(StringTable::get(SHIPWRECK_SHIP_NAME));
  vector<string> reasons = String::create_string_vector_from_csv_string(StringTable::get(SHIPWRECK_REASON));

  if (!ships.empty() && !reasons.empty())
  {
    string ship;
    
    if (RNG::percent_chance(75))
    {
      ship = boost::trim_copy(ships.at(RNG::range(0, ships.size() - 1)));
    }
    else
    {
      ship = StringTable::get(SHIPWRECK_SHIP_NAME_POSSESSIVE);
      vector<string> possessors = String::create_string_vector_from_csv_string(StringTable::get(SHIPWRECK_SHIP_NAME_POSSESSOR));
      vector<string> possessees = String::create_string_vector_from_csv_string(StringTable::get(SHIPWRECK_SHIP_NAME_POSSESSEE));

      boost::replace_first(ship, "%s1", boost::trim_copy(possessors.at(RNG::range(0, possessors.size() - 1))));
      boost::replace_first(ship, "%s2", boost::trim_copy(possessees.at(RNG::range(0, possessees.size() - 1))));
    }

    string reason = boost::trim_copy(reasons.at(RNG::range(0, reasons.size() - 1)));

    boost::replace_first(shipwreck_msg, "%s1", ship);
    boost::replace_first(shipwreck_msg, "%s2", reason);
  }

  return shipwreck_msg;
}
