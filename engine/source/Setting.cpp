#include "Setting.hpp"

using namespace std;

Setting::Setting()
{
}

Setting::~Setting()
{
}

const string Setting::LOG_DIR = "log_dir";
const string Setting::USERDATA_DIR = "userdata_dir";
const string Setting::GENERATE_SYSTEM_CHARDUMP = "generate_system_chardump";
const string Setting::SYSCHARDUMP_DIR = "syschardump_dir";
const string Setting::SHADE_TERRAIN = "shade_terrain";
const string Setting::SHADE_CREATURES_AND_ITEMS = "shade_creatures_and_items";
const string Setting::DEFAULT_HP_COLOUR = "default_hp_colour";
const string Setting::DEFAULT_AP_COLOUR = "default_ap_colour";
const string Setting::HIGHLIGHT_ON_PC_CRITICAL_HIT = "highlight_on_pc_critical_hit";
const string Setting::HIGHLIGHT_ON_PC_MAX_DAMAGE_PCT = "highlight_on_pc_max_damage_pct";
const string Setting::HIGHLIGHT_ON_PC_HP_BELOW_PCT = "highlight_on_pc_hp_below_pct";
const string Setting::REST_TURNS = "rest_turns";
const string Setting::NEVER_MOVE_TO_DANGER_TILES = "never_move_to_danger_tiles";
const string Setting::MULTIPLE_DAMAGE_TYPE_MESSAGES = "multiple_damage_type_messages";
const string Setting::SAVEFILE_COMPRESSION = "savefile_compression";
const string Setting::COMPRESSION_LEVEL = "compression_level";
const string Setting::LANGUAGE_FILE = "language_file";
const string Setting::LOG_LEVEL = "log_level";
const string Setting::CURSOR_MODE = "cursor_mode";
const string Setting::DAYS_ELAPSED = "days_elapsed";
const string Setting::HOURS_ELAPSED = "hours_elapsed";
const string Setting::CURRENT_MONTH_IS_START_MONTH = "current_month_is_start_month";
const string Setting::PROMPT_FOR_CHARACTER_DUMP_ON_EXIT = "prompt_for_character_dump_on_exit";
const string Setting::DEFAULT_SEX = "default_sex";
const string Setting::DEFAULT_RACE_ID = "default_race_id";
const string Setting::DEFAULT_CLASS_ID = "default_class_id";
const string Setting::DEFAULT_DEITY_ID = "default_deity_id";
const string Setting::DEFAULT_HAIR_COLOUR = "default_hair_colour";
const string Setting::DEFAULT_EYE_COLOUR = "default_eye_colour";
const string Setting::DEFAULT_STARTING_LOCATION_ID = "default_starting_location_id";
const string Setting::USE_DEFAULT_NAME = "use_default_name";
const string Setting::DEFAULT_NAME = "default_name";
const string Setting::USERNAME_IS_CHARACTER_NAME = "username_is_character_name";
const string Setting::MAX_CHARACTERS_PER_USER = "_max_characters_per_user";
const string Setting::DISPLAY = "display";
const string Setting::DISPLAY_SDL_RENDERER = "display_sdl_renderer";
const string Setting::DISPLAY_SDL_WINDOW_SIZE = "display_sdl_window_size";
const string Setting::DISPLAY_SDL_INTEGER_SCALING = "display_sdl_integer_scaling";
const string Setting::DISPLAY_FONT = "display_font";
const string Setting::DISPLAY_TILE_SIZE = "display_tile_size";
const string Setting::DISPLAY_TILE_GLYPHS_PER_LINE = "display_tile_glyphs_per_line";
const string Setting::DISPLAY_NUM_GLYPHS = "display_num_glyphs";
const string Setting::DISPLAY_FORCE_ASCII = "display_force_ascii";
const string Setting::DISPLAY_SDL_PREFIX = "display_sdl_";
const string Setting::REMOVE_LOGS_DAYS_OLD = "remove_logs_days_old";
const string Setting::SINGLE_USER_MODE = "_single_user_mode";
const string Setting::SKIP_SAVEFILE_METADATA_VERIFICATION = "_skip_savefile_metadata_verification";
const string Setting::AUTOPICKUP = "autopickup";
const string Setting::AUTOPICKUP_TYPES = "autopickup_types";
const string Setting::AUTOPICKUP_IGNORE_CORPSES = "autopickup_ignore_corpses";
const string Setting::PROMPT_ON_STACK_PICKUP = "prompt_on_stack_pickup";
const string Setting::AUTOMELEE = "automelee";
const string Setting::CHECKPOINT_SAVE = "checkpoint_save";
const string Setting::ALLOW_CURSED_AMMUNITION_USE = "allow_cursed_ammunition_use";
const string Setting::SKILL_SELECTION_REQUIRE_CAPITALIZATION = "skill_selection_require_capitalization";
const string Setting::CONFIRMATION_REQUIRE_CAPITALIZATION = "confirmation_require_capitalization";
const string Setting::CONFIGURATION_FILE_BASE = "_configuration_file_base";
const string Setting::CONFIGURATION_FILE_CREATURES = "_configuration_file_creatures";
const string Setting::CONFIGURATION_FILE_ITEMS = "_configuration_file_items";
const string Setting::CONFIGURATION_FILE_WORLD_MAP_AREAS = "_configuration_file_world_map_areas";
const string Setting::NARRATIVE_MODE = "narrative_mode";
const string Setting::DISALLOW_SCORE_ON_EXPLORATION = "_disallow_score_on_exploration";
