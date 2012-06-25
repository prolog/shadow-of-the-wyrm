#pragma once
#include <map>
#include <string>
#include "CreatureFeatures.hpp"
#include "DamageTypes.hpp"
#include "Date.hpp"
#include "EquipmentTypes.hpp"
#include "tiles.hpp"

// String constants related to the player.
// Note that these are actual string constants that are not meant to be text keys.
class PlayerConstants
{
  public:
    static const std::string PLAYER_CREATURE_ID;
    
  protected:
    PlayerConstants();
    ~PlayerConstants();
};

// These define all the string keys.
// Key/value pairs are defined in savagelandstext_lang.ini, where lang=en,fr,ru,kl,etc.
class TextKeys
{
  public:
    static const std::string SL_TITLE;
    static const std::string SL_TITLE_POEM;
    static const std::string COPYRIGHT_NOTICE;
    static const std::string DEATH_MESSAGE;
    static const std::string DEFAULT_PLAYER_NAME;
    static const std::string YOU;
    static const std::string NPC_ESCAPES_MESSAGE;
    static const std::string SEX;
    static const std::string SELECT_SEX;
    static const std::string SEX_MALE;
    static const std::string SEX_FEMALE;
    static const std::string AGE;
    static const std::string HAIR_COLOUR;
    static const std::string EYE_COLOUR;
    static const std::string SELECT_RACE;
    static const std::string SELECT_CLASS;
    static const std::string SELECT_DEITY;
    static const std::string DEITY;
    static const std::string RACE_1_NAME;
    static const std::string RACE_1_SHORT_DESC;
    static const std::string RACE_1_DESC;
    static const std::string RACE_2_NAME;
    static const std::string RACE_2_SHORT_DESC;
    static const std::string RACE_2_DESC;
    static const std::string RACE_3_NAME;
    static const std::string RACE_3_SHORT_DESC;
    static const std::string RACE_3_DESC;
    static const std::string RACE_4_NAME;
    static const std::string RACE_4_SHORT_DESC;
    static const std::string RACE_4_DESC;
    static const std::string RACE_5_NAME;
    static const std::string RACE_5_SHORT_DESC;
    static const std::string RACE_5_DESC;
    static const std::string RACE_6_NAME;
    static const std::string RACE_6_SHORT_DESC;
    static const std::string RACE_6_DESC;
    static const std::string RACE_7_NAME;
    static const std::string RACE_7_SHORT_DESC;
    static const std::string RACE_7_DESC;
    static const std::string RACE_8_NAME;
    static const std::string RACE_8_SHORT_DESC;
    static const std::string RACE_8_DESC;
    static const std::string RACE_9_NAME;
    static const std::string RACE_9_SHORT_DESC;
    static const std::string RACE_9_DESC;
    static const std::string RACE_10_NAME;
    static const std::string RACE_10_SHORT_DESC;
    static const std::string RACE_10_DESC;

    static const std::string STRENGTH;
    static const std::string STRENGTH_ABRV;
    static const std::string DEXTERITY;
    static const std::string DEXTERITY_ABRV;
    static const std::string AGILITY;
    static const std::string AGILITY_ABRV;
    static const std::string HEALTH;
    static const std::string HEALTH_ABRV;
    static const std::string INTELLIGENCE;
    static const std::string INTELLIGENCE_ABRV;
    static const std::string WILLPOWER;
    static const std::string WILLPOWER_ABRV;
    static const std::string CHARISMA;
    static const std::string CHARISMA_ABRV;

    static const std::string VALOUR;
    static const std::string VALOUR_ABRV;
    static const std::string SPIRIT;
    static const std::string SPIRIT_ABRV;
    static const std::string SPEED;
    static const std::string SPEED_ABRV;

    static const std::string HIT_POINTS;
    static const std::string HIT_POINTS_ABRV;
    static const std::string ARCANA_POINTS;
    static const std::string ARCANA_POINTS_ABRV;

    static const std::string EVADE;
    static const std::string EVADE_ABRV;
    static const std::string SOAK;
    static const std::string SOAK_ABRV;

    static const std::string LEVEL;
    static const std::string LEVEL_ABRV;
    
    static const std::string DAMAGE_MELEE;
    static const std::string DAMAGE_RANGED;
    
