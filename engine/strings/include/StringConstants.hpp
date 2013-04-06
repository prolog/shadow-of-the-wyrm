#pragma once
#include <map>
#include <string>
#include "AttackTypes.hpp"
#include "CreatureFeatures.hpp"
#include "CalendarTypes.hpp"
#include "DamageTypes.hpp"
#include "Date.hpp"
#include "EquipmentTypes.hpp"
#include "tiles.hpp"
#include "Weapon.hpp"
#include "Ammunition.hpp"

// These define all the string keys.
// Key/value pairs are defined in savagelandstext_lang.ini, where lang=en,fr,ru,kl,etc.
class TextKeys
{
  public:
    static const std::string SL_TITLE;
    static const std::string SL_TITLE_POEM;
    static const std::string COPYRIGHT_NOTICE;
    static const std::string SL_TITLE_NEW_GAME;
    static const std::string CHARACTER_ALREADY_EXISTS;
    static const std::string SL_TITLE_LOAD_GAME;
    static const std::string SL_TITLE_QUIT_GAME;
    static const std::string EXIT;
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
    static const std::string SELECT_SAVED_GAME;
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
    static const std::string DECISION_JUMP_INTO_WATER;
    static const std::string DECISION_QUIT_GAME;
    static const std::string DECISION_SAVE_GAME;
    static const std::string DECISION_ATTACK_FRIENDLY_CREATURE;
    
    static const std::string GAIN_LEVEL;
    static const std::string UNARMED;

  protected:
    TextKeys();
    ~TextKeys();
};

class DateTextKeys
{
  public:
    static std::string get_date_time_message(const Date& date, const std::string& season_sid);
    static std::string get_time(const Date& date);
    
  protected:
    static const std::string DATE_TIME_MESSAGE;
    
    DateTextKeys();
    ~DateTextKeys();
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
    static const std::string ITEM_TYPE_BOATS;
    static const std::string ITEM_TYPE_CURRENCY;
    static const std::string ITEM_TYPE_TOOLS;

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

class MenuTitleKeys
{
  public:
    static const std::string MENU_TITLE_QUEST_LIST;

  protected:
    MenuTitleKeys();
    ~MenuTitleKeys();
};

class PromptTextKeys
{
  public:
    static const std::string PROMPT_ANY_KEY;
    static const std::string PROMPT_ENTER_YOUR_NAME;
    static const std::string PROMPT_RUN_SCRIPT;

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
    static const std::string ACTION_MOVE_ADJACENT_HOSTILE_CREATURE;
    static const std::string ACTION_MOVE_OFF_WORLD_MAP;
    static const std::string ACTION_NO_WAY_UP_WORLD_MAP;
    static const std::string ACTION_MOVE_OFF_OVERWORLD_MAP;
    static const std::string ACTION_MOVE_OFF_UNDERWORLD_MAP;
    static const std::string ITEMS_ON_TILE;
    
  protected:
    MovementTextKeys();
    ~MovementTextKeys();
};

class TileExtraDescriptionKeys
{
  public:
    static const std::string TILE_EXTRA_DESCRIPTION_ISEN_DUN;
    static const std::string TILE_EXTRA_DESCRIPTION_ISEN_DUN_GRAVEYARD;
    static const std::string TILE_EXTRA_DESCRIPTION_ISEN_DUN_DUNGEON;
    static const std::string TILE_EXTRA_DESCRIPTION_LAST_ISLAND_LAIR;
    static const std::string TILE_EXTRA_DESCRIPTION_WINTERSEA_KEEP;

  protected:
    TileExtraDescriptionKeys();
    ~TileExtraDescriptionKeys();
};

class EffectTextKeys
{
  public:
    static std::string get_healing_effect_message(const std::string& monster_desc_sid, bool is_player);
    static std::string get_ether_effect_message(const std::string& monster_desc_sid, bool is_player);
    static std::string get_identify_individual_item_message(const std::string& unid_usage_desc_sid, const std::string& id_usage_desc_sid);
  
    static const std::string EFFECT_NULL;
    static const std::string EFFECT_SWEET_TASTE;
    static const std::string EFFECT_FRUIT_JUICE;
    static const std::string EFFECT_IDENTIFY_ALL_ITEMS;
    static const std::string EFFECT_IDENTIFY_TYPE;
    
  protected:
    EffectTextKeys();
    ~EffectTextKeys();
    
    static std::string get_general_effect_message(const std::string& monster_desc_sid, const bool is_player, const std::string& player_message_sid, const std::string& monster_message_sid);

    static const std::string EFFECT_HEALING_PLAYER;
    static const std::string EFFECT_HEALING_MONSTER;
    static const std::string EFFECT_ETHER_PLAYER;
    static const std::string EFFECT_ETHER_MONSTER;
    static const std::string EFFECT_IDENTIFY_ITEM;
};

class TileDangerConfirmationKeys
{
  public:
    static const std::string TILE_DANGER_MOUNTAINS;
    
  protected:
    TileDangerConfirmationKeys();
    ~TileDangerConfirmationKeys();
};

class DeityTextKeys
{
  public:
    static std::string get_prayer_message(const std::string& deity_sid);
    
    static const std::string PRAYER_INITIAL_MESSAGE;
    static const std::string PRAYER_DO_NOTHING;
    static const std::string PRAYER_FULL_HP;
    static const std::string DEITY_ACTION_DISPLEASED;
    
  protected:
    DeityTextKeys();
    ~DeityTextKeys();
};

