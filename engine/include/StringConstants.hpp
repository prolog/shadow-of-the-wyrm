#pragma once
#include <string>

// These define all the string keys.
// Key/value pairs are defined in savagelandstext_lang.ini, where lang=en,fr,ru,kl,etc.
class TextKeys
{
  public:
    static std::string SL_TITLE;
    static std::string SL_TITLE_POEM;
    static std::string COPYRIGHT_NOTICE;
    static std::string DEFAULT_PLAYER_NAME;
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

  protected:
    TextKeys();
    ~TextKeys();
};

class SkillTextKeys
{
  public:
    // General (NWP)
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
    static std::string SKILL_MAGIC_ARCANE;
    static std::string SKILL_MAGIC_DIVINE;
    static std::string SKILL_MAGIC_MYSTIC;
    static std::string SKILL_MAGIC_PRIMORDIAL;

  protected:
    SkillTextKeys();
    ~SkillTextKeys();
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

class ActionTextKeys
{
  public:
    static std::string ACTION_SEARCH;
    static std::string ACTION_MOVE_OFF_WORLD_MAP;

  protected:
    ActionTextKeys();
    ~ActionTextKeys();
};

class TextMessages
{
  public:
    static std::string get_welcome_message(const std::string& player_name);

  protected:
    TextMessages();
    ~TextMessages();

    static std::string WELCOME_MESSAGE;
};

// JCD FIXME Todo: Define full text/abbreviation SIDs for statistics: Strength, Piety, etc.