    static const std::string EQUIPMENT;
    static const std::string EQUIPMENT_PROMPT;
    static const std::string INVENTORY;
    static const std::string INVENTORY_PROMPT;
    
    static const std::string DECISION_CONFIRM_KEY;
    static const std::string DECISION_DENY_KEY;
    static const std::string DECISION_LEAVE_AREA;
    static const std::string DECISION_QUIT_GAME;
    
    static const std::string GAIN_LEVEL;

  protected:
    TextKeys();
    ~TextKeys();
};

class MaterialTextKeys
{
  public:
    static const std::string MATERIAL_CLOTH;
    static const std::string MATERIAL_DRAGON_SCALE;
    static const std::string MATERIAL_GLASS;
    static const std::string MATERIAL_IRON;
    static const std::string MATERIAL_LEATHER;
    static const std::string MATERIAL_PAPER;
    static const std::string MATERIAL_STEEL;
    static const std::string MATERIAL_STONE;
    static const std::string MATERIAL_WOOD;
    static const std::string MATERIAL_MARBLE;
    static const std::string MATERIAL_ONYX;
    
  protected:
    MaterialTextKeys();
    ~MaterialTextKeys();
};

class DateTextKeys
{
  public:
    static std::string get_date_time_message(const Date& date);
    static std::string get_time(const Date& date);
    
  protected:
    static const std::string DATE_TIME_MESSAGE;
    
    DateTextKeys();
    ~DateTextKeys();
};

class EntranceTextKeys
{
  public:
    static const std::string ENTRANCE_FIELD;
    static const std::string ENTRANCE_SCRUB;
    static const std::string ENTRANCE_DESERT;
    static const std::string ENTRANCE_MOUNTAINS;
    static const std::string ENTRANCE_SEA;
    static const std::string ENTRANCE_FOREST;
    static const std::string ENTRANCE_MARSH;
    static const std::string ENTRANCE_HILLS;
    static const std::string ENTRANCE_CAVERN;
    static const std::string ENTRANCE_VILLAGE;
    static const std::string ENTRANCE_DUNGEON_COMPLEX;
    static const std::string ENTRANCE_BARRACKS;
    static const std::string ENTRANCE_CASTLE;
    static const std::string ENTRANCE_CHURCH;
    static const std::string ENTRANCE_GRAVEYARD;
    static const std::string ENTRANCE_KEEP;
    static const std::string ENTRANCE_LIBRARY;
    static const std::string ENTRANCE_SITE_OF_DEATH;
    static const std::string ENTRANCE_TEMPLE;
    
  protected:
    EntranceTextKeys();
    ~EntranceTextKeys();
};

class EquipmentTextKeys
{
  public:
    static const std::string EQUIPMENT_HEAD;
    static const std::string EQUIPMENT_NECK;
    static const std::string EQUIPMENT_RIGHT_FINGER;
    static const std::string EQUIPMENT_LEFT_FINGER;
    static const std::string EQUIPMENT_RIGHT_HAND;
    static const std::string EQUIPMENT_LEFT_HAND;
    static const std::string EQUIPMENT_BODY;
    static const std::string EQUIPMENT_ABOUT_BODY;
    static const std::string EQUIPMENT_FEET;
    
    static std::string get_equipment_text_from_given_worn_location(const EquipmentWornLocation& worn_location);
    
  protected:
    EquipmentTextKeys();
};

class ColourTextKeys
{
  public:
    static const std::string COLOUR_BLACK;
    static const std::string COLOUR_BROWN;
    static const std::string COLOUR_BLONDE;
    static const std::string COLOUR_RED;
    static const std::string COLOUR_BLUE;
    static const std::string COLOUR_GREEN;
    static const std::string COLOUR_HAZEL;
    static const std::string COLOUR_GREY;
    static const std::string COLOUR_WHITE;
    
    static std::string get_colour_sid_from_hair_colour(const HairColour hair_colour);
    static std::string get_colour_sid_from_eye_colour(const EyeColour eye_colour);
    
  protected:
    ColourTextKeys();
    ~ColourTextKeys();
};

class SizeTextKeys
{
  public:
    static const std::string SIZE;
    static const std::string SIZE_TINY;
    static const std::string SIZE_SMALL;
    static const std::string SIZE_MEDIUM;
    static const std::string SIZE_LARGE;
    static const std::string SIZE_HUGE;
    static const std::string SIZE_BEHEMOTH;
    
