#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include "StringTable.hpp"
#include "StringConstants.hpp"

using namespace std;

TextKeys::TextKeys()
{
}

TextKeys::~TextKeys()
{
}

string TextKeys::SL_TITLE    = "SL_TITLE";
string TextKeys::SL_TITLE_POEM = "SL_TITLE_POEM";
string TextKeys::COPYRIGHT_NOTICE = "COPYRIGHT_NOTICE";
string TextKeys::DEATH_MESSAGE = "DEATH_MESSAGE";
string TextKeys::DEFAULT_PLAYER_NAME = "DEFAULT_PLAYER_NAME";
string TextKeys::SELECT_RACE = "SELECT_RACE";
string TextKeys::SELECT_CLASS = "SELECT_CLASS";
string TextKeys::SELECT_DEITY = "SELECT_DEITY";
string TextKeys::AGE = "AGE";
string TextKeys::SEX = "SEX";
string TextKeys::HAIR_COLOUR = "HAIR_COLOUR";
string TextKeys::EYE_COLOUR = "EYE_COLOUR";
string TextKeys::SELECT_SEX = "SELECT_SEX";
string TextKeys::SEX_MALE = "SEX_MALE";
string TextKeys::SEX_FEMALE = "SEX_FEMALE";

string TextKeys::RACE_1_NAME = "RACE_1_NAME";
string TextKeys::RACE_1_SHORT_DESC = "RACE_1_SHORT_DESC";
string TextKeys::RACE_1_DESC = "RACE_1_DESC";
string TextKeys::RACE_2_NAME = "RACE_2_NAME";
string TextKeys::RACE_2_SHORT_DESC = "RACE_2_SHORT_DESC";
string TextKeys::RACE_2_DESC = "RACE_2_DESC";
string TextKeys::RACE_3_NAME = "RACE_3_NAME";
string TextKeys::RACE_3_SHORT_DESC = "RACE_3_SHORT_DESC";
string TextKeys::RACE_3_DESC = "RACE_3_DESC";
string TextKeys::RACE_4_NAME = "RACE_4_NAME";
string TextKeys::RACE_4_SHORT_DESC = "RACE_4_SHORT_DESC";
string TextKeys::RACE_4_DESC = "RACE_4_DESC";
string TextKeys::RACE_5_NAME = "RACE_5_NAME";
string TextKeys::RACE_5_SHORT_DESC = "RACE_5_SHORT_DESC";
string TextKeys::RACE_5_DESC = "RACE_5_DESC";
string TextKeys::RACE_6_NAME = "RACE_6_NAME";
string TextKeys::RACE_6_SHORT_DESC = "RACE_6_SHORT_DESC";
string TextKeys::RACE_6_DESC = "RACE_6_DESC";
string TextKeys::RACE_7_NAME = "RACE_7_NAME";
string TextKeys::RACE_7_SHORT_DESC = "RACE_7_SHORT_DESC";
string TextKeys::RACE_7_DESC = "RACE_7_DESC";
string TextKeys::RACE_8_NAME = "RACE_8_NAME";
string TextKeys::RACE_8_SHORT_DESC = "RACE_8_SHORT_DESC";
string TextKeys::RACE_8_DESC = "RACE_8_DESC";
string TextKeys::RACE_9_NAME = "RACE_9_NAME";
string TextKeys::RACE_9_SHORT_DESC = "RACE_9_SHORT_DESC";
string TextKeys::RACE_9_DESC = "RACE_8_DESC";
string TextKeys::RACE_10_NAME = "RACE_10_NAME";
string TextKeys::RACE_10_SHORT_DESC = "RACE_10_SHORT_DESC";
string TextKeys::RACE_10_DESC = "RACE_10_DESC";

string TextKeys::STRENGTH          = "STRENGTH";
string TextKeys::STRENGTH_ABRV     = "STRENGTH_ABRV";
string TextKeys::DEXTERITY         = "DEXTERITY";
string TextKeys::DEXTERITY_ABRV    = "DEXTERITY_ABRV";
string TextKeys::AGILITY           = "AGILITY";
string TextKeys::AGILITY_ABRV      = "AGILITY_ABRV";
string TextKeys::HEALTH            = "HEALTH";
string TextKeys::HEALTH_ABRV       = "HEALTH_ABRV";
string TextKeys::INTELLIGENCE      = "INTELLIGENCE";
string TextKeys::INTELLIGENCE_ABRV = "INTELLIGENCE_ABRV";
string TextKeys::WILLPOWER         = "WILLPOWER";
string TextKeys::WILLPOWER_ABRV    = "WILLPOWER_ABRV";
string TextKeys::CHARISMA          = "CHARISMA";
string TextKeys::CHARISMA_ABRV     = "CHARISMA_ABRV";

string TextKeys::VALOUR            = "VALOUR";
string TextKeys::VALOUR_ABRV       = "VALOUR_ABRV";
string TextKeys::SPIRIT            = "SPIRIT";
string TextKeys::SPIRIT_ABRV       = "SPIRIT_ABRV";
string TextKeys::SPEED             = "SPEED";
string TextKeys::SPEED_ABRV        = "SPEED_ABRV";

