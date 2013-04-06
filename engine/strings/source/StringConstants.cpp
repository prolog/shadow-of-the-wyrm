#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include "Conversion.hpp"
#include "ItemDescriber.hpp"
#include "StringTable.hpp"
#include "StringConstants.hpp"

using namespace std;

TextKeys::TextKeys()
{
}

TextKeys::~TextKeys()
{
}

const string TextKeys::SL_TITLE    = "SL_TITLE";
const string TextKeys::SL_TITLE_POEM = "SL_TITLE_POEM";
const string TextKeys::COPYRIGHT_NOTICE = "COPYRIGHT_NOTICE";
const string TextKeys::SL_TITLE_NEW_GAME = "SL_TITLE_NEW_GAME";
const string TextKeys::CHARACTER_ALREADY_EXISTS = "CHARACTER_ALREADY_EXISTS";
const string TextKeys::SL_TITLE_LOAD_GAME = "SL_TITLE_LOAD_GAME";
const string TextKeys::SL_TITLE_QUIT_GAME = "SL_TITLE_QUIT_GAME";
const string TextKeys::EXIT = "EXIT";
const string TextKeys::DEATH_MESSAGE = "DEATH_MESSAGE";
const string TextKeys::DEFAULT_PLAYER_NAME = "DEFAULT_PLAYER_NAME";
const string TextKeys::YOU = "YOU";
const string TextKeys::NPC_ESCAPES_MESSAGE = "NPC_ESCAPES_MESSAGE";
const string TextKeys::SELECT_RACE = "SELECT_RACE";
const string TextKeys::SELECT_CLASS = "SELECT_CLASS";
const string TextKeys::SELECT_DEITY = "SELECT_DEITY";
const string TextKeys::SELECT_SAVED_GAME = "SELECT_SAVED_GAME";
const string TextKeys::DEITY = "DEITY";
const string TextKeys::AGE = "AGE";
const string TextKeys::SEX = "SEX";
const string TextKeys::HAIR_COLOUR = "HAIR_COLOUR";
const string TextKeys::EYE_COLOUR = "EYE_COLOUR";
const string TextKeys::SELECT_SEX = "SELECT_SEX";
const string TextKeys::SEX_MALE = "SEX_MALE";
const string TextKeys::SEX_FEMALE = "SEX_FEMALE";

const string TextKeys::RACE_1_NAME = "RACE_1_NAME";
const string TextKeys::RACE_1_SHORT_DESC = "RACE_1_SHORT_DESC";
const string TextKeys::RACE_1_DESC = "RACE_1_DESC";
const string TextKeys::RACE_2_NAME = "RACE_2_NAME";
const string TextKeys::RACE_2_SHORT_DESC = "RACE_2_SHORT_DESC";
const string TextKeys::RACE_2_DESC = "RACE_2_DESC";
const string TextKeys::RACE_3_NAME = "RACE_3_NAME";
const string TextKeys::RACE_3_SHORT_DESC = "RACE_3_SHORT_DESC";
const string TextKeys::RACE_3_DESC = "RACE_3_DESC";
const string TextKeys::RACE_4_NAME = "RACE_4_NAME";
const string TextKeys::RACE_4_SHORT_DESC = "RACE_4_SHORT_DESC";
const string TextKeys::RACE_4_DESC = "RACE_4_DESC";
const string TextKeys::RACE_5_NAME = "RACE_5_NAME";
const string TextKeys::RACE_5_SHORT_DESC = "RACE_5_SHORT_DESC";
const string TextKeys::RACE_5_DESC = "RACE_5_DESC";
const string TextKeys::RACE_6_NAME = "RACE_6_NAME";
const string TextKeys::RACE_6_SHORT_DESC = "RACE_6_SHORT_DESC";
const string TextKeys::RACE_6_DESC = "RACE_6_DESC";
const string TextKeys::RACE_7_NAME = "RACE_7_NAME";
const string TextKeys::RACE_7_SHORT_DESC = "RACE_7_SHORT_DESC";
const string TextKeys::RACE_7_DESC = "RACE_7_DESC";
const string TextKeys::RACE_8_NAME = "RACE_8_NAME";
const string TextKeys::RACE_8_SHORT_DESC = "RACE_8_SHORT_DESC";
const string TextKeys::RACE_8_DESC = "RACE_8_DESC";
const string TextKeys::RACE_9_NAME = "RACE_9_NAME";
const string TextKeys::RACE_9_SHORT_DESC = "RACE_9_SHORT_DESC";
const string TextKeys::RACE_9_DESC = "RACE_8_DESC";
const string TextKeys::RACE_10_NAME = "RACE_10_NAME";
const string TextKeys::RACE_10_SHORT_DESC = "RACE_10_SHORT_DESC";
const string TextKeys::RACE_10_DESC = "RACE_10_DESC";