    static std::string get_size_sid_from_creature_size(const CreatureSize size);
    
  protected:
    SizeTextKeys();
    ~SizeTextKeys();
};

class SkillTextKeys
{
  public:
    // General (NWP)
    static const std::string SKILLS_GENERAL;
    static const std::string SKILL_GENERAL_ARCHERY;
    static const std::string SKILL_GENERAL_AWARENESS;
    static const std::string SKILL_GENERAL_BARGAINING;
    static const std::string SKILL_GENERAL_BEASTMASTERY;
    static const std::string SKILL_GENERAL_BLIND_FIGHTING;
    static const std::string SKILL_GENERAL_BOATING;
    static const std::string SKILL_GENERAL_BOWYER;
    static const std::string SKILL_GENERAL_BREWING;
    static const std::string SKILL_GENERAL_CANTRIPS;
    static const std::string SKILL_GENERAL_CARRYING;
    static const std::string SKILL_GENERAL_COMBAT;
    static const std::string SKILL_GENERAL_CRAFTING;
    static const std::string SKILL_GENERAL_DESERT_LORE;
    static const std::string SKILL_GENERAL_DETECTION;
    static const std::string SKILL_GENERAL_DISARM_TRAPS;
    static const std::string SKILL_GENERAL_DUAL_WIELD;
    static const std::string SKILL_GENERAL_DUNGEONEERING;
    static const std::string SKILL_GENERAL_ESCAPE;
    static const std::string SKILL_GENERAL_FORAGING;
    static const std::string SKILL_GENERAL_FOREST_LORE;
    static const std::string SKILL_GENERAL_FISHING;
    static const std::string SKILL_GENERAL_FLETCHERY;
    static const std::string SKILL_GENERAL_HERBALISM;
    static const std::string SKILL_GENERAL_HIDING;
    static const std::string SKILL_GENERAL_HUNTING;
    static const std::string SKILL_GENERAL_INTIMIDATION;
    static const std::string SKILL_GENERAL_JEWELER;
    static const std::string SKILL_GENERAL_JUMPING;
    static const std::string SKILL_GENERAL_LEADERSHIP;
    static const std::string SKILL_GENERAL_LITERACY;
    static const std::string SKILL_GENERAL_LORE;
    static const std::string SKILL_GENERAL_MAGIC;
    static const std::string SKILL_GENERAL_MARSH_LORE;
    static const std::string SKILL_GENERAL_MEDICINE;
    static const std::string SKILL_GENERAL_MOUNTAIN_LORE;
    static const std::string SKILL_GENERAL_MOUNTAINEERING;
    static const std::string SKILL_GENERAL_MUSIC;
    static const std::string SKILL_GENERAL_NIGHT_SIGHT;
    static const std::string SKILL_GENERAL_OCEANOGRAPHY;
    static const std::string SKILL_GENERAL_PAPERCRAFT;
    static const std::string SKILL_GENERAL_RELIGION;
    static const std::string SKILL_GENERAL_SCRIBING;
    static const std::string SKILL_GENERAL_SKINNING;
    static const std::string SKILL_GENERAL_SMITHING;
    static const std::string SKILL_GENERAL_SPELUNKING;
    static const std::string SKILL_GENERAL_STEALTH;
    static const std::string SKILL_GENERAL_SWIMMING;
    static const std::string SKILL_GENERAL_TANNING;
    static const std::string SKILL_GENERAL_THIEVERY;
    static const std::string SKILL_GENERAL_WEAVING;

    // Weapon (Melee)
    static const std::string SKILLS_WEAPON;
    static const std::string SKILL_MELEE_AXES;
    static const std::string SKILL_MELEE_SHORT_BLADES;
    static const std::string SKILL_MELEE_LONG_BLADES;
    static const std::string SKILL_MELEE_BLUDGEONS;
    static const std::string SKILL_MELEE_DAGGERS;
    static const std::string SKILL_MELEE_RODS_AND_STAVES;
    static const std::string SKILL_MELEE_SPEARS;
    static const std::string SKILL_MELEE_UNARMED;
    static const std::string SKILL_MELEE_WHIPS;

