#pragma once
#include <string>
#include "CreatureFeatures.hpp"
#include "EquipmentTypes.hpp"
#include "tiles.hpp"

// These define all the string keys.
// Key/value pairs are defined in savagelandstext_lang.ini, where lang=en,fr,ru,kl,etc.
class TextKeys
{
  public:
    static std::string SL_TITLE;
    static std::string SL_TITLE_POEM;
    static std::string COPYRIGHT_NOTICE;
    static std::string DEFAULT_PLAYER_NAME;
    static std::string SEX;
    static std::string SELECT_SEX;
    static std::string SEX_MALE;
    static std::string SEX_FEMALE;
    static std::string AGE;
    static std::string HAIR_COLOUR;
    static std::string EYE_COLOUR;
    static std::string SELECT_RACE;
    static std::string SELECT_CLASS;
    static std::string RACE_1_NAME;
    static std::string RACE_1_SHORT_DESC;
    static std::string RACE_1_DESC;
    static std::string RACE_2_NAME;
    static std::string RACE_2_SHORT_DESC;
    static std::string RACE_2_DESC;
    static std::string RACE_3_NAME;
    static std::string RACE_3_SHORT_DESC;
    static std::string RACE_3_DESC;
    static std::string RACE_4_NAME;
    static std::string RACE_4_SHORT_DESC;
    static std::string RACE_4_DESC;
    static std::string RACE_5_NAME;
    static std::string RACE_5_SHORT_DESC;
    static std::string RACE_5_DESC;
    static std::string RACE_6_NAME;
    static std::string RACE_6_SHORT_DESC;
    static std::string RACE_6_DESC;
    static std::string RACE_7_NAME;
    static std::string RACE_7_SHORT_DESC;
    static std::string RACE_7_DESC;
    static std::string RACE_8_NAME;
    static std::string RACE_8_SHORT_DESC;
    static std::string RACE_8_DESC;
    static std::string RACE_9_NAME;
    static std::string RACE_9_SHORT_DESC;
    static std::string RACE_9_DESC;
    static std::string RACE_10_NAME;
    static std::string RACE_10_SHORT_DESC;
    static std::string RACE_10_DESC;

    static std::string STRENGTH;
    static std::string STRENGTH_ABRV;
    static std::string DEXTERITY;
    static std::string DEXTERITY_ABRV;
    static std::string AGILITY;
    static std::string AGILITY_ABRV;
    static std::string HEALTH;
    static std::string HEALTH_ABRV;
    static std::string INTELLIGENCE;
    static std::string INTELLIGENCE_ABRV;
    static std::string WILLPOWER;
    static std::string WILLPOWER_ABRV;
    static std::string CHARISMA;
    static std::string CHARISMA_ABRV;

    static std::string VALOUR;
    static std::string VALOUR_ABRV;
    static std::string SPIRIT;
    static std::string SPIRIT_ABRV;
    static std::string SPEED;
    static std::string SPEED_ABRV;

    static std::string HIT_POINTS;
    static std::string HIT_POINTS_ABRV;
    static std::string ARCANA_POINTS;
    static std::string ARCANA_POINTS_ABRV;

    static std::string EVADE;
    static std::string EVADE_ABRV;
    static std::string SOAK;
    static std::string SOAK_ABRV;

    static std::string LEVEL;
    static std::string LEVEL_ABRV;
    
    static std::string DAMAGE_MELEE;
    static std::string DAMAGE_RANGED;
    
    static std::string EQUIPMENT;
    static std::string EQUIPMENT_PROMPT;
    static std::string INVENTORY;
    static std::string INVENTORY_PROMPT;
    
    static std::string DECISION_CONFIRM_KEY;
    static std::string DECISION_DENY_KEY;
    static std::string DECISION_LEAVE_AREA;
    static std::string DECISION_QUIT_GAME;

  protected:
    TextKeys();
    ~TextKeys();
};

class MaterialTextKeys
{
  public:
    static std::string MATERIAL_CLOTH;
    static std::string MATERIAL_DRAGON_SCALE;
    static std::string MATERIAL_GLASS;
    static std::string MATERIAL_IRON;
    static std::string MATERIAL_LEATHER;
    static std::string MATERIAL_PAPER;
    static std::string MATERIAL_STEEL;
    static std::string MATERIAL_STONE;
    static std::string MATERIAL_WOOD;
    