const string TextKeys::STRENGTH          = "STRENGTH";
const string TextKeys::STRENGTH_ABRV     = "STRENGTH_ABRV";
const string TextKeys::DEXTERITY         = "DEXTERITY";
const string TextKeys::DEXTERITY_ABRV    = "DEXTERITY_ABRV";
const string TextKeys::AGILITY           = "AGILITY";
const string TextKeys::AGILITY_ABRV      = "AGILITY_ABRV";
const string TextKeys::HEALTH            = "HEALTH";
const string TextKeys::HEALTH_ABRV       = "HEALTH_ABRV";
const string TextKeys::INTELLIGENCE      = "INTELLIGENCE";
const string TextKeys::INTELLIGENCE_ABRV = "INTELLIGENCE_ABRV";
const string TextKeys::WILLPOWER         = "WILLPOWER";
const string TextKeys::WILLPOWER_ABRV    = "WILLPOWER_ABRV";
const string TextKeys::CHARISMA          = "CHARISMA";
const string TextKeys::CHARISMA_ABRV     = "CHARISMA_ABRV";

const string TextKeys::VALOUR            = "VALOUR";
const string TextKeys::VALOUR_ABRV       = "VALOUR_ABRV";
const string TextKeys::SPIRIT            = "SPIRIT";
const string TextKeys::SPIRIT_ABRV       = "SPIRIT_ABRV";
const string TextKeys::SPEED             = "SPEED";
const string TextKeys::SPEED_ABRV        = "SPEED_ABRV";

const string TextKeys::HIT_POINTS        = "HIT_POINTS";
const string TextKeys::HIT_POINTS_ABRV   = "HIT_POINTS_ABRV";
const string TextKeys::ARCANA_POINTS     = "ARCANA_POINTS";
const string TextKeys::ARCANA_POINTS_ABRV = "ARCANA_POINTS_ABRV";

const string TextKeys::EVADE             = "EVADE";
const string TextKeys::EVADE_ABRV        = "EVADE_ABRV";
const string TextKeys::SOAK              = "SOAK";
const string TextKeys::SOAK_ABRV         = "SOAK_ABRV";

const string TextKeys::LEVEL             = "LEVEL";
const string TextKeys::LEVEL_ABRV        = "LEVEL_ABRV";

const string TextKeys::DAMAGE_MELEE      = "DAMAGE_MELEE";
const string TextKeys::DAMAGE_RANGED     = "DAMAGE_RANGED";

const string TextKeys::EQUIPMENT         = "EQUIPMENT";
const string TextKeys::EQUIPMENT_PROMPT  = "EQUIPMENT_PROMPT";
const string TextKeys::INVENTORY         = "INVENTORY";
const string TextKeys::INVENTORY_PROMPT  = "INVENTORY_PROMPT";

const string TextKeys::DECISION_CONFIRM_KEY = "DECISION_CONFIRM_KEY";
const string TextKeys::DECISION_DENY_KEY    = "DECISION_DENY_KEY";
const string TextKeys::DECISION_LEAVE_AREA  = "DECISION_LEAVE_AREA";
const string TextKeys::DECISION_QUIT_GAME   = "DECISION_QUIT_GAME";
const string TextKeys::DECISION_JUMP_INTO_WATER = "DECISION_JUMP_INTO_WATER";
const string TextKeys::DECISION_SAVE_GAME = "DECISION_SAVE_GAME";
const string TextKeys::DECISION_ATTACK_FRIENDLY_CREATURE = "DECISION_ATTACK_FRIENDLY_CREATURE";

const string TextKeys::GAIN_LEVEL = "GAIN_LEVEL";