    // Weapon (Ranged)
    static const std::string SKILLS_RANGED_WEAPON;
    static const std::string SKILL_RANGED_AXES;
    static const std::string SKILL_RANGED_BLADES;
    static const std::string SKILL_RANGED_BLUDGEONS;
    static const std::string SKILL_RANGED_BOWS;
    static const std::string SKILL_RANGED_CROSSBOWS;
    static const std::string SKILL_RANGED_DAGGERS;
    static const std::string SKILL_RANGED_ROCKS;
    static const std::string SKILL_RANGED_SLINGS;
    static const std::string SKILL_RANGED_SPEARS;

    // Magic
    static const std::string SKILLS_MAGIC;
    static const std::string SKILL_MAGIC_ARCANE;
    static const std::string SKILL_MAGIC_DIVINE;
    static const std::string SKILL_MAGIC_MYSTIC;
    static const std::string SKILL_MAGIC_PRIMORDIAL;

  protected:
    SkillTextKeys();
    ~SkillTextKeys();
};

class ItemTypeTextKeys
{
  public:
    static const std::string ITEM_TYPE_MISC;
    static const std::string ITEM_TYPE_WEAPONS;
    static const std::string ITEM_TYPE_ARMOURS;
    static const std::string ITEM_TYPE_POTIONS;
    static const std::string ITEM_TYPE_BOOKS;
    static const std::string ITEM_TYPE_SCROLLS;
    static const std::string ITEM_TYPE_WANDS;
    static const std::string ITEM_TYPE_STAVES;
    static const std::string ITEM_TYPE_RINGS;
    static const std::string ITEM_TYPE_AMULETS;
    static const std::string ITEM_TYPE_FOOD;
    static const std::string ITEM_TYPE_AMMUNITION;
    static const std::string ITEM_TYPE_PLANTS;

  protected:
    ItemTypeTextKeys();
    ~ItemTypeTextKeys();
};

class ResistanceTextKeys
{
  public:
    static const std::string RESISTANCE_SLASH;
    static const std::string RESISTANCE_POUND;
    static const std::string RESISTANCE_PIERCE;
    static const std::string RESISTANCE_HEAT;
    static const std::string RESISTANCE_COLD;
    static const std::string RESISTANCE_ACID;
    static const std::string RESISTANCE_POISON;
    static const std::string RESISTANCE_HOLY;
    static const std::string RESISTANCE_SHADOW;
    static const std::string RESISTANCE_ARCANE;
    static const std::string RESISTANCE_MENTAL;
    static const std::string RESISTANCE_SONIC;
    static const std::string RESISTANCE_RADIANT;
    static const std::string RESISTANCE_LIGHTNING;

  protected:
    ResistanceTextKeys();
    ~ResistanceTextKeys();
};

class PromptTextKeys
{
  public:
    static const std::string PROMPT_ANY_KEY;
    static const std::string PROMPT_ENTER_YOUR_NAME;

  protected:
    PromptTextKeys();
    ~PromptTextKeys();
};

class WorldMapLocationTextKeys
{
  public:
    static const std::string STARTING_LOCATION;
    static const std::string CURRENT_PLAYER_LOCATION;

  protected:
    WorldMapLocationTextKeys();
    ~WorldMapLocationTextKeys();
};

class MovementTextKeys
{
  public:
    static const std::string ACTION_MOVE_NO_EXIT;
    static const std::string ACTION_MOVE_OFF_WORLD_MAP;
    static const std::string ACTION_NO_WAY_UP_WORLD_MAP;
    static const std::string ACTION_MOVE_OFF_OVERWORLD_MAP;
    static const std::string ACTION_MOVE_OFF_UNDERWORLD_MAP;
    static const std::string ITEMS_ON_TILE;
    
  protected:
    MovementTextKeys();
    ~MovementTextKeys();
};

