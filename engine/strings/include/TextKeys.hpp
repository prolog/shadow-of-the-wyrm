#pragma once
#include <string>

// These define all the string keys.
// Key/value pairs are defined in shadowofthewyrmtext_lang.ini, where lang=en,fr,ru,kl,etc.
class TextKeys
{
  public:
    static const std::string SW_TITLE;
    static const std::string SW_TITLE_POEM;
    static const std::string COPYRIGHT_NOTICE;
    static const std::string SW_TITLE_NEW_GAME;
    static const std::string SW_TITLE_NEW_GAME_RANDOM;
    static const std::string CHARACTER_ALREADY_EXISTS;
    static const std::string SW_TITLE_LOAD_GAME;
    static const std::string SW_TITLE_HIGH_SCORES;
    static const std::string SW_TITLE_QUIT_GAME;
    static const std::string SW_PROBLEM_GAME_SAVED;
    static const std::string RANDOM_SELECTION;
    static const std::string EXIT;
    static const std::string DEATH_MESSAGE;
    static const std::string PLAYER_DESC;
    static const std::string YOU;
    static const std::string YOURSELF;
    static const std::string HIMSELF;
    static const std::string HERSELF;
    static const std::string ITSELF;
    static const std::string BOOL_TRUE;
    static const std::string BOOL_FALSE;
    static const std::string MORTUARY;
    static const std::string STATUSES;
    static const std::string TOTAL;
    static const std::string MAXIMUM_LEVEL_DIFFERENCE;
    static const std::string TURNS;
    static const std::string MAXIMUM_DEPTH_REACHED;
    static const std::string NPC_ESCAPES_MESSAGE;
    static const std::string SEX;
    static const std::string SELECT_SEX;
    static const std::string SEX_MALE;
    static const std::string SEX_MALE_ABRV;
    static const std::string SEX_FEMALE;
    static const std::string SEX_FEMALE_ABRV;
    static const std::string SEX_NOT_SPECIFIED;
    static const std::string SEX_NOT_SPECIFIED_ABRV;
    static const std::string SELECT_EQUIPMENT_WORN_LOCATION;
    static const std::string AGE;
    static const std::string HAIR_COLOUR;
    static const std::string EYE_COLOUR;
    static const std::string RACE;
    static const std::string RACES;
    static const std::string SELECT_RACE;
    static const std::string SELECT_CLASS;
    static const std::string SELECT_DEITY;
    static const std::string SELECT_STARTING_LOCATION;
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

    static const std::string SPEED;
    static const std::string SPEED_ABRV;

    static const std::string HIT_POINTS;
    static const std::string HIT_POINTS_ABRV;
    static const std::string ARCANA_POINTS;
    static const std::string ARCANA_POINTS_ABRV;

    static const std::string RANGE_ABRV;

    static const std::string EVADE;
    static const std::string EVADE_ABRV;
    static const std::string SOAK;
    static const std::string SOAK_ABRV;

    static const std::string ALIGNMENT;
    static const std::string ALIGNMENT_GOOD;
    static const std::string ALIGNMENT_GOOD_ABRV;
    static const std::string ALIGNMENT_EVIL;
    static const std::string ALIGNMENT_EVIL_ABRV;
    static const std::string ALIGNMENT_NEUTRAL;
    static const std::string ALIGNMENT_NEUTRAL_ABRV;

    static const std::string LEVEL;
    static const std::string LEVEL_ABRV;
    static const std::string EXPERIENCE;
    static const std::string WINNER;
    static const std::string WINNER_EVIL;
    static const std::string WINNER_GODSLAYER;
    
    static const std::string DAMAGE_MELEE;
    static const std::string DAMAGE_RANGED;
    static const std::string DAMAGE_PIERCING;
    static const std::string DAMAGE_CHAOTIC;
    static const std::string DAMAGE_DRAINING;
    static const std::string DAMAGE_ETHEREAL;
    static const std::string DAMAGE_VORPAL;
    static const std::string DAMAGE_EXPLOSIVE;
    static const std::string DAMAGE_INCORPOREAL;
    static const std::string DAMAGE_SCYTHING;
    static const std::string DAMAGE_SLAYS;

    static const std::string ATTACK_DETAILS;
    static const std::string EQUIPMENT;
    static const std::string EQUIPMENT_PROMPT;
    static const std::string INVENTORY;
    static const std::string INVENTORY_FILTERED;
    static const std::string INVENTORY_PROMPT;
    static const std::string GENERATED_ARTIFACTS;
    static const std::string SKIN_PROMPT;
    static const std::string WEAVE_PROMPT;
    
    static const std::string DECISION_CONFIRM_KEY;
    static const std::string DECISION_DENY_KEY;
    static const std::string DECISION_LEAVE_AREA;
    static const std::string DECISION_JUMP_INTO_WATER;
    static const std::string DECISION_QUIT_GAME;
    static const std::string DECISION_SAVE_GAME;
    static const std::string DECISION_ATTACK_FRIENDLY_CREATURE;
    static const std::string DECISION_SWITCH_FRIENDLY_CREATURE;
    static const std::string DECISION_SQUEEZE_FRIENDLY_CREATURE;
    static const std::string DECISION_RESIST_SWITCH;
    static const std::string DECISION_STEAL_FRIENDLY_CREATURE;
    static const std::string DECISION_CREATE_IDENTIFIED_DUMP;

    static const std::string GAIN_LEVEL;
    static const std::string UNARMED;

    static const std::string SOMETHING;
    static const std::string EVERYTHING;

    static const std::string LATEST_MESSAGES;
    static const std::string FRIENDLY;
    static const std::string DUMPING_CHARACTER_FAILED;
    static const std::string NO_NEW_CHARACTERS;
    static const std::string MEMBERSHIPS;
    static const std::string NOT_APPLICABLE_ABRV;
    static const std::string CARRYING_CAPACITY;
    static const std::string ARTIFACT;

  protected:
    TextKeys();
    ~TextKeys();
};