string TextKeys::HIT_POINTS        = "HIT_POINTS";
string TextKeys::HIT_POINTS_ABRV   = "HIT_POINTS_ABRV";
string TextKeys::ARCANA_POINTS     = "ARCANA_POINTS";
string TextKeys::ARCANA_POINTS_ABRV = "ARCANA_POINTS_ABRV";

string TextKeys::EVADE             = "EVADE";
string TextKeys::EVADE_ABRV        = "EVADE_ABRV";
string TextKeys::SOAK              = "SOAK";
string TextKeys::SOAK_ABRV         = "SOAK_ABRV";

string TextKeys::LEVEL             = "LEVEL";
string TextKeys::LEVEL_ABRV        = "LEVEL_ABRV";

string TextKeys::DAMAGE_MELEE      = "DAMAGE_MELEE";
string TextKeys::DAMAGE_RANGED     = "DAMAGE_RANGED";

string TextKeys::EQUIPMENT         = "EQUIPMENT";
string TextKeys::EQUIPMENT_PROMPT  = "EQUIPMENT_PROMPT";
string TextKeys::INVENTORY         = "INVENTORY";
string TextKeys::INVENTORY_PROMPT  = "INVENTORY_PROMPT";

string TextKeys::DECISION_CONFIRM_KEY = "DECISION_CONFIRM_KEY";
string TextKeys::DECISION_DENY_KEY = "DECISION_DENY_KEY";
string TextKeys::DECISION_LEAVE_AREA = "DECISION_LEAVE_AREA";
string TextKeys::DECISION_QUIT_GAME = "DECISION_QUIT_GAME";

// Materials
MaterialTextKeys::MaterialTextKeys()
{
}

MaterialTextKeys::~MaterialTextKeys()
{
}

string MaterialTextKeys::MATERIAL_CLOTH        = "MATERIAL_CLOTH";
string MaterialTextKeys::MATERIAL_DRAGON_SCALE = "MATERIAL_DRAGON_SCALE";
string MaterialTextKeys::MATERIAL_GLASS        = "MATERIAL_GLASS";
string MaterialTextKeys::MATERIAL_IRON         = "MATERIAL_IRON";
string MaterialTextKeys::MATERIAL_LEATHER      = "MATERIAL_LEATHER";
string MaterialTextKeys::MATERIAL_PAPER        = "MATERIAL_PAPER";
string MaterialTextKeys::MATERIAL_STEEL        = "MATERIAL_STEEL";
string MaterialTextKeys::MATERIAL_STONE        = "MATERIAL_STONE";
string MaterialTextKeys::MATERIAL_WOOD         = "MATERIAL_WOOD";
string MaterialTextKeys::MATERIAL_MARBLE       = "MATERIAL_MARBLE";
string MaterialTextKeys::MATERIAL_ONYX         = "MATERIAL_ONYX";

// Entrance
EntranceTextKeys::EntranceTextKeys()
{
}

EntranceTextKeys::~EntranceTextKeys()
{
}

string EntranceTextKeys::ENTRANCE_FIELD           = "ENTRANCE_FIELD";
string EntranceTextKeys::ENTRANCE_SCRUB           = "ENTRANCE_SCRUB";
string EntranceTextKeys::ENTRANCE_DESERT          = "ENTRANCE_DESERT";
string EntranceTextKeys::ENTRANCE_MOUNTAINS       = "ENTRANCE_MOUNTAINS";
string EntranceTextKeys::ENTRANCE_SEA             = "ENTRANCE_SEA";
string EntranceTextKeys::ENTRANCE_FOREST          = "ENTRANCE_FOREST";
string EntranceTextKeys::ENTRANCE_MARSH           = "ENTRANCE_MARSH";
string EntranceTextKeys::ENTRANCE_HILLS           = "ENTRANCE_HILLS";
string EntranceTextKeys::ENTRANCE_CAVERN          = "ENTRANCE_CAVERN";
string EntranceTextKeys::ENTRANCE_VILLAGE         = "ENTRANCE_VILLAGE";
string EntranceTextKeys::ENTRANCE_DUNGEON_COMPLEX = "ENTRANCE_DUNGEON_COMPLEX";
string EntranceTextKeys::ENTRANCE_BARRACKS        = "ENTRANCE_BARRACKS";
string EntranceTextKeys::ENTRANCE_CASTLE          = "ENTRANCE_CASTLE";
string EntranceTextKeys::ENTRANCE_CHURCH          = "ENTRANCE_CHURCH";
string EntranceTextKeys::ENTRANCE_GRAVEYARD       = "ENTRANCE_GRAVEYARD";
string EntranceTextKeys::ENTRANCE_KEEP            = "ENTRANCE_KEEP";
string EntranceTextKeys::ENTRANCE_LIBRARY         = "ENTRANCE_LIBRARY";
string EntranceTextKeys::ENTRANCE_SITE_OF_DEATH   = "ENTRANCE_SITE_OF_DEATH";
string EntranceTextKeys::ENTRANCE_TEMPLE          = "ENTRANCE_TEMPLE";

// Equipment
EquipmentTextKeys::EquipmentTextKeys()
{
}