class TileTextKeys
{
  public:
    static const std::string TILE_DESC_BEACH;
    static const std::string TILE_DESC_BUSH;
    static const std::string TILE_DESC_CAIRN;
    static const std::string TILE_DESC_CAVERN;
    static const std::string TILE_DESC_DESERT;
    static const std::string TILE_DESC_DUNGEON;
    static const std::string TILE_DESC_DUNGEON_COMPLEX;
    static const std::string TILE_DESC_FIELD;
    static const std::string TILE_DESC_FOREST;
    static const std::string TILE_DESC_GRAVE;
    static const std::string TILE_DESC_HILLS;
    static const std::string TILE_DESC_MARSH;
    static const std::string TILE_DESC_MOUNTAINS;
    static const std::string TILE_DESC_REEDS;
    static const std::string TILE_DESC_RIVER;
    static const std::string TILE_DESC_ROAD;
    static const std::string TILE_DESC_ROCK;
    static const std::string TILE_DESC_UP_STAIRCASE;
    static const std::string TILE_DESC_DOWN_STAIRCASE;
    static const std::string TILE_DESC_SCRUB;
    static const std::string TILE_DESC_SEA;
    static const std::string TILE_DESC_SHOALS;
    static const std::string TILE_DESC_SPRINGS;
    static const std::string TILE_DESC_TREE;
    static const std::string TILE_DESC_VILLAGE;
    static const std::string TILE_DESC_WEEDS;
    static const std::string TILE_DESC_WHEAT;
    static const std::string TILE_DESC_BARRACKS;
    static const std::string TILE_DESC_CASTLE;
    static const std::string TILE_DESC_CHURCH;
    static const std::string TILE_DESC_GRAVEYARD;
    static const std::string TILE_DESC_KEEP;
    static const std::string TILE_DESC_LIBRARY;
    static const std::string TILE_DESC_SITE_OF_DEATH;
    static const std::string TILE_DESC_TEMPLE;
    static const std::string TILE_DESC_DAIS;
    
  protected:
    TileTextKeys();
    ~TileTextKeys();
};

class ActionTextKeys
{
  public:
    static const std::string ACTION_NOT_FOUND;
    static const std::string ACTION_SEARCH;
    static const std::string ACTION_PICK_UP_NOT_ALLOWED;
    static const std::string ACTION_DROP_NOT_ALLOWED;
    static const std::string ACTION_DROP_NO_ITEM_SELECTED;
    static const std::string ACTION_PICK_UP_NOTHING_ON_GROUND;
    static const std::string ACTION_MOVEMENT_BLOCKED;

  protected:
    ActionTextKeys();
    ~ActionTextKeys();
};

class TextMessages
{
  public:
    static std::string get_welcome_message(const std::string& player_name);
    static std::string get_death_message(const std::string& deity_death_message_sid);
    static std::string get_npc_escapes_message(const std::string& creature_description);
    static std::string get_action_not_found_message(const std::string& command_action);
    static std::string get_dumping_character_message(const std::string& creature_name);
    static std::string get_sex(const CreatureSex sex);
    static std::string get_equipment_location(const EquipmentWornLocation location);
    static std::string get_confirmation_message(const std::string& query_sid);
    static std::string get_area_entrance_message_given_terrain_type(const TileType type);
    static std::string get_item_drop_message(const std::string& item_description);
    static std::string get_item_pick_up_message(const std::string& item_description);
    static std::string get_item_on_ground_description_message(const std::string& item_on_ground_description);

  protected:
    TextMessages();
    ~TextMessages();

    static const std::string WELCOME_MESSAGE;
    static const std::string DUMPING_CHARACTER_MESSAGE;
    static const std::string ITEM_DROP_MESSAGE;
    static const std::string ITEM_PICK_UP_MESSAGE;
    static const std::string ITEM_ON_GROUND_DESCRIPTION_MESSAGE;
};

class FeatureDescriptionTextKeys
{
  public:
    static const std::string FEATURE_DESCRIPTION_DOOR;
    static const std::string FEATURE_DESCRIPTION_GATE;
    static const std::string FEATURE_DESCRIPTION_EVIL_ALTAR;
    static const std::string FEATURE_DESCRIPTION_GOOD_ALTAR;
    static const std::string FEATURE_DESCRIPTION_NEUTRAL_ALTAR;
    static const std::string FEATURE_DESCRIPTION_FIRE_PILLAR;
    static const std::string FEATURE_DESCRIPTION_FOUNTAIN;
    static const std::string FEATURE_DESCRIPTION_PEW;
    static const std::string FEATURE_DESCRIPTION_KING_STATUE;
    static const std::string FEATURE_DESCRIPTION_QUEEN_STATUE;
    static const std::string FEATURE_DESCRIPTION_WARLORD_STATUE;
    static const std::string FEATURE_DESCRIPTION_KNIGHT_STATUE;
    static const std::string FEATURE_DESCRIPTION_HIGH_PRIEST_STATUE;
    static const std::string FEATURE_DESCRIPTION_SORCEROR_STATUE;
    static const std::string FEATURE_DESCRIPTION_BENCH;
    
