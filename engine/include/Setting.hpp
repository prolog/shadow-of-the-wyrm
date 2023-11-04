#pragma once
#include <string>
class Setting
{
  public:
    static const std::string LOG_DIR;
    static const std::string USERDATA_DIR;
    static const std::string GENERATE_SYSTEM_CHARDUMP;
    static const std::string SYSCHARDUMP_DIR;
    static const std::string SHADE_TERRAIN;
    static const std::string SHADE_CREATURES_AND_ITEMS;
    static const std::string DEFAULT_HP_COLOUR;
    static const std::string DEFAULT_AP_COLOUR;
    static const std::string HIGHLIGHT_ON_PC_CRITICAL_HIT;
    static const std::string HIGHLIGHT_ON_PC_MAX_DAMAGE_PCT;
    static const std::string HIGHLIGHT_ON_PC_HP_BELOW_PCT;
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
    static const std::string DEFAULT_AGE;
    static const std::string DEFAULT_SEX;
    static const std::string DEFAULT_RACE_ID;
    static const std::string DEFAULT_CLASS_ID;
    static const std::string DEFAULT_DEITY_ID;
    static const std::string DEFAULT_HAIR_COLOUR;
    static const std::string DEFAULT_EYE_COLOUR;
    static const std::string DEFAULT_STARTING_LOCATION_ID;
    static const std::string DEFAULT_NAME;
    static const std::string USERNAME_IS_CHARACTER_NAME;
    static const std::string MAX_CHARACTERS_PER_USER;
    static const std::string FULL_STOP_AFTER_OPTIONS;
    static const std::string DISPLAY_LOCATION;
    static const std::string DISPLAY;
    static const std::string DISPLAY_SDL_RENDERER;
    static const std::string DISPLAY_SDL_WINDOW_MODE;
    static const std::string DISPLAY_SDL_WINDOW_SIZE;
    static const std::string DISPLAY_SDL_INTEGER_SCALING;
    static const std::string DISPLAY_FONT;
    static const std::string DISPLAY_SPLASH_IMAGE;
    static const std::string DISPLAY_TILE_SIZE;
    static const std::string DISPLAY_TILE_GLYPHS_PER_LINE;
    static const std::string DISPLAY_NUM_GLYPHS;
    static const std::string DISPLAY_FORCE_ASCII;
    static const std::string DISPLAY_SDL_PREFIX;
    static const std::string DISPLAY_SIMPLIFIED_SPLASH_SCREEN;
    static const std::string REMOVE_LOGS_DAYS_OLD;
    static const std::string SINGLE_USER_MODE;
    static const std::string SKIP_SAVEFILE_METADATA_VERIFICATION;
    static const std::string AUTOPICKUP;
    static const std::string AUTOPICKUP_TYPES;
    static const std::string AUTOPICKUP_IGNORE_CORPSES;
    static const std::string AUTOPICKUP_IGNORE_UNPAID;
    static const std::string AUTOPICKUP_IGNORE_ITEMS_OVER_WEIGHT;
    static const std::string AUTOPICKUP_IGNORE_ITEMS_OVER_WEIGHT_LBS;
    static const std::string PROMPT_ON_STACK_PICKUP;
    static const std::string AUTOMELEE;
    static const std::string AUTOMOVE_ALWAYS_STOP_ON_ITEMS;
    static const std::string CHECKPOINT_SAVE;
    static const std::string ALLOW_CURSED_AMMUNITION_USE;
    static const std::string SKILL_SELECTION_REQUIRE_CAPITALIZATION;
    static const std::string CONFIRMATION_REQUIRE_CAPITALIZATION;
    static const std::string CONFIGURATION_FILE_BASE;
    static const std::string CONFIGURATION_FILE_CREATURES;
    static const std::string CONFIGURATION_FILE_ITEMS;
    static const std::string CONFIGURATION_FILE_WORLD_MAP_AREAS;
    static const std::string NARRATIVE_MODE;
    static const std::string DISALLOW_SCORE_ON_EXPLORATION;
    static const std::string SPELLCASTER_UNUSABLE_SPELLBOOK_SQUELCH_PCT;
    static const std::string CONTINUE_TILE_SELECTION_AFTER_LOOKUP;
    static const std::string SHOW_DISTANCE_ON_EXAMINE;
    static const std::string WORLD_MAP_ROWS;
    static const std::string WORLD_MAP_COLS;
    static const std::string WORLD_MAP_TREASURE_X_IN_Y_X;
    static const std::string WORLD_MAP_TREASURE_X_IN_Y_Y;
    static const std::string WORLD_MAP_FILL_TILE_TYPE;

    // world map cellular automata terrain has the form below: as well as FIELD,
    // there is also FOREST, HILLS, MOUNTAINS, SCRUBLAND, MARSHES, DESERT.
    /* static const std::string WORLD_MAP_CA_FIELD_P_CLOSE_CELL;
    static const std::string WORLD_MAP_CA_FIELD_ITERATIONS;
    static const std::string WORLD_MAP_CA_FIELD_NEIGHBOUR_THRESHOLD;
    static const std::string WORLD_MAP_CA_FIELD_OFFSET;
    static const std::string WORLD_MAP_CA_FIELD_FLIP_VALUE; */

  protected:
    Setting();
    ~Setting();
};