string EquipmentTextKeys::EQUIPMENT_HEAD         = "EQUIPMENT_HEAD";
string EquipmentTextKeys::EQUIPMENT_NECK         = "EQUIPMENT_NECK";
string EquipmentTextKeys::EQUIPMENT_RIGHT_FINGER = "EQUIPMENT_RIGHT_FINGER";
string EquipmentTextKeys::EQUIPMENT_LEFT_FINGER  = "EQUIPMENT_LEFT_FINGER";
string EquipmentTextKeys::EQUIPMENT_RIGHT_HAND   = "EQUIPMENT_RIGHT_HAND";
string EquipmentTextKeys::EQUIPMENT_LEFT_HAND    = "EQUIPMENT_LEFT_HAND";
string EquipmentTextKeys::EQUIPMENT_BODY         = "EQUIPMENT_BODY";
string EquipmentTextKeys::EQUIPMENT_ABOUT_BODY   = "EQUIPMENT_ABOUT_BODY";
string EquipmentTextKeys::EQUIPMENT_FEET         = "EQUIPMENT_FEET";

string EquipmentTextKeys::get_equipment_text_from_given_worn_location(const EquipmentWornLocation& worn_location)
{
  string equipment_text;
  string equipment_text_sid;
  
  switch(worn_location)
  {
    case EQUIPMENT_WORN_HEAD:
      equipment_text_sid = EQUIPMENT_HEAD;
      break;
    case EQUIPMENT_WORN_NECK:
      equipment_text_sid = EQUIPMENT_NECK;
      break;
    case EQUIPMENT_WORN_RIGHT_FINGER:
      equipment_text_sid = EQUIPMENT_RIGHT_FINGER;
      break;
    case EQUIPMENT_WORN_LEFT_FINGER:
      equipment_text_sid = EQUIPMENT_LEFT_FINGER;
      break;
    case EQUIPMENT_WORN_RIGHT_HAND:
      equipment_text_sid = EQUIPMENT_RIGHT_HAND;
      break;
    case EQUIPMENT_WORN_LEFT_HAND:
      equipment_text_sid = EQUIPMENT_LEFT_HAND;
      break;
    case EQUIPMENT_WORN_BODY:
      equipment_text_sid = EQUIPMENT_BODY;
      break;
    case EQUIPMENT_WORN_ABOUT_BODY:
      equipment_text_sid = EQUIPMENT_ABOUT_BODY;
      break;
    case EQUIPMENT_WORN_FEET:
      equipment_text_sid = EQUIPMENT_FEET;
      break;
    case EQUIPMENT_WORN_NONE:
    case EQUIPMENT_WORN_LAST:
    default:
      break;
  }
  
  equipment_text = StringTable::get(equipment_text_sid);
  return equipment_text;
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

string ColourTextKeys::COLOUR_BLACK = "COLOUR_BLACK";
string ColourTextKeys::COLOUR_BROWN = "COLOUR_BROWN";
string ColourTextKeys::COLOUR_BLONDE = "COLOUR_BLONDE";
string ColourTextKeys::COLOUR_RED = "COLOUR_RED";
string ColourTextKeys::COLOUR_GREEN = "COLOUR_GREEN";
string ColourTextKeys::COLOUR_HAZEL = "COLOUR_HAZEL";
string ColourTextKeys::COLOUR_BLUE = "COLOUR_BLUE";
string ColourTextKeys::COLOUR_GREY = "COLOUR_GREY";
string ColourTextKeys::COLOUR_WHITE = "COLOUR_WHITE";


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

string SizeTextKeys::SIZE = "SIZE";
string SizeTextKeys::SIZE_TINY = "SIZE_TINY";
string SizeTextKeys::SIZE_SMALL = "SIZE_SMALL";
string SizeTextKeys::SIZE_MEDIUM = "SIZE_MEDIUM";
string SizeTextKeys::SIZE_LARGE = "SIZE_LARGE";
string SizeTextKeys::SIZE_HUGE = "SIZE_HUGE";
string SizeTextKeys::SIZE_BEHEMOTH = "SIZE_BEHEMOTH";

SkillTextKeys::SkillTextKeys()
{
}

SkillTextKeys::~SkillTextKeys()
{
}

// SkillTextKeys
// General (NWP)
string SkillTextKeys::SKILLS_GENERAL = "SKILLS_GENERAL";
string SkillTextKeys::SKILL_GENERAL_ARCHERY = "SKILL_GENERAL_ARCHERY";
string SkillTextKeys::SKILL_GENERAL_AWARENESS = "SKILL_GENERAL_AWARENESS";
string SkillTextKeys::SKILL_GENERAL_BARGAINING = "SKILL_GENERAL_BARGAINING";
string SkillTextKeys::SKILL_GENERAL_BEASTMASTERY = "SKILL_GENERAL_BEASTMASTERY";
string SkillTextKeys::SKILL_GENERAL_BLIND_FIGHTING = "SKILL_GENERAL_BLIND_FIGHTING";
string SkillTextKeys::SKILL_GENERAL_BOATING = "SKILL_GENERAL_BOATING";
string SkillTextKeys::SKILL_GENERAL_BOWYER = "SKILL_GENERAL_BOWYER";
string SkillTextKeys::SKILL_GENERAL_BREWING = "SKILL_GENERAL_BREWING";
string SkillTextKeys::SKILL_GENERAL_CANTRIPS = "SKILL_GENERAL_CANTRIPS";
string SkillTextKeys::SKILL_GENERAL_CARRYING = "SKILL_GENERAL_CARRYING";
string SkillTextKeys::SKILL_GENERAL_COMBAT = "SKILL_GENERAL_COMBAT";
string SkillTextKeys::SKILL_GENERAL_CRAFTING = "SKILL_GENERAL_CRAFTING";
string SkillTextKeys::SKILL_GENERAL_DESERT_LORE = "SKILL_GENERAL_DESERT_LORE";
string SkillTextKeys::SKILL_GENERAL_DETECTION = "SKILL_GENERAL_DETECTION";
string SkillTextKeys::SKILL_GENERAL_DISARM_TRAPS = "SKILL_GENERAL_DISARM_TRAPS";
string SkillTextKeys::SKILL_GENERAL_DUAL_WIELD = "SKILL_GENERAL_DUAL_WIELD";
string SkillTextKeys::SKILL_GENERAL_DUNGEONEERING = "SKILL_GENERAL_DUNGEONEERING";
string SkillTextKeys::SKILL_GENERAL_ESCAPE = "SKILL_GENERAL_ESCAPE";
string SkillTextKeys::SKILL_GENERAL_FORAGING = "SKILL_GENERAL_ESCAPE";
string SkillTextKeys::SKILL_GENERAL_FOREST_LORE = "SKILL_GENERAL_FOREST_LORE";
string SkillTextKeys::SKILL_GENERAL_FISHING = "SKILL_GENERAL_FISHING";
string SkillTextKeys::SKILL_GENERAL_FLETCHERY = "SKILL_GENERAL_FLETCHERY";
string SkillTextKeys::SKILL_GENERAL_HERBALISM = "SKILL_GENERAL_HERBALISM";
string SkillTextKeys::SKILL_GENERAL_HIDING = "SKILL_GENERAL_HIDING";
string SkillTextKeys::SKILL_GENERAL_HUNTING = "SKILL_GENERAL_HUNTING";
string SkillTextKeys::SKILL_GENERAL_INTIMIDATION = "SKILL_GENERAL_INTIMIDATION";
string SkillTextKeys::SKILL_GENERAL_JEWELER = "SKILL_GENERAL_JEWELER";
string SkillTextKeys::SKILL_GENERAL_JUMPING = "SKILL_GENERAL_JUMPING";
string SkillTextKeys::SKILL_GENERAL_LEADERSHIP = "SKILL_GENERAL_LEADERSHIP";
string SkillTextKeys::SKILL_GENERAL_LITERACY = "SKILL_GENERAL_LITERACY";
string SkillTextKeys::SKILL_GENERAL_LORE = "SKILL_GENERAL_LORE";
string SkillTextKeys::SKILL_GENERAL_MAGIC = "SKILL_GENERAL_MAGIC";
string SkillTextKeys::SKILL_GENERAL_MARSH_LORE = "SKILL_GENERAL_MARSH_LORE";
string SkillTextKeys::SKILL_GENERAL_MEDICINE = "SKILL_GENERAL_MEDICINE";
string SkillTextKeys::SKILL_GENERAL_MOUNTAIN_LORE = "SKILL_GENERAL_MOUNTAIN_LORE";
string SkillTextKeys::SKILL_GENERAL_MOUNTAINEERING = "SKILL_GENERAL_MOUNTAINEERING";
string SkillTextKeys::SKILL_GENERAL_MUSIC = "SKILL_GENERAL_MUSIC";
string SkillTextKeys::SKILL_GENERAL_NIGHT_SIGHT = "SKILL_GENERAL_NIGHT_SIGHT";
string SkillTextKeys::SKILL_GENERAL_OCEANOGRAPHY = "SKILL_GENERAL_OCEANOGRAPHY";
string SkillTextKeys::SKILL_GENERAL_PAPERCRAFT = "SKILL_GENERAL_PAPERCRAFT";
string SkillTextKeys::SKILL_GENERAL_RELIGION = "SKILL_GENERAL_RELIGION";
string SkillTextKeys::SKILL_GENERAL_SCRIBING = "SKILL_GENERAL_SCRIBING";
string SkillTextKeys::SKILL_GENERAL_SKINNING = "SKILL_GENERAL_SKINNING";
string SkillTextKeys::SKILL_GENERAL_SMITHING = "SKILL_GENERAL_SMITHING";
string SkillTextKeys::SKILL_GENERAL_SPELUNKING = "SKILL_GENERAL_SPELUNKING";
string SkillTextKeys::SKILL_GENERAL_STEALTH = "SKILL_GENERAL_STEALTH";
string SkillTextKeys::SKILL_GENERAL_SWIMMING = "SKILL_GENERAL_SWIMMING";
string SkillTextKeys::SKILL_GENERAL_TANNING = "SKILL_GENERAL_TANNING";
string SkillTextKeys::SKILL_GENERAL_THIEVERY = "SKILL_GENERAL_THIEVERY";
string SkillTextKeys::SKILL_GENERAL_WEAVING = "SKILL_GENERAL_WEAVING";

// Weapon (Melee)
string SkillTextKeys::SKILLS_WEAPON = "SKILLS_WEAPON";
string SkillTextKeys::SKILL_MELEE_AXES = "SKILL_MELEE_AXES";
string SkillTextKeys::SKILL_MELEE_SHORT_BLADES = "SKILL_MELEE_SHORT_BLADES";
string SkillTextKeys::SKILL_MELEE_LONG_BLADES = "SKILL_MELEE_LONG_BLADES";
string SkillTextKeys::SKILL_MELEE_BLUDGEONS = "SKILL_MELEE_BLUDGEONS";
string SkillTextKeys::SKILL_MELEE_DAGGERS = "SKILL_MELEE_DAGGERS";
string SkillTextKeys::SKILL_MELEE_RODS_AND_STAVES = "SKILL_MELEE_RODS_AND_STAVES";
string SkillTextKeys::SKILL_MELEE_SPEARS = "SKILL_MELEE_SPEARS";
string SkillTextKeys::SKILL_MELEE_UNARMED = "SKILL_MELEE_UNARMED";
string SkillTextKeys::SKILL_MELEE_WHIPS = "SKILL_MELEE_WHIPS";

// Weapon (Ranged)
string SkillTextKeys::SKILLS_RANGED_WEAPON = "SKILLS_RANGED_WEAPON";
string SkillTextKeys::SKILL_RANGED_AXES = "SKILL_RANGED_AXES";
string SkillTextKeys::SKILL_RANGED_BLADES = "SKILL_RANGED_BLADES";
string SkillTextKeys::SKILL_RANGED_BLUDGEONS = "SKILL_RANGED_BLUDGEONS";
string SkillTextKeys::SKILL_RANGED_BOWS = "SKILL_RANGED_BOWS";
string SkillTextKeys::SKILL_RANGED_CROSSBOWS = "SKILL_RANGED_CROSSBOWS";
string SkillTextKeys::SKILL_RANGED_DAGGERS = "SKILL_RANGED_DAGGERS";
string SkillTextKeys::SKILL_RANGED_ROCKS = "SKILL_RANGED_ROCKS";
string SkillTextKeys::SKILL_RANGED_SLINGS = "SKILL_RANGED_SLINGS";
string SkillTextKeys::SKILL_RANGED_SPEARS = "SKILL_RANGED_SPEARS";

// Magic
string SkillTextKeys::SKILLS_MAGIC = "SKILLS_MAGIC";
string SkillTextKeys::SKILL_MAGIC_ARCANE = "SKILL_MAGIC_ARCANE";
string SkillTextKeys::SKILL_MAGIC_DIVINE = "SKILL_MAGIC_DIVINE";
string SkillTextKeys::SKILL_MAGIC_MYSTIC = "SKILL_MAGIC_MYSTIC";
string SkillTextKeys::SKILL_MAGIC_PRIMORDIAL = "SKILL_MAGIC_PRIMORDIAL";

// Item types
ItemTypeTextKeys::ItemTypeTextKeys()
{
}

ItemTypeTextKeys::~ItemTypeTextKeys()
{
}

string ItemTypeTextKeys::ITEM_TYPE_MISC       = "ITEM_TYPE_MISC";
string ItemTypeTextKeys::ITEM_TYPE_WEAPONS    = "ITEM_TYPE_WEAPONS";
string ItemTypeTextKeys::ITEM_TYPE_ARMOURS    = "ITEM_TYPE_ARMOURS";
string ItemTypeTextKeys::ITEM_TYPE_POTIONS    = "ITEM_TYPE_POTIONS";
string ItemTypeTextKeys::ITEM_TYPE_BOOKS      = "ITEM_TYPE_BOOKS";
string ItemTypeTextKeys::ITEM_TYPE_SCROLLS    = "ITEM_TYPE_SCROLLS";
string ItemTypeTextKeys::ITEM_TYPE_WANDS      = "ITEM_TYPE_WANDS";
string ItemTypeTextKeys::ITEM_TYPE_STAVES     = "ITEM_TYPE_STAVES";
string ItemTypeTextKeys::ITEM_TYPE_RINGS      = "ITEM_TYPE_RINGS";
string ItemTypeTextKeys::ITEM_TYPE_AMULETS    = "ITEM_TYPE_AMULETS";
string ItemTypeTextKeys::ITEM_TYPE_FOOD       = "ITEM_TYPE_FOOD";
string ItemTypeTextKeys::ITEM_TYPE_AMMUNITION = "ITEM_TYPE_AMMUNITION";

// Resistances
ResistanceTextKeys::ResistanceTextKeys()
{
}

ResistanceTextKeys::~ResistanceTextKeys()
{
}

string ResistanceTextKeys::RESISTANCE_SLASH = "RESISTANCE_SLASH";
string ResistanceTextKeys::RESISTANCE_POUND = "RESISTANCE_POUND";
string ResistanceTextKeys::RESISTANCE_PIERCE = "RESISTANCE_PIERCE";
string ResistanceTextKeys::RESISTANCE_HEAT = "RESISTANCE_HEAT";
string ResistanceTextKeys::RESISTANCE_COLD = "RESISTANCE_COLD";
string ResistanceTextKeys::RESISTANCE_ACID = "RESISTANCE_ACID";
string ResistanceTextKeys::RESISTANCE_POISON = "RESISTANCE_POISON";
string ResistanceTextKeys::RESISTANCE_HOLY = "RESISTANCE_HOLY";
string ResistanceTextKeys::RESISTANCE_SHADOW = "RESISTANCE_SHADOW";
string ResistanceTextKeys::RESISTANCE_ARCANE = "RESISTANCE_ARCANE";
string ResistanceTextKeys::RESISTANCE_MENTAL = "RESISTANCE_MENTAL";
string ResistanceTextKeys::RESISTANCE_SONIC = "RESISTANCE_SONIC";
string ResistanceTextKeys::RESISTANCE_RADIANT = "RESISTANCE_RADIANT";
string ResistanceTextKeys::RESISTANCE_LIGHTNING = "RESISTANCE_LIGHTNING";

// Prompts
PromptTextKeys::PromptTextKeys()
{
}

PromptTextKeys::~PromptTextKeys()
{
}

string PromptTextKeys::PROMPT_ANY_KEY = "PROMPT_ANY_KEY";
string PromptTextKeys::PROMPT_ENTER_YOUR_NAME = "PROMPT_ENTER_YOUR_NAME";

// Special locations on the world map
WorldMapLocationTextKeys::WorldMapLocationTextKeys()
{
}

WorldMapLocationTextKeys::~WorldMapLocationTextKeys()
{
}

string WorldMapLocationTextKeys::STARTING_LOCATION = "STARTING_LOCATION";
string WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION = "CURRENT_PLAYER_LOCATION";

// Text keys for text related to movement in some way.
MovementTextKeys::MovementTextKeys()
{
}

MovementTextKeys::~MovementTextKeys()
{
}

string MovementTextKeys::ACTION_MOVE_NO_EXIT               = "ACTION_MOVE_NO_EXIT";
string MovementTextKeys::ACTION_MOVE_OFF_WORLD_MAP         = "ACTION_MOVE_OFF_WORLD_MAP";
string MovementTextKeys::ACTION_NO_WAY_UP_WORLD_MAP        = "ACTION_NO_WAY_UP_WORLD_MAP";
string MovementTextKeys::ACTION_MOVE_OFF_OVERWORLD_MAP     = "ACTION_MOVE_OFF_OVERWORLD_MAP";
string MovementTextKeys::ACTION_MOVE_OFF_UNDERWORLD_MAP    = "ACTION_MOVE_OFF_UNDERWORLD_MAP";
string MovementTextKeys::ITEMS_ON_TILE                     = "ITEMS_ON_TILE";

// Text keys for descriptions of tiles
TileTextKeys::TileTextKeys()
{
}

TileTextKeys::~TileTextKeys()
{
}

string TileTextKeys::TILE_DESC_BEACH          = "TILE_DESC_BEACH";
string TileTextKeys::TILE_DESC_BUSH           = "TILE_DESC_BUSH";
string TileTextKeys::TILE_DESC_CAIRN          = "TILE_DESC_CAIRN";
string TileTextKeys::TILE_DESC_CAVERN         = "TILE_DESC_CAVERN";
string TileTextKeys::TILE_DESC_DESERT         = "TILE_DESC_DESERT";
string TileTextKeys::TILE_DESC_DUNGEON        = "TILE_DESC_DUNGEON";
string TileTextKeys::TILE_DESC_DUNGEON_COMPLEX = "TILE_DESC_DUNGEON_COMPLEX";
string TileTextKeys::TILE_DESC_FIELD          = "TILE_DESC_FIELD";
string TileTextKeys::TILE_DESC_FOREST         = "TILE_DESC_FOREST";
string TileTextKeys::TILE_DESC_GRAVE          = "TILE_DESC_GRAVE";
string TileTextKeys::TILE_DESC_HILLS          = "TILE_DESC_HILLS";
string TileTextKeys::TILE_DESC_MARSH          = "TILE_DESC_MARSH";
string TileTextKeys::TILE_DESC_MOUNTAINS      = "TILE_DESC_MOUNTAINS";
string TileTextKeys::TILE_DESC_REEDS          = "TILE_DESC_REEDS";
string TileTextKeys::TILE_DESC_RIVER          = "TILE_DESC_RIVER";
string TileTextKeys::TILE_DESC_ROAD           = "TILE_DESC_ROAD";
string TileTextKeys::TILE_DESC_ROCK           = "TILE_DESC_ROCK";
string TileTextKeys::TILE_DESC_UP_STAIRCASE   = "TILE_DESC_UP_STAIRCASE";
string TileTextKeys::TILE_DESC_DOWN_STAIRCASE = "TILE_DESC_DOWN_STAIRCASE"; 
string TileTextKeys::TILE_DESC_SCRUB          = "TILE_DESC_SCRUB";
string TileTextKeys::TILE_DESC_SEA            = "TILE_DESC_SEA";
string TileTextKeys::TILE_DESC_SHOALS         = "TILE_DESC_SHOALS";
string TileTextKeys::TILE_DESC_SPRINGS        = "TILE_DESC_SPRINGS";
string TileTextKeys::TILE_DESC_TREE           = "TILE_DESC_TREE";
string TileTextKeys::TILE_DESC_VILLAGE        = "TILE_DESC_VILLAGE";
string TileTextKeys::TILE_DESC_WEEDS          = "TILE_DESC_WEEDS";
string TileTextKeys::TILE_DESC_WHEAT          = "TILE_DESC_WHEAT";
string TileTextKeys::TILE_DESC_BARRACKS       = "TILE_DESC_BARRACKS";
string TileTextKeys::TILE_DESC_CASTLE         = "TILE_DESC_CASTLE";
string TileTextKeys::TILE_DESC_CHURCH         = "TILE_DESC_CHURCH";
string TileTextKeys::TILE_DESC_GRAVEYARD      = "TILE_DESC_GRAVEYARD";
string TileTextKeys::TILE_DESC_KEEP           = "TILE_DESC_KEEP";
string TileTextKeys::TILE_DESC_LIBRARY        = "TILE_DESC_LIBRARY";
string TileTextKeys::TILE_DESC_SITE_OF_DEATH  = "TILE_DESC_SITE_OF_DEATH";
string TileTextKeys::TILE_DESC_TEMPLE         = "TILE_DESC_TEMPLE";
string TileTextKeys::TILE_DESC_DAIS           = "TILE_DESC_DAIS";

// Text keys for player/creature actions
ActionTextKeys::ActionTextKeys()
{
}

ActionTextKeys::~ActionTextKeys()
{
}

string ActionTextKeys::ACTION_NOT_FOUND                  = "ACTION_NOT_FOUND";
string ActionTextKeys::ACTION_SEARCH                     = "ACTION_SEARCH";
string ActionTextKeys::ACTION_PICK_UP_NOT_ALLOWED        = "ACTION_PICK_UP_NOT_ALLOWED";
string ActionTextKeys::ACTION_DROP_NOT_ALLOWED           = "ACTION_DROP_NOT_ALLOWED";
string ActionTextKeys::ACTION_DROP_NO_ITEM_SELECTED      = "ACTION_DROP_NO_ITEM_SELECTED";
string ActionTextKeys::ACTION_PICK_UP_NOTHING_ON_GROUND  = "ACTION_PICK_UP_NOTHING_ON_GROUND";
string ActionTextKeys::ACTION_MOVEMENT_BLOCKED           = "ACTION_MOVEMENT_BLOCKED";

// Messages that can be sent to the user in the message buffer
TextMessages::TextMessages()
{
}

TextMessages::~TextMessages()
{
}

string TextMessages::WELCOME_MESSAGE                    = "WELCOME_MESSAGE";
string TextMessages::DUMPING_CHARACTER_MESSAGE          = "DUMPING_CHARACTER_MESSAGE";
string TextMessages::ITEM_DROP_MESSAGE                  = "ITEM_DROP_MESSAGE";
string TextMessages::ITEM_PICK_UP_MESSAGE               = "ITEM_PICK_UP_MESSAGE";
string TextMessages::ITEM_ON_GROUND_DESCRIPTION_MESSAGE = "ITEM_ON_GROUND_DESCRIPTION_MESSAGE";

// Public functions used to access protected members.  These are used to wrap any strings
// that contain replaceable symbols.
string TextMessages::get_welcome_message(const string& player_name)
{
  string welcome_message = StringTable::get(TextMessages::WELCOME_MESSAGE);
  boost::replace_first(welcome_message, "%s", player_name);
  return welcome_message;
}

// Gets the overall death message.  This is the deity's message plus
// "You die..." (or equivalent)
string TextMessages::get_death_message(const string& deity_death_message_sid)
{
  string deity_death_message = StringTable::get(deity_death_message_sid);
  string you_die = StringTable::get(TextKeys::DEATH_MESSAGE);
  string death_message = deity_death_message + "  " + you_die;
  return death_message;
}

string TextMessages::get_action_not_found_message(const string& command_action)
{
  string action_message = StringTable::get(ActionTextKeys::ACTION_NOT_FOUND);
  boost::replace_first(action_message, "%s", command_action);
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
    case CREATURE_SEX_MALE:
      creature_sex = StringTable::get(TextKeys::SEX_MALE);
      break;
    case CREATURE_SEX_FEMALE:
      creature_sex = StringTable::get(TextKeys::SEX_FEMALE);
      break;
    default:
      creature_sex = "?";
      break;
  }
  
  return creature_sex;
}

