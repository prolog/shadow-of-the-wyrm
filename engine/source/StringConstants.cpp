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
string TextKeys::DEFAULT_PLAYER_NAME = "DEFAULT_PLAYER_NAME";
string TextKeys::SELECT_RACE = "SELECT_RACE";
string TextKeys::SELECT_CLASS = "SELECT_CLASS";

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

SkillTextKeys::SkillTextKeys()
{
}

SkillTextKeys::~SkillTextKeys()
{
}

// SkillTextKeys
// General (NWP)
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
string SkillTextKeys::SKILL_GENERAL_LITERACY = "SKILL_GENERAL_LEADERHSIP";
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
string SkillTextKeys::SKILL_MAGIC_ARCANE = "SKILL_MAGIC_ARCANE";
string SkillTextKeys::SKILL_MAGIC_DIVINE = "SKILL_MAGIC_DIVINE";
string SkillTextKeys::SKILL_MAGIC_MYSTIC = "SKILL_MAGIC_MYSTIC";
string SkillTextKeys::SKILL_MAGIC_PRIMORDIAL = "SKILL_MAGIC_PRIMORDIAL";

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

// Text keys for player/creature actions
ActionTextKeys::ActionTextKeys()
{
}

ActionTextKeys::~ActionTextKeys()
{
}

string ActionTextKeys::ACTION_SEARCH = "ACTION_SEARCH";
string ActionTextKeys::ACTION_MOVE_OFF_WORLD_MAP = "ACTION_MOVE_OFF_WORLD_MAP";

// Messages that can be sent to the user in the message buffer
TextMessages::TextMessages()
{
}

TextMessages::~TextMessages()
{
}

string TextMessages::WELCOME_MESSAGE = "WELCOME_MESSAGE";


// Public functions used to access protected members.  These are used to wrap any strings
// that contain replaceable symbols.
string TextMessages::get_welcome_message(const string& player_name)
{
  string welcome_message = StringTable::get(TextMessages::WELCOME_MESSAGE);
  boost::replace_first(welcome_message, "%s", player_name);
  return welcome_message;
}