const string TextKeys::UNARMED = "UNARMED";

// Date/time
DateTextKeys::DateTextKeys()
{
}

DateTextKeys::~DateTextKeys()
{
}

const string DateTextKeys::DATE_TIME_MESSAGE = "DATE_TIME_MESSAGE";

string DateTextKeys::get_date_time_message(const Date& date, const string& season_sid)
{
  string date_time_message = StringTable::get(DateTextKeys::DATE_TIME_MESSAGE);
  string season = StringTable::get(season_sid);
  
  string time = DateTextKeys::get_time(date);
  string day_of_week = StringTable::get(date.get_day_of_week_sid());
  string month = StringTable::get(date.get_month_sid());  

  boost::replace_first(date_time_message, "%s", time);
  boost::replace_first(date_time_message, "%s", day_of_week);
  boost::replace_first(date_time_message, "%s", Integer::to_string(date.get_day_of_month()));
  boost::replace_first(date_time_message, "%s", month);
  boost::replace_first(date_time_message, "%s", Integer::to_string(date.get_year()));
  boost::replace_first(date_time_message, "%s", season);
  
  return date_time_message;
}

string DateTextKeys::get_time(const Date& date)
{
  uint hours = date.get_hours();
  uint minutes = date.get_minutes();
  uint seconds = static_cast<uint>(date.get_seconds());
  
  ostringstream ss;
  
  if (hours < 10)
  {
    ss << "0";
  }
  
  ss << hours << ":";
  
  if (minutes < 10)
  {
    ss << "0";
  }
  
  ss << minutes << ":";
  
  if (seconds < 10)
  {
    ss << "0";
  }
  
  ss << seconds;
  
  return ss.str();
}

// Colours
ColourTextKeys::ColourTextKeys()
{
}

ColourTextKeys::~ColourTextKeys()
{
}

string ColourTextKeys::get_colour_sid_from_hair_colour(const HairColour hair_colour)
{
  string colour_sid;
  
  switch(hair_colour)
  {
    case HAIR_COLOUR_BLACK:
      colour_sid = COLOUR_BLACK;
      break;
    case HAIR_COLOUR_BROWN:
      colour_sid = COLOUR_BROWN;
      break;
    case HAIR_COLOUR_BLONDE:
      colour_sid = COLOUR_BLONDE;
      break;
    case HAIR_COLOUR_RED:
      colour_sid = COLOUR_RED;
      break;
    case HAIR_COLOUR_GREY:
      colour_sid = COLOUR_GREY;
      break;
    case HAIR_COLOUR_WHITE:
      colour_sid = COLOUR_WHITE;
      break;
    default:
      break;
  }
  
  return colour_sid;
}

string ColourTextKeys::get_colour_sid_from_eye_colour(const EyeColour eye_colour)
{
  string colour_sid;
  
  switch(eye_colour)
  {
    case EYE_COLOUR_BROWN:
      colour_sid = COLOUR_BROWN;
      break;
    case EYE_COLOUR_BLUE:
      colour_sid = COLOUR_BLUE;
      break;
    case EYE_COLOUR_GREEN:
      colour_sid = COLOUR_GREEN;
      break;
    case EYE_COLOUR_HAZEL:
      colour_sid = COLOUR_HAZEL;
      break;
    case EYE_COLOUR_GREY:
      colour_sid = COLOUR_GREY;
      break;
    default:
      break;
  }
  
  return colour_sid;
}

const string ColourTextKeys::COLOUR_BLACK = "COLOUR_BLACK";
const string ColourTextKeys::COLOUR_BROWN = "COLOUR_BROWN";
const string ColourTextKeys::COLOUR_BLONDE = "COLOUR_BLONDE";
const string ColourTextKeys::COLOUR_RED = "COLOUR_RED";
const string ColourTextKeys::COLOUR_GREEN = "COLOUR_GREEN";
const string ColourTextKeys::COLOUR_HAZEL = "COLOUR_HAZEL";
const string ColourTextKeys::COLOUR_BLUE = "COLOUR_BLUE";
const string ColourTextKeys::COLOUR_GREY = "COLOUR_GREY";
const string ColourTextKeys::COLOUR_WHITE = "COLOUR_WHITE";


