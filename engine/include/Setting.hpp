#pragma once
#include <string>
class Setting
{
  public:
    static const std::string SHADE_TERRAIN;
    static const std::string SHADE_CREATURES_AND_ITEMS;
    static const std::string DEFAULT_HP_COLOUR;
    static const std::string DEFAULT_AP_COLOUR;
    static const std::string REST_TURNS;
    static const std::string NEVER_MOVE_TO_DANGER_TILES;
    static const std::string MULTIPLE_DAMAGE_TYPE_MESSAGES;
    static const std::string SAVEFILE_COMPRESSION;
    static const std::string COMPRESSION_LEVEL;
    static const std::string LANGUAGE_FILE;
    static const std::string LOG_LEVEL;
    static const std::string CURSOR_MODE;
    static const std::string DAYS_ELAPSED;
    static const std::string HOURS_ELAPSED;
    static const std::string CURRENT_MONTH_IS_START_MONTH;
    static const std::string PROMPT_FOR_CHARACTER_DUMP_ON_EXIT;
    static const std::string DEFAULT_SEX;
    static const std::string DEFAULT_RACE_ID;
    static const std::string DEFAULT_CLASS_ID;
    static const std::string DEFAULT_DEITY_ID;
    static const std::string DEFAULT_STARTING_LOCATION_ID;
    static const std::string DEFAULT_NAME;
    static const std::string USERNAME_IS_CHARACTER_NAME;
    static const std::string MAX_CHARACTERS_PER_USER;
    static const std::string DISPLAY;
    static const std::string REMOVE_LOGS_DAYS_OLD;
    static const std::string SINGLE_USER_MODE;
    static const std::string AUTOPICKUP;
    static const std::string AUTOPICKUP_TYPES;
    static const std::string AUTOPICKUP_IGNORE_CORPSES;
    static const std::string PROMPT_ON_STACK_PICKUP;
    static const std::string CHECKPOINT_SAVE;
    static const std::string ALLOW_CURSED_AMMUNITION_USE;

  protected:
    Setting();
    ~Setting();
};