  protected:
    MaterialTextKeys();
    ~MaterialTextKeys();
};

class EntranceTextKeys
{
  public:
    static std::string ENTRANCE_FIELD;
    static std::string ENTRANCE_SCRUB;
    static std::string ENTRANCE_DESERT;
    static std::string ENTRANCE_MOUNTAINS;
    static std::string ENTRANCE_SEA;
    static std::string ENTRANCE_FOREST;
    static std::string ENTRANCE_MARSH;
    static std::string ENTRANCE_HILLS;
    static std::string ENTRANCE_CAVERN;
    static std::string ENTRANCE_VILLAGE;
    
  protected:
    EntranceTextKeys();
    ~EntranceTextKeys();
};

class EquipmentTextKeys
{
  public:
    static std::string EQUIPMENT_HEAD;
    static std::string EQUIPMENT_NECK;
    static std::string EQUIPMENT_RIGHT_FINGER;
    static std::string EQUIPMENT_LEFT_FINGER;
    static std::string EQUIPMENT_RIGHT_HAND;
    static std::string EQUIPMENT_LEFT_HAND;
    static std::string EQUIPMENT_BODY;
    static std::string EQUIPMENT_ABOUT_BODY;
    static std::string EQUIPMENT_FEET;
    
    static std::string get_equipment_text_from_given_worn_location(const EquipmentWornLocation& worn_location);
    
  protected:
    EquipmentTextKeys();
};

class ColourTextKeys
{
  public:
    static std::string COLOUR_BLACK;
    static std::string COLOUR_BROWN;
    static std::string COLOUR_BLONDE;
    static std::string COLOUR_RED;
    static std::string COLOUR_BLUE;
    static std::string COLOUR_GREEN;
    static std::string COLOUR_HAZEL;
    static std::string COLOUR_GREY;
    static std::string COLOUR_WHITE;
    
    static std::string get_colour_sid_from_hair_colour(const HairColour hair_colour);
    static std::string get_colour_sid_from_eye_colour(const EyeColour eye_colour);
    
  protected:
    ColourTextKeys();
    ~ColourTextKeys();
};

class SizeTextKeys
{
  public:
    static std::string SIZE;
    static std::string SIZE_TINY;
    static std::string SIZE_SMALL;
    static std::string SIZE_MEDIUM;
    static std::string SIZE_LARGE;
    static std::string SIZE_HUGE;
    static std::string SIZE_BEHEMOTH;
    
    static std::string get_size_sid_from_creature_size(const CreatureSize size);
    
  protected:
    SizeTextKeys();
    ~SizeTextKeys();
};