SizeTextKeys::SizeTextKeys()
{
}

SizeTextKeys::~SizeTextKeys()
{
}

string SizeTextKeys::get_size_sid_from_creature_size(const CreatureSize size)
{
  string size_sid;
  
  switch(size)
  {
    case CREATURE_SIZE_TINY:
      size_sid = SIZE_TINY;
      break;
    case CREATURE_SIZE_SMALL:
      size_sid = SIZE_SMALL;
      break;
    case CREATURE_SIZE_MEDIUM:
      size_sid = SIZE_MEDIUM;
      break;
    case CREATURE_SIZE_LARGE:
      size_sid = SIZE_LARGE;
      break;
    case CREATURE_SIZE_HUGE:
      size_sid = SIZE_HUGE;
      break;
    case CREATURE_SIZE_BEHEMOTH: 
      size_sid = SIZE_BEHEMOTH;
      break;
    default:
      break;
  }
  
  return size_sid;
}

const string SizeTextKeys::SIZE = "SIZE";
const string SizeTextKeys::SIZE_TINY = "SIZE_TINY";
const string SizeTextKeys::SIZE_SMALL = "SIZE_SMALL";
const string SizeTextKeys::SIZE_MEDIUM = "SIZE_MEDIUM";
const string SizeTextKeys::SIZE_LARGE = "SIZE_LARGE";
const string SizeTextKeys::SIZE_HUGE = "SIZE_HUGE";
const string SizeTextKeys::SIZE_BEHEMOTH = "SIZE_BEHEMOTH";

// Item types
ItemTypeTextKeys::ItemTypeTextKeys()
{
}

ItemTypeTextKeys::~ItemTypeTextKeys()
{
}

const string ItemTypeTextKeys::ITEM_TYPE_MISC       = "ITEM_TYPE_MISC";
const string ItemTypeTextKeys::ITEM_TYPE_WEAPONS    = "ITEM_TYPE_WEAPONS";
const string ItemTypeTextKeys::ITEM_TYPE_ARMOURS    = "ITEM_TYPE_ARMOURS";
const string ItemTypeTextKeys::ITEM_TYPE_POTIONS    = "ITEM_TYPE_POTIONS";
const string ItemTypeTextKeys::ITEM_TYPE_BOOKS      = "ITEM_TYPE_BOOKS";
const string ItemTypeTextKeys::ITEM_TYPE_SCROLLS    = "ITEM_TYPE_SCROLLS";
const string ItemTypeTextKeys::ITEM_TYPE_WANDS      = "ITEM_TYPE_WANDS";
const string ItemTypeTextKeys::ITEM_TYPE_STAVES     = "ITEM_TYPE_STAVES";
const string ItemTypeTextKeys::ITEM_TYPE_RINGS      = "ITEM_TYPE_RINGS";
const string ItemTypeTextKeys::ITEM_TYPE_AMULETS    = "ITEM_TYPE_AMULETS";
const string ItemTypeTextKeys::ITEM_TYPE_FOOD       = "ITEM_TYPE_FOOD";
const string ItemTypeTextKeys::ITEM_TYPE_AMMUNITION = "ITEM_TYPE_AMMUNITION";
const string ItemTypeTextKeys::ITEM_TYPE_PLANTS     = "ITEM_TYPE_PLANTS";
const string ItemTypeTextKeys::ITEM_TYPE_BOATS      = "ITEM_TYPE_BOATS";
const string ItemTypeTextKeys::ITEM_TYPE_CURRENCY   = "ITEM_TYPE_CURRENCY";
const string ItemTypeTextKeys::ITEM_TYPE_TOOLS      = "ITEM_TYPE_TOOLS";

// Resistances
ResistanceTextKeys::ResistanceTextKeys()
{
}

ResistanceTextKeys::~ResistanceTextKeys()
{
}