  protected:
    FeatureDescriptionTextKeys();
};

class PrayerTextKeys
{
  public:
    static std::string get_prayer_message(const std::string& deity_sid);
    
    static const std::string PRAYER_INITIAL_MESSAGE;
    static const std::string PRAYER_DO_NOTHING;
    static const std::string PRAYER_FULL_HP;
    
  protected:
    PrayerTextKeys();
    ~PrayerTextKeys();
};

// Contains player and non-player versions of all combat strings.
class CombatTextKeys
{
  public:
    static std::string get_close_miss_message(const bool is_player, const std::string& attacker, const std::string& missed_target);
    static std::string get_miss_message(const bool is_player, const std::string& attacker, const std::string& missed_target);
    static std::string get_critical_hit_message();
    static std::string get_mighty_blow_message();
    static std::string get_hit_message(const bool is_player, const DamageType damage_type, const std::string& attacker, const std::string& hit_target);
    static std::string get_monster_death_message(const std::string& monster_name);
    static std::string get_no_damage_message(const bool is_player, const std::string& target);

    static const std::string COMBAT_CRITICAL_HIT_MESSAGE; // Common to both - no substitutions
    static const std::string COMBAT_MIGHTY_BLOW_MESSAGE; // Common to both - no substitutions
    static const std::string COMBAT_ATTACK_NO_EFFECT;

  protected:
    CombatTextKeys();

    static const std::string COMBAT_MONSTER_NO_DAMAGE_RECEIVED_MESSAGE;
    static const std::string COMBAT_PLAYER_NO_DAMAGE_RECEIVED_MESSAGE;
    static const std::string COMBAT_MONSTER_DEATH_MESSAGE;
    static const std::string COMBAT_CLOSE_MISS_MESSAGE;
    static const std::string COMBAT_CLOSE_MISS_MESSAGE_NP;
    static const std::string COMBAT_MISS_MESSAGE;
    static const std::string COMBAT_MISS_MESSAGE_NP;
    static const std::string COMBAT_HIT_SLASH;
    static const std::string COMBAT_HIT_SLASH_NP;
    static const std::string COMBAT_HIT_POUND;
    static const std::string COMBAT_HIT_POUND_NP;
    static const std::string COMBAT_HIT_PIERCE;
    static const std::string COMBAT_HIT_PIERCE_NP;
    static const std::string COMBAT_HIT_HEAT;
    static const std::string COMBAT_HIT_HEAT_NP;
    static const std::string COMBAT_HIT_COLD;
    static const std::string COMBAT_HIT_COLD_NP;
    static const std::string COMBAT_HIT_ACID;
    static const std::string COMBAT_HIT_ACID_NP;
    static const std::string COMBAT_HIT_POISON;
    static const std::string COMBAT_HIT_POISON_NP;
    static const std::string COMBAT_HIT_HOLY;
    static const std::string COMBAT_HIT_HOLY_NP;
    static const std::string COMBAT_HIT_SHADOW;
    static const std::string COMBAT_HIT_SHADOW_NP;
    static const std::string COMBAT_HIT_ARCANE;
    static const std::string COMBAT_HIT_ARCANE_NP;
    static const std::string COMBAT_HIT_MENTAL;
    static const std::string COMBAT_HIT_MENTAL_NP;
    static const std::string COMBAT_HIT_SONIC;
    static const std::string COMBAT_HIT_SONIC_NP;
    static const std::string COMBAT_HIT_RADIANT;
    static const std::string COMBAT_HIT_RADIANT_NP;
    static const std::string COMBAT_HIT_LIGHTNING;
    static const std::string COMBAT_HIT_LIGHTNING_NP;
    
    static void populate_combat_messages();
    static std::string create_key(const bool is_player, const DamageType damage_type);
    static std::map<std::string, std::string> combat_damage_hit_messages;
};