class SkillTextKeys
{
  public:
    // General (NWP)
    static std::string SKILLS_GENERAL;
    static std::string SKILL_GENERAL_ARCHERY;
    static std::string SKILL_GENERAL_AWARENESS;
    static std::string SKILL_GENERAL_BARGAINING;
    static std::string SKILL_GENERAL_BEASTMASTERY;
    static std::string SKILL_GENERAL_BLIND_FIGHTING;
    static std::string SKILL_GENERAL_BOATING;
    static std::string SKILL_GENERAL_BOWYER;
    static std::string SKILL_GENERAL_BREWING;
    static std::string SKILL_GENERAL_CANTRIPS;
    static std::string SKILL_GENERAL_CARRYING;
    static std::string SKILL_GENERAL_COMBAT;
    static std::string SKILL_GENERAL_CRAFTING;
    static std::string SKILL_GENERAL_DESERT_LORE;
    static std::string SKILL_GENERAL_DETECTION;
    static std::string SKILL_GENERAL_DISARM_TRAPS;
    static std::string SKILL_GENERAL_DUAL_WIELD;
    static std::string SKILL_GENERAL_DUNGEONEERING;
    static std::string SKILL_GENERAL_ESCAPE;
    static std::string SKILL_GENERAL_FORAGING;
    static std::string SKILL_GENERAL_FOREST_LORE;
    static std::string SKILL_GENERAL_FISHING;
    static std::string SKILL_GENERAL_FLETCHERY;
    static std::string SKILL_GENERAL_HERBALISM;
    static std::string SKILL_GENERAL_HIDING;
    static std::string SKILL_GENERAL_HUNTING;
    static std::string SKILL_GENERAL_INTIMIDATION;
    static std::string SKILL_GENERAL_JEWELER;
    static std::string SKILL_GENERAL_JUMPING;
    static std::string SKILL_GENERAL_LEADERSHIP;
    static std::string SKILL_GENERAL_LITERACY;
    static std::string SKILL_GENERAL_LORE;
    static std::string SKILL_GENERAL_MAGIC;
    static std::string SKILL_GENERAL_MARSH_LORE;
    static std::string SKILL_GENERAL_MEDICINE;
    static std::string SKILL_GENERAL_MOUNTAIN_LORE;
    static std::string SKILL_GENERAL_MOUNTAINEERING;
    static std::string SKILL_GENERAL_MUSIC;
    static std::string SKILL_GENERAL_NIGHT_SIGHT;
    static std::string SKILL_GENERAL_OCEANOGRAPHY;
    static std::string SKILL_GENERAL_PAPERCRAFT;
    static std::string SKILL_GENERAL_RELIGION;
    static std::string SKILL_GENERAL_SCRIBING;
    static std::string SKILL_GENERAL_SKINNING;
    static std::string SKILL_GENERAL_SMITHING;
    static std::string SKILL_GENERAL_SPELUNKING;
    static std::string SKILL_GENERAL_STEALTH;
    static std::string SKILL_GENERAL_SWIMMING;
    static std::string SKILL_GENERAL_TANNING;
    static std::string SKILL_GENERAL_THIEVERY;
    static std::string SKILL_GENERAL_WEAVING;

    // Weapon (Melee)
    static std::string SKILLS_WEAPON;
    static std::string SKILL_MELEE_AXES;
    static std::string SKILL_MELEE_SHORT_BLADES;
    static std::string SKILL_MELEE_LONG_BLADES;
    static std::string SKILL_MELEE_BLUDGEONS;
    static std::string SKILL_MELEE_DAGGERS;
    static std::string SKILL_MELEE_RODS_AND_STAVES;
    static std::string SKILL_MELEE_SPEARS;
    static std::string SKILL_MELEE_UNARMED;
    static std::string SKILL_MELEE_WHIPS;

    // Weapon (Ranged)
    static std::string SKILLS_RANGED_WEAPON;
    static std::string SKILL_RANGED_AXES;
    static std::string SKILL_RANGED_BLADES;
    static std::string SKILL_RANGED_BLUDGEONS;
    static std::string SKILL_RANGED_BOWS;
    static std::string SKILL_RANGED_CROSSBOWS;
    static std::string SKILL_RANGED_DAGGERS;
    static std::string SKILL_RANGED_ROCKS;
    static std::string SKILL_RANGED_SLINGS;
    static std::string SKILL_RANGED_SPEARS;

    // Magic
    static std::string SKILLS_MAGIC;
    static std::string SKILL_MAGIC_ARCANE;
    static std::string SKILL_MAGIC_DIVINE;
    static std::string SKILL_MAGIC_MYSTIC;
    static std::string SKILL_MAGIC_PRIMORDIAL;

  protected:
    SkillTextKeys();
    ~SkillTextKeys();
};

class ItemTypeTextKeys
{
  public:
    static std::string ITEM_TYPE_MISC;
    static std::string ITEM_TYPE_WEAPONS;
    static std::string ITEM_TYPE_ARMOURS;
    static std::string ITEM_TYPE_POTIONS;
    static std::string ITEM_TYPE_BOOKS;
    static std::string ITEM_TYPE_SCROLLS;
    static std::string ITEM_TYPE_WANDS;
    static std::string ITEM_TYPE_STAVES;
    static std::string ITEM_TYPE_RINGS;
    static std::string ITEM_TYPE_AMULETS;
    static std::string ITEM_TYPE_FOOD;
    static std::string ITEM_TYPE_AMMUNITION;
  protected:
    ItemTypeTextKeys();
    ~ItemTypeTextKeys();
};