const string ResistanceTextKeys::RESISTANCE_SLASH = "RESISTANCE_SLASH";
const string ResistanceTextKeys::RESISTANCE_POUND = "RESISTANCE_POUND";
const string ResistanceTextKeys::RESISTANCE_PIERCE = "RESISTANCE_PIERCE";
const string ResistanceTextKeys::RESISTANCE_HEAT = "RESISTANCE_HEAT";
const string ResistanceTextKeys::RESISTANCE_COLD = "RESISTANCE_COLD";
const string ResistanceTextKeys::RESISTANCE_ACID = "RESISTANCE_ACID";
const string ResistanceTextKeys::RESISTANCE_POISON = "RESISTANCE_POISON";
const string ResistanceTextKeys::RESISTANCE_HOLY = "RESISTANCE_HOLY";
const string ResistanceTextKeys::RESISTANCE_SHADOW = "RESISTANCE_SHADOW";
const string ResistanceTextKeys::RESISTANCE_ARCANE = "RESISTANCE_ARCANE";
const string ResistanceTextKeys::RESISTANCE_MENTAL = "RESISTANCE_MENTAL";
const string ResistanceTextKeys::RESISTANCE_SONIC = "RESISTANCE_SONIC";
const string ResistanceTextKeys::RESISTANCE_RADIANT = "RESISTANCE_RADIANT";
const string ResistanceTextKeys::RESISTANCE_LIGHTNING = "RESISTANCE_LIGHTNING";

// Menu titles
MenuTitleKeys::MenuTitleKeys()
{
}

MenuTitleKeys::~MenuTitleKeys()
{
}

const string MenuTitleKeys::MENU_TITLE_QUEST_LIST = "MENU_TITLE_QUEST_LIST";

// Prompts
PromptTextKeys::PromptTextKeys()
{
}

PromptTextKeys::~PromptTextKeys()
{
}

const string PromptTextKeys::PROMPT_ANY_KEY = "PROMPT_ANY_KEY";
const string PromptTextKeys::PROMPT_ENTER_YOUR_NAME = "PROMPT_ENTER_YOUR_NAME";
const string PromptTextKeys::PROMPT_RUN_SCRIPT = "PROMPT_RUN_SCRIPT";

// Special locations on the world map
WorldMapLocationTextKeys::WorldMapLocationTextKeys()
{
}

WorldMapLocationTextKeys::~WorldMapLocationTextKeys()
{
}

const string WorldMapLocationTextKeys::STARTING_LOCATION = "STARTING_LOCATION";
const string WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION = "CURRENT_PLAYER_LOCATION";

// Text keys for text related to movement in some way.
MovementTextKeys::MovementTextKeys()
{
}

MovementTextKeys::~MovementTextKeys()
{
}

const string MovementTextKeys::ACTION_MOVE_NO_EXIT               = "ACTION_MOVE_NO_EXIT";
const string MovementTextKeys::ACTION_MOVE_ADJACENT_HOSTILE_CREATURE = "ACTION_MOVE_ADJACENT_HOSTILE_CREATURE";
const string MovementTextKeys::ACTION_MOVE_OFF_WORLD_MAP         = "ACTION_MOVE_OFF_WORLD_MAP";
const string MovementTextKeys::ACTION_NO_WAY_UP_WORLD_MAP        = "ACTION_NO_WAY_UP_WORLD_MAP";
const string MovementTextKeys::ACTION_MOVE_OFF_OVERWORLD_MAP     = "ACTION_MOVE_OFF_OVERWORLD_MAP";
const string MovementTextKeys::ACTION_MOVE_OFF_UNDERWORLD_MAP    = "ACTION_MOVE_OFF_UNDERWORLD_MAP";
const string MovementTextKeys::ITEMS_ON_TILE                     = "ITEMS_ON_TILE";

// Text keys for tile extra descriptions
TileExtraDescriptionKeys::TileExtraDescriptionKeys()
{
}

TileExtraDescriptionKeys::~TileExtraDescriptionKeys()
{
}

const string TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_ISEN_DUN           = "TILE_EXTRA_DESCRIPTION_ISEN_DUN";
const string TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_ISEN_DUN_GRAVEYARD = "TILE_EXTRA_DESCRIPTION_ISEN_DUN_GRAVEYARD";
const string TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_ISEN_DUN_DUNGEON   = "TILE_EXTRA_DESCRIPTION_ISEN_DUN_DUNGEON";
const string TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_LAST_ISLAND_LAIR   = "TILE_EXTRA_DESCRIPTION_LAST_ISLAND_LAIR";
const string TileExtraDescriptionKeys::TILE_EXTRA_DESCRIPTION_WINTERSEA_KEEP     = "TILE_EXTRA_DESCRIPTION_WINTERSEA_KEEP";

