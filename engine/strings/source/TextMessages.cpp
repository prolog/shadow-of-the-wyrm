#include <boost/algorithm/string/replace.hpp>
#include "ActionTextKeys.hpp"
#include "ClassManager.hpp"
#include "Conversion.hpp"
#include "EquipmentTextKeys.hpp"
#include "ItemDescriberFactory.hpp"
#include "TextMessages.hpp"
#include "EntranceTextKeys.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

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
const string TextMessages::ITEM_PICK_UP_MESSAGE               = "ITEM_PICK_UP_MESSAGE";
const string TextMessages::ITEM_PICK_UP_AND_MERGE_MESSAGE     = "ITEM_PICK_UP_AND_MERGE_MESSAGE";
const string TextMessages::ITEM_ON_GROUND_DESCRIPTION_MESSAGE = "ITEM_ON_GROUND_DESCRIPTION_MESSAGE";
const string TextMessages::CURRENCY_MESSAGE_SINGLE            = "CURRENCY_MESSAGE_SINGLE";
const string TextMessages::CURRENCY_MESSAGE_MULTIPLE          = "CURRENCY_MESSAGE_MULTIPLE";
const string TextMessages::NAME_TITLE_MESSAGE                 = "NAME_TITLE_MESSAGE";

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
  escapes_message[0] = toupper(escapes_message[0]);
  return escapes_message;
}

string TextMessages::get_action_not_found_message(const string& command_action)
{
  string action_message = StringTable::get(ActionTextKeys::ACTION_NOT_FOUND);
  boost::replace_first(action_message, "%s", String::clean(command_action));
  return action_message;
}

string TextMessages::get_dumping_character_message(const string& creature_name)
{
  string dumping_message = StringTable::get(TextMessages::DUMPING_CHARACTER_MESSAGE);
  boost::replace_first(dumping_message, "%s", creature_name);
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

  ss << query;
  ss << " [";
  ss << StringTable::get(TextKeys::DECISION_CONFIRM_KEY);
  ss << "/" << StringTable::get(TextKeys::DECISION_DENY_KEY);
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

string TextMessages::get_item_drop_message(const bool blind, ItemPtr item)
{
  ItemDescriberPtr id = ItemDescriberFactory::create_item_describer(blind, item);

  string item_message = StringTable::get(TextMessages::ITEM_DROP_MESSAGE);
  boost::replace_first(item_message, "%s", id->describe_usage());
  
  return item_message;
}

string TextMessages::get_item_pick_up_message(const bool blind, ItemPtr item)
{
  ItemDescriberPtr id = ItemDescriberFactory::create_item_describer(blind, item);
  
  string item_message = StringTable::get(TextMessages::ITEM_PICK_UP_MESSAGE);
  boost::replace_first(item_message, "%s", id->describe_usage());
  return item_message;
}

string TextMessages::get_item_pick_up_and_merge_message(const bool blind, ItemPtr item)
{
  ItemDescriberPtr id = ItemDescriberFactory::create_item_describer(blind, item);

  string item_message = StringTable::get(TextMessages::ITEM_PICK_UP_AND_MERGE_MESSAGE);
  boost::replace_first(item_message, "%s", id->describe_usage());
  return item_message;
}

string TextMessages::get_item_on_ground_description_message(const bool blind, ItemPtr item)
{
  ItemDescriberPtr id = ItemDescriberFactory::create_item_describer(blind, item);

  string item_message = StringTable::get(TextMessages::ITEM_ON_GROUND_DESCRIPTION_MESSAGE);
  boost::replace_first(item_message, "%s", id->describe_usage());
  return item_message;
}

string TextMessages::get_currency_amount_message(const uint currency_amount)
{
  string currency_message = StringTable::get(CURRENCY_MESSAGE_SINGLE);

  if (currency_amount != 1)
  {
    currency_message = StringTable::get(CURRENCY_MESSAGE_MULTIPLE);
    boost::replace_first(currency_message, "%s", Integer::to_string(currency_amount));
  }
  
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
      if (creature->get_sex() == CreatureSex::CREATURE_SEX_MALE)
      {
        reflexive_pronoun = StringTable::get(TextKeys::HIMSELF);
      }
      else
      {
        reflexive_pronoun = StringTable::get(TextKeys::HERSELF);
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