string TextMessages::get_equipment_location(const EquipmentWornLocation location)
{
  string equipment_location;
  
  switch(location)
  {
    case EQUIPMENT_WORN_HEAD:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_HEAD);
      break;
    case EQUIPMENT_WORN_NECK:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_NECK);
      break;
    case EQUIPMENT_WORN_RIGHT_FINGER:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_RIGHT_FINGER);
      break;
    case EQUIPMENT_WORN_LEFT_FINGER:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_LEFT_FINGER);
      break;
    case EQUIPMENT_WORN_RIGHT_HAND:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_RIGHT_HAND);
      break;
    case EQUIPMENT_WORN_LEFT_HAND:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_LEFT_HAND);
      break;
    case EQUIPMENT_WORN_BODY:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_BODY);
      break;
    case EQUIPMENT_WORN_ABOUT_BODY:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_ABOUT_BODY);
      break;
    case EQUIPMENT_WORN_FEET:
      equipment_location = StringTable::get(EquipmentTextKeys::EQUIPMENT_FEET);
      break;
    case EQUIPMENT_WORN_NONE:
    case EQUIPMENT_WORN_LAST:
    default:
      equipment_location = "?";
      break;
  }
  
  return equipment_location;
}

string TextMessages::get_confirmation_message(const string& query_sid)
{
  ostringstream ss;
  
  ss << StringTable::get(query_sid);
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
    case TILE_TYPE_FIELD:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_FIELD);
      break;
    case TILE_TYPE_SCRUB:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_SCRUB);
      break;
    case TILE_TYPE_DESERT:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_DESERT);
      break;
    case TILE_TYPE_MOUNTAINS:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_MOUNTAINS);
      break;
    case TILE_TYPE_SEA:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_SEA);
      break;
    case TILE_TYPE_FOREST:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_FOREST);
      break;
    case TILE_TYPE_MARSH:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_MARSH);
      break;
    case TILE_TYPE_HILLS:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_HILLS);
      break;
    case TILE_TYPE_CAVERN:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_CAVERN);
      break;
    case TILE_TYPE_VILLAGE:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_VILLAGE);
      break;
    case TILE_TYPE_DUNGEON_COMPLEX:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_DUNGEON_COMPLEX);
      break;
    case TILE_TYPE_BARRACKS:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_BARRACKS);
      break;
    case TILE_TYPE_CASTLE:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_CASTLE);
      break;
    case TILE_TYPE_CHURCH:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_CHURCH);
      break;
    case TILE_TYPE_GRAVEYARD:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_GRAVEYARD);
      break;
    case TILE_TYPE_KEEP:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_KEEP);
      break;
    case TILE_TYPE_LIBRARY:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_LIBRARY);
      break;
    case TILE_TYPE_SITE_OF_DEATH:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_SITE_OF_DEATH);
      break;
    case TILE_TYPE_TEMPLE:
      entrance_message = StringTable::get(EntranceTextKeys::ENTRANCE_TEMPLE);
      break;
    case TILE_TYPE_UNDEFINED:
    case TILE_TYPE_WHEAT:
    case TILE_TYPE_CAIRN:
    case TILE_TYPE_TREE:
    case TILE_TYPE_ROAD:
    case TILE_TYPE_RIVER:
    case TILE_TYPE_SHOALS:
    case TILE_TYPE_DUNGEON:
    case TILE_TYPE_ROCK:
    case TILE_TYPE_GRAVE:
    case TILE_TYPE_REEDS:
    case TILE_TYPE_BEACH:
    case TILE_TYPE_BUSH:
    case TILE_TYPE_WEEDS:
    case TILE_TYPE_SPRINGS:
    case TILE_TYPE_DAIS:
    case TILE_TYPE_UP_STAIRCASE:
    case TILE_TYPE_DOWN_STAIRCASE:
    default:
      break;
  }
  
  return entrance_message;
}