// Strings for various magical effects
EffectTextKeys::EffectTextKeys()
{
}

EffectTextKeys::~EffectTextKeys()
{
}

string EffectTextKeys::get_healing_effect_message(const string& monster_desc_sid, const bool is_player)
{
  return get_general_effect_message(monster_desc_sid, is_player, EFFECT_HEALING_PLAYER, EFFECT_HEALING_MONSTER);
}

string EffectTextKeys::get_ether_effect_message(const string& monster_desc_sid, const bool is_player)
{
  return get_general_effect_message(monster_desc_sid, is_player, EFFECT_ETHER_PLAYER, EFFECT_ETHER_MONSTER);
}

string EffectTextKeys::get_general_effect_message(const string& monster_desc_sid, const bool is_player, const string& player_msg_sid, const string& monster_msg_sid)
{
  string message = StringTable::get(player_msg_sid);

  if (!is_player)
  {
    message = StringTable::get(monster_msg_sid);
    boost::replace_first(message, "%s", StringTable::get(monster_desc_sid));
    message[0] = toupper(message[0]);
  }
  
  return message;  
}

string EffectTextKeys::get_identify_individual_item_message(const string& unid_usage_desc_sid, const string& id_usage_desc_sid)
{
  string id_message = StringTable::get(EFFECT_IDENTIFY_ITEM);
  
  boost::replace_first(id_message, "%s", StringTable::get(unid_usage_desc_sid));
  boost::replace_first(id_message, "%s", StringTable::get(id_usage_desc_sid));
  
  return id_message;
}

const string EffectTextKeys::EFFECT_HEALING_PLAYER = "EFFECT_HEALING_PLAYER";
const string EffectTextKeys::EFFECT_HEALING_MONSTER = "EFFECT_HEALING_MONSTER";
const string EffectTextKeys::EFFECT_NULL = "EFFECT_NULL";
const string EffectTextKeys::EFFECT_SWEET_TASTE = "EFFECT_SWEET_TASTE";
const string EffectTextKeys::EFFECT_FRUIT_JUICE = "EFFECT_FRUIT_JUICE";
const string EffectTextKeys::EFFECT_IDENTIFY_ALL_ITEMS = "EFFECT_IDENTIFY_ALL_ITEMS";
const string EffectTextKeys::EFFECT_IDENTIFY_TYPE = "EFFECT_IDENTIFY_TYPE";
const string EffectTextKeys::EFFECT_IDENTIFY_ITEM = "EFFECT_IDENTIFY_ITEM";
const string EffectTextKeys::EFFECT_ETHER_PLAYER = "EFFECT_ETHER_PLAYER";
const string EffectTextKeys::EFFECT_ETHER_MONSTER = "EFFECT_ETHER_MONSTER";

// Confirmation messages for moving on to dangerous tiles
TileDangerConfirmationKeys::TileDangerConfirmationKeys()
{
}

TileDangerConfirmationKeys::~TileDangerConfirmationKeys()
{
}

const string TileDangerConfirmationKeys::TILE_DANGER_MOUNTAINS = "TILE_DANGER_MOUNTAINS";

// Strings for deity actions, such as being pleased, displeased, a

// Strings for Prayer
DeityTextKeys::DeityTextKeys()
{
}

DeityTextKeys::~DeityTextKeys()
{
}

string DeityTextKeys::get_prayer_message(const string& deity_sid)
{
  string prayer_message = StringTable::get(DeityTextKeys::PRAYER_INITIAL_MESSAGE);
  boost::replace_first(prayer_message, "%s", StringTable::get(deity_sid));
  
  return prayer_message;
}

const string DeityTextKeys::PRAYER_INITIAL_MESSAGE  = "PRAYER_INITIAL_MESSAGE";
const string DeityTextKeys::PRAYER_DO_NOTHING       = "PRAYER_DO_NOTHING";
const string DeityTextKeys::PRAYER_FULL_HP          = "PRAYER_FULL_HP";
const string DeityTextKeys::DEITY_ACTION_DISPLEASED = "DEITY_ACTION_DISPLEASED"; 
