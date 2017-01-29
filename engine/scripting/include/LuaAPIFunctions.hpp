#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "Tile.hpp"

void set_local_creature(CreaturePtr creature);
CreaturePtr get_creature(const std::string& creature_id);
CreaturePtr get_creature_from_map(const std::string& creature_id, const std::string& map_id);
TilePtr get_tile(const std::string& map_id, const Coordinate& c);

// API prototypes
int add_message_with_pause(lua_State* ls);
int clear_and_add_message(lua_State* ls);
int add_message(lua_State* ls);
int add_fov_message(lua_State* ls);
int add_message_direct(lua_State* ls);
int add_debug_message(lua_State* ls);
int add_confirmation_message(lua_State* ls);
int add_prompt_message(lua_State* ls);
int add_char_message(lua_State* ls);
int add_message_for_creature(lua_State* ls);
int add_new_quest(lua_State* ls);
int is_on_quest(lua_State* ls);
int get_num_creature_killed_global(lua_State* ls);
int get_num_uniques_killed_global(lua_State* ls);
int add_object_to_player_tile(lua_State* ls);
int add_object_to_tile(lua_State* ls);
int add_key_to_player_tile(lua_State* ls);
int add_feature_to_player_tile(lua_State* ls);
int mark_quest_completed(lua_State* ls);
int remove_active_quest(lua_State* ls);
int is_quest_completed(lua_State* ls);
int player_has_item(lua_State* ls);
int remove_object_from_player(lua_State* ls);
int is_item_generated(lua_State* ls);
int get_num_item_generated(lua_State* ls);
int set_skill_value(lua_State* ls);
int get_skill_value(lua_State* ls);
int check_skill(lua_State* ls);
int RNG_range(lua_State* ls);
int RNG_percent_chance(lua_State* ls);
int add_spell_castings(lua_State* ls);
int gain_experience(lua_State* ls);
int get_experience_value(lua_State* ls);
int add_creature_to_map(lua_State* ls);
int remove_creature_from_map(lua_State* ls);
int add_status_to_creature(lua_State* ls);
int add_status_to_creature_at(lua_State* ls);
int get_creature_statuses(lua_State* ls);
int stop_playing_game(lua_State* ls);
int set_creature_base_damage(lua_State* ls);
int set_creature_speed(lua_State* ls);
int get_creature_speed(lua_State* ls);
int get_creature_yx(lua_State* ls);
int get_creature_id(lua_State* ls);
int get_current_map_id(lua_State* ls);
int incr_str(lua_State* ls);
int incr_dex(lua_State* ls);
int incr_agi(lua_State* ls);
int incr_hea(lua_State* ls);
int incr_int(lua_State* ls);
int incr_wil(lua_State* ls);
int incr_cha(lua_State* ls);
int mark_stat(lua_State* ls);
int mark_str(lua_State* ls);
int mark_dex(lua_State* ls);
int mark_agi(lua_State* ls);
int mark_hea(lua_State* ls);
int mark_int(lua_State* ls);
int mark_wil(lua_State* ls);
int mark_cha(lua_State* ls);
int is_stat_max_marked(lua_State* ls);
int gain_level(lua_State* ls);
int goto_level(lua_State* ls);
int is_player(lua_State* ls);
int map_set_custom_map_id(lua_State* ls);
int map_set_edesc(lua_State* ls);
int map_set_additional_property(lua_State* ls);
int map_set_tile_subtype(lua_State* ls);
int map_add_location(lua_State* ls);
int map_transform_tile(lua_State* ls);
int map_add_tile_exit(lua_State* ls);
int log(lua_State* ls);
int get_player_title(lua_State* ls);
int set_creature_current_hp(lua_State* ls);
int set_creature_current_ap(lua_State* ls);
int set_creature_name(lua_State* ls);
int destroy_creature_equipment(lua_State* ls);
int destroy_creature_inventory(lua_State* ls);
int get_deity_summons(lua_State* ls);
int summon_monsters_around_creature(lua_State* ls);
int creature_is_class(lua_State* ls);
int get_item_count(lua_State* ls);
int count_currency(lua_State* ls);
int get_unidentified_item_count(lua_State* ls);
int is_item_identified(lua_State* ls);
int get_item_value(lua_State* ls);
int select_item(lua_State* ls);
int set_hostility(lua_State* ls);
int teleport(lua_State* ls);
int get_creature_description(lua_State* ls);
int transfer_item(lua_State* ls);
int creature_tile_has_item(lua_State* ls);
int pick_up_item(lua_State* ls);
int identify_item(lua_State* ls);
int identify_item_type(lua_State* ls);
int calendar_add_seconds(lua_State* ls);
int calendar_add_minutes(lua_State* ls);
int calendar_add_hours(lua_State* ls);
int calendar_add_days(lua_State* ls);
int calendar_add_years(lua_State* ls);
int add_kill_to_creature_mortuary(lua_State* ls);
int report_coords(lua_State* ls);
int cast_spell(lua_State* ls);
int bless_equipment(lua_State* ls);
int curse_equipment(lua_State* ls);
int curse_inventory(lua_State* ls);
int set_winner(lua_State* ls);
int get_creature_colour(lua_State* ls);
int set_creature_colour(lua_State* ls);
int set_creature_evade(lua_State* ls);
int set_trap(lua_State* ls);
int get_nearby_hostile_creatures(lua_State* ls);
int set_creature_additional_property(lua_State* ls);
int get_creature_additional_property(lua_State* ls);
int get_creature_additional_property_csv(lua_State* ls);
int is_creature_in_view_map(lua_State* ls);
int redraw(lua_State* ls);
int get_race_ids(lua_State* ls);
int get_unarmed_slays(lua_State* ls);
int add_unarmed_slay(lua_State* ls);
int get_race_name(lua_State* ls);
int set_inscription(lua_State* ls);
int get_map_dimensions(lua_State* ls);
int get_coords_with_tile_type_in_range(lua_State* ls);
int get_custom_map_id(lua_State* ls);
int ranged_attack(lua_State* ls);
int get_spellbooks(lua_State* ls);
int set_shop_shopkeeper_id(lua_State* ls);
int repop_shop(lua_State* ls);
int get_unpaid_amount(lua_State* ls);
int set_items_paid(lua_State* ls);

// helper functions for the Lua API functions.
std::string read_sid_and_replace_values(lua_State* ls, int offset = 0);