string TextMessages::get_item_drop_message(const string& item_description)
{
  string item_message = StringTable::get(TextMessages::ITEM_DROP_MESSAGE);
  boost::replace_first(item_message, "%s", item_description);
  return item_message;
  
}

string TextMessages::get_item_pick_up_message(const string& item_description)
{
  string item_message = StringTable::get(TextMessages::ITEM_PICK_UP_MESSAGE);
  boost::replace_first(item_message, "%s", item_description);
  return item_message;
}

string TextMessages::get_item_on_ground_description_message(const string& item_on_ground_description)
{
  string item_message = StringTable::get(TextMessages::ITEM_ON_GROUND_DESCRIPTION_MESSAGE);
  boost::replace_first(item_message, "%s", item_on_ground_description);
  return item_message;
}

// Descriptions of tile features
FeatureDescriptionTextKeys::FeatureDescriptionTextKeys()
{
}

string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_DOOR               = "FEATURE_DESCRIPTION_DOOR";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_EVIL_ALTAR         = "FEATURE_DESCRIPTION_EVIL_ALTAR";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_GOOD_ALTAR         = "FEATURE_DESCRIPTION_GOOD_ALTAR";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_NEUTRAL_ALTAR      = "FEATURE_DESCRIPTION_NEUTRAL_ALTAR";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FOUNTAIN           = "FEATURE_DESCRIPTION_FOUNTAIN";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_FIRE_PILLAR        = "FEATURE_DESCRIPTION_FIRE_PILLAR";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_PEW                = "FEATURE_DESCRIPTION_PEW";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KING_STATUE        = "FEATURE_DESCRIPTION_KING_STATUE";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_QUEEN_STATUE       = "FEATURE_DESCRIPTION_QUEEN_STATUE";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_WARLORD_STATUE     = "FEATURE_DESCRIPTION_WARLORD_STATUE";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_KNIGHT_STATUE      = "FEATURE_DESCRIPTION_KNIGHT_STATUE";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_HIGH_PRIEST_STATUE = "FEATURE_DESCRIPTION_HIGH_PRIEST_STATUE";
string FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SORCEROR_STATUE    = "FEATURE_DESCRIPTION_SORCEROR_STATUE";