class ResistanceTextKeys
{
  public:
    static std::string RESISTANCE_SLASH;
    static std::string RESISTANCE_POUND;
    static std::string RESISTANCE_PIERCE;
    static std::string RESISTANCE_HEAT;
    static std::string RESISTANCE_COLD;
    static std::string RESISTANCE_ACID;
    static std::string RESISTANCE_POISON;
    static std::string RESISTANCE_HOLY;
    static std::string RESISTANCE_SHADOW;
    static std::string RESISTANCE_ARCANE;
    static std::string RESISTANCE_MENTAL;
    static std::string RESISTANCE_SONIC;
    static std::string RESISTANCE_RADIANT;
    static std::string RESISTANCE_LIGHTNING;

  protected:
    ResistanceTextKeys();
    ~ResistanceTextKeys();
};

class PromptTextKeys
{
  public:
    static std::string PROMPT_ANY_KEY;
    static std::string PROMPT_ENTER_YOUR_NAME;

  protected:
    PromptTextKeys();
    ~PromptTextKeys();
};

class WorldMapLocationTextKeys
{
  public:
    static std::string STARTING_LOCATION;
    static std::string CURRENT_PLAYER_LOCATION;

  protected:
    WorldMapLocationTextKeys();
    ~WorldMapLocationTextKeys();
};

class MovementTextKeys
{
  public:
    static std::string ACTION_MOVE_NO_EXIT;
    static std::string ACTION_MOVE_OFF_WORLD_MAP;
    static std::string ACTION_NO_WAY_UP_WORLD_MAP;
    static std::string ACTION_MOVE_OFF_OVERWORLD_MAP;
    static std::string ACTION_MOVE_OFF_UNDERWORLD_MAP;
    static std::string ITEMS_ON_TILE;
    
  protected:
    MovementTextKeys();
    ~MovementTextKeys();
};

class TileTextKeys
{
  public:
    static std::string TILE_DESC_BEACH;
    static std::string TILE_DESC_BUSH;
    static std::string TILE_DESC_CAIRN;
    static std::string TILE_DESC_CAVERN;
    static std::string TILE_DESC_DESERT;
    static std::string TILE_DESC_DUNGEON;
    static std::string TILE_DESC_FIELD;
    static std::string TILE_DESC_FOREST;
    static std::string TILE_DESC_GRAVE;
    static std::string TILE_DESC_HILLS;
    static std::string TILE_DESC_MARSH;
    static std::string TILE_DESC_MOUNTAINS;
    static std::string TILE_DESC_REEDS;
    static std::string TILE_DESC_RIVER;
    static std::string TILE_DESC_ROAD;
    static std::string TILE_DESC_ROCK;
    static std::string TILE_DESC_UP_STAIRCASE;
    static std::string TILE_DESC_DOWN_STAIRCASE;
    static std::string TILE_DESC_SCRUB;
    static std::string TILE_DESC_SEA;
    static std::string TILE_DESC_SHOALS;
    static std::string TILE_DESC_SPRINGS;
    static std::string TILE_DESC_TREE;
    static std::string TILE_DESC_VILLAGE;
    static std::string TILE_DESC_WEEDS;
    static std::string TILE_DESC_WHEAT;
    
  protected:
    TileTextKeys();
    ~TileTextKeys();
};

class ActionTextKeys
{
  public:
    static std::string ACTION_NOT_FOUND;
    static std::string ACTION_SEARCH;
    static std::string ACTION_PICK_UP_NOT_ALLOWED;
    static std::string ACTION_DROP_NOT_ALLOWED;
    static std::string ACTION_DROP_NO_ITEM_SELECTED;
    static std::string ACTION_PICK_UP_NOTHING_ON_GROUND;

  protected:
    ActionTextKeys();
    ~ActionTextKeys();
};

class TextMessages
{
  public:
    static std::string get_welcome_message(const std::string& player_name);
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

    static std::string WELCOME_MESSAGE;
    static std::string DUMPING_CHARACTER_MESSAGE;
    static std::string ITEM_DROP_MESSAGE;
    static std::string ITEM_PICK_UP_MESSAGE;
    static std::string ITEM_ON_GROUND_DESCRIPTION_MESSAGE;
};

// JCD FIXME Todo: Define full text/abbreviation SIDs for statistics: Strength, Piety, etc.
