#include "LuaAPIFunctions.hpp"
#include "BestiaryAction.hpp"
#include "BuySellCalculator.hpp"
#include "CarryingCapacityCalculator.hpp"
#include "CitySectorGenerator.hpp"
#include "ClassManager.hpp"
#include "CombatManager.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureFactory.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreatureProperties.hpp"
#include "CreatureUtils.hpp"
#include "DecisionStrategyProperties.hpp"
#include "DirectionUtils.hpp"
#include "EngineConversion.hpp"
#include "EffectFactory.hpp"
#include "ExperienceManager.hpp"
#include "FeatureGenerator.hpp"
#include "FruitVegetableGardenGenerator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "GenerationProperties.hpp"
#include "GeneratorUtils.hpp"
#include "HostilityManager.hpp"
#include "ItemEnchantmentCalculator.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemGenerationManager.hpp"
#include "ItemIdentifier.hpp"
#include "Log.hpp"
#include "LuaItemFilter.hpp"
#include "LuaUtils.hpp"
#include "ItemManager.hpp"
#include "MapExitUtils.hpp"
#include "MapItemGenerator.hpp"
#include "MapProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "Naming.hpp"
#include "NPCBackgroundGenerator.hpp"
#include "OptionScreen.hpp"
#include "OrderAction.hpp"
#include "EnclosureSectorFeature.hpp"
#include "PickupAction.hpp"
#include "PrimordialCalculator.hpp"
#include "RaceManager.hpp"
#include "Quests.hpp"
#include "RaceConstants.hpp"
#include "ReligionConstants.hpp"
#include "ReligionManager.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "ShopGenerator.hpp"
#include "SkillManager.hpp"
#include "SoundEffectID.hpp"
#include "Spellbook.hpp"
#include "SpellbookReadStrategy.hpp"
#include "SpellcastingAction.hpp"
#include "StatisticsMarker.hpp"
#include "StatisticTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StringTable.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextMessages.hpp"
#include "TileGenerator.hpp"
#include "Tool.hpp"
#include "WorldWeatherUpdater.hpp"

using namespace std;

CreaturePtr local_creature;

void add_seconds_to_calendar(const int seconds, int& add_successful);
bool set_all_eq_to(CreaturePtr creature, const ItemStatus status);
bool set_all_inv_to(CreaturePtr creature, const ItemStatus status);

void add_seconds_to_calendar(const int seconds, int& added_time)
{
  if (seconds > 0)
  {
    Game& game = Game::instance();
    game.process_elapsed_time(seconds);

    added_time = 1;
  }
}

void set_local_creature(CreaturePtr creature)
{
  local_creature = creature;
}

// Get the local creature, if it matches, or from the current map
// otherwise.  This allows lookup of a local creature before the
// game has been set up (so that level-up scripts can be run on
// creatures on startup, etc).
CreaturePtr get_creature(const string& creature_id)
{
  // Check to see if there is a local creature defined, and if
  // it has the ID we're looking for.
  //
  // Otherwise, check the Game's current map, as usual.
  if (local_creature && (creature_id == local_creature->get_id()))
  {
    return local_creature;
  }
  else
  {
    MapPtr current_map = Game::instance().get_current_map();

    if (current_map != nullptr)
    {
      CreatureMap& cmap = current_map->get_creatures_ref();
      CreatureMap::iterator c_it = cmap.find(creature_id);

      if (c_it != cmap.end())
      {
        CreaturePtr creature = c_it->second;
        return creature;
      }
      else
      {
        // Couldn't find by creature ID.
        // Try by original creature ID.
        for (const auto& c_pair : cmap)
        {
          CreaturePtr cr_original = c_pair.second;

          if (cr_original != nullptr && cr_original->get_original_id() == creature_id)
          {
            return cr_original;
          }
        }
      }
    }
  }

  CreaturePtr null_creature;
  return null_creature;
}

CreaturePtr get_creature_from_map(const string& creature_id, const string& map_id)
{
  CreaturePtr creature;
  Game& game = Game::instance();
  MapPtr map = game.get_map_registry_ref().get_map(map_id);

  if (map != nullptr)
  {
    creature = map->get_creature(creature_id);
  }

  return creature;
}

// Get a particular tile from the given map
TilePtr get_tile(const string& map_id, const Coordinate& c)
{
  Game& game = Game::instance();
  MapRegistry& mr = game.get_map_registry_ref();
  MapPtr map = mr.get_map(map_id);

  if (map_id.empty() && map == nullptr)
  {
    map = game.get_current_map();
  }

  TilePtr tile;

  if (map)
  {
    tile = map->at(c);
  }

  return tile;
}

// Register all the functions available to the scripting engine.
void ScriptEngine::register_api_functions()
{
  lua_register(L, "add_message_with_pause", add_message_with_pause);
  lua_register(L, "clear_messages", clear_messages);
  lua_register(L, "clear_and_add_message", clear_and_add_message);
  lua_register(L, "add_message", add_message);
  lua_register(L, "add_fov_message", add_fov_message);
  lua_register(L, "add_message_direct", add_message_direct);
  lua_register(L, "add_debug_message", add_debug_message);  
  lua_register(L, "add_confirmation_message", add_confirmation_message);
  lua_register(L, "add_prompt_message", add_prompt_message);
  lua_register(L, "add_char_message", add_char_message);
  lua_register(L, "add_message_for_creature", add_message_for_creature);
  lua_register(L, "add_new_quest", add_new_quest);
  lua_register(L, "is_on_quest", is_on_quest);
  lua_register(L, "get_num_creature_killed_global", get_num_creature_killed_global);
  lua_register(L, "get_num_uniques_killed_global", get_num_uniques_killed_global);
  lua_register(L, "is_unique", is_unique);
  lua_register(L, "add_object_to_player_tile", add_object_to_player_tile);
  lua_register(L, "add_object_with_resists_to_player_tile", add_object_with_resists_to_player_tile);
  lua_register(L, "add_objects_to_player_tile", add_objects_to_player_tile);
  lua_register(L, "add_object_to_map", add_object_to_map);
  lua_register(L, "add_object_to_creature", add_object_to_creature);
  lua_register(L, "add_object_on_tile_to_creature", add_object_on_tile_to_creature);
  lua_register(L, "add_object_to_tile", add_object_to_tile);
  lua_register(L, "add_randart_to_player_tile", add_randart_to_player_tile);
  lua_register(L, "add_key_to_player_tile", add_key_to_player_tile);
  lua_register(L, "add_configurable_feature_to_map", add_configurable_feature_to_map);
  lua_register(L, "add_feature_to_map", add_feature_to_map);
  lua_register(L, "add_all_base_features_to_map", add_all_base_features_to_map);
  lua_register(L, "add_feature_to_player_tile", add_feature_to_player_tile);
  lua_register(L, "set_feature_additional_property", set_feature_additional_property);
  lua_register(L, "mark_quest_completed", mark_quest_completed);
  lua_register(L, "remove_active_quest", remove_active_quest);
  lua_register(L, "is_quest_completed", is_quest_completed);
  lua_register(L, "get_quest_details", get_quest_details);
  lua_register(L, "player_has_item", player_has_item);
  lua_register(L, "remove_object_from_player", remove_object_from_player);
  lua_register(L, "is_item_generated", is_item_generated);
  lua_register(L, "get_num_item_generated", get_num_item_generated);
  lua_register(L, "set_skill_value", set_skill_value);
  lua_register(L, "get_skill_value", get_skill_value);
  lua_register(L, "get_magic_skills", get_magic_skills);
  lua_register(L, "check_skill", check_skill);
  lua_register(L, "set_all_skills_value", set_all_skills_value);
  lua_register(L, "RNG_range", RNG_range);
  lua_register(L, "RNG_percent_chance", RNG_percent_chance);
  lua_register(L, "RNG_dice", RNG_dice);
  lua_register(L, "add_spell_castings", add_spell_castings);
  lua_register(L, "add_all_spells_castings", add_all_spells_castings);
  lua_register(L, "count_spells_known", count_spells_known);
  lua_register(L, "gain_experience", gain_experience);
  lua_register(L, "get_experience_value", get_experience_value);
  lua_register(L, "add_creature_to_map", add_creature_to_map);
  lua_register(L, "remove_creature_from_map", remove_creature_from_map);
  lua_register(L, "add_status_to_creature", add_status_to_creature);
  lua_register(L, "add_status_to_creature_at", add_status_to_creature_at);
  lua_register(L, "remove_negative_statuses_from_creature", remove_negative_statuses_from_creature);
  lua_register(L, "get_creature_statuses", get_creature_statuses);
  lua_register(L, "creature_has_status", creature_has_status);
  lua_register(L, "stop_playing_game", stop_playing_game);
  lua_register(L, "set_creature_base_damage", set_creature_base_damage);
  lua_register(L, "get_creature_base_damage", get_creature_base_damage);
  lua_register(L, "set_creature_piety", set_creature_piety);
  lua_register(L, "get_creature_piety", get_creature_piety);
  lua_register(L, "add_piety", add_piety);
  lua_register(L, "set_creature_piety_regen_bonus", set_creature_piety_regen_bonus);
  lua_register(L, "get_creature_piety_regen_bonus", get_creature_piety_regen_bonus);
  lua_register(L, "set_creature_intrinsic_resist", set_creature_intrinsic_resist);
  lua_register(L, "set_creature_speed", set_creature_speed);
  lua_register(L, "get_creature_speed", get_creature_speed);
  lua_register(L, "set_creature_str", set_creature_str);
  lua_register(L, "set_creature_dex", set_creature_dex);
  lua_register(L, "set_creature_agi", set_creature_agi);
  lua_register(L, "set_creature_hea", set_creature_hea);
  lua_register(L, "set_creature_int", set_creature_int);
  lua_register(L, "set_creature_wil", set_creature_wil);
  lua_register(L, "set_creature_cha", set_creature_cha);
  lua_register(L, "get_creature_yx", get_creature_yx);
  lua_register(L, "get_creature_id", get_creature_id);
  lua_register(L, "get_creature_ids", get_creature_ids);
  lua_register(L, "get_creature_base_id", get_creature_base_id);
  lua_register(L, "get_creature_num_broken_conducts", get_creature_num_broken_conducts);
  lua_register(L, "get_current_map_id", get_current_map_id);
  lua_register(L, "get_map_id", get_map_id);
  lua_register(L, "get_map_exists", get_map_exists);
  lua_register(L, "gain_level", gain_level);
  lua_register(L, "goto_level", goto_level);
  lua_register(L, "get_creature_level", get_creature_level);
  lua_register(L, "is_player", is_player);
  lua_register(L, "incr_str", incr_str);
  lua_register(L, "incr_str_to_unburdened", incr_str_to_unburdened);
  lua_register(L, "incr_dex", incr_dex);
  lua_register(L, "incr_agi", incr_agi);
  lua_register(L, "incr_hea", incr_hea);
  lua_register(L, "incr_int", incr_int);
  lua_register(L, "incr_wil", incr_wil);
  lua_register(L, "incr_cha", incr_cha);
  lua_register(L, "mark_stat", mark_stat);
  lua_register(L, "mark_str", mark_str);
  lua_register(L, "mark_dex", mark_dex);
  lua_register(L, "mark_agi", mark_agi);
  lua_register(L, "mark_hea", mark_hea);
  lua_register(L, "mark_int", mark_int);
  lua_register(L, "mark_wil", mark_wil);
  lua_register(L, "mark_cha", mark_cha);
  lua_register(L, "is_stat_max_marked", is_stat_max_marked);
  lua_register(L, "map_set_custom_map_id", map_set_custom_map_id);
  lua_register(L, "map_set_edesc", map_set_edesc);
  lua_register(L, "map_set_property", map_set_property);
  lua_register(L, "map_get_property", map_get_property);
  lua_register(L, "map_set_tile_subtype", map_set_tile_subtype);
  lua_register(L, "map_set_tile_property", map_set_tile_property);
  lua_register(L, "map_add_location", map_add_location);
  lua_register(L, "map_fill_random", map_fill_random);
  lua_register(L, "map_fill_staggered", map_fill_staggered);
  lua_register(L, "map_transform_tile", map_transform_tile);
  lua_register(L, "map_remove_tile_exit", map_remove_tile_exit);
  lua_register(L, "map_add_tile_exit", map_add_tile_exit);
  lua_register(L, "map_set_explored", map_set_explored);
  lua_register(L, "map_get_name_sid", map_get_name_sid);
  lua_register(L, "map_get_dimensions", map_get_dimensions);
  lua_register(L, "map_get_available_creature_coords", map_get_available_creature_coords);
  lua_register(L, "map_get_tile", map_get_tile);
  lua_register(L, "map_do_tiles_in_range_match_type", map_do_tiles_in_range_match_type);
  lua_register(L, "map_creature_ids_have_substring", map_creature_ids_have_substring);
  lua_register(L, "log", log);
  lua_register(L, "get_player_title", get_player_title);
  lua_register(L, "set_creature_at_fleeing", set_creature_at_fleeing);
  lua_register(L, "set_creature_current_hp", set_creature_current_hp);
  lua_register(L, "get_creature_current_hp", get_creature_current_hp);
  lua_register(L, "set_creature_base_hp", set_creature_base_hp);
  lua_register(L, "get_creature_base_hp", get_creature_base_hp);
  lua_register(L, "set_creature_current_ap", set_creature_current_ap);
  lua_register(L, "get_creature_current_ap", get_creature_current_ap);
  lua_register(L, "set_creature_base_ap", set_creature_base_ap);
  lua_register(L, "get_creature_base_ap", get_creature_base_ap);
  lua_register(L, "set_creature_name", set_creature_name);
  lua_register(L, "get_creature_name", get_creature_name);
  lua_register(L, "destroy_creature_equipment", destroy_creature_equipment);
  lua_register(L, "destroy_creature_inventory", destroy_creature_inventory);
  lua_register(L, "get_deity_summons", get_deity_summons);
  lua_register(L, "get_num_deities", get_num_deities);
  lua_register(L, "clear_deities", clear_deities);
  lua_register(L, "summon_monsters_around_creature", summon_monsters_around_creature);
  lua_register(L, "summon_items_around_creature", summon_items_around_creature);
  lua_register(L, "creature_is_class", creature_is_class);
  lua_register(L, "get_item_count", get_item_count);
  lua_register(L, "count_currency", count_currency);
  lua_register(L, "get_unidentified_item_count", get_unidentified_item_count);
  lua_register(L, "is_item_identified", is_item_identified);
  lua_register(L, "get_item_value", get_item_value);
  lua_register(L, "select_item", select_item);
  lua_register(L, "set_hostility", set_hostility);
  lua_register(L, "set_map_hostility", set_map_hostility);
  lua_register(L, "is_creature_hostile", is_creature_hostile);
  lua_register(L, "teleport", teleport);
  lua_register(L, "get_creature_short_description_sid", get_creature_short_description_sid);
  lua_register(L, "get_creature_description", get_creature_description);
  lua_register(L, "get_creature_description_sids", get_creature_description_sids);
  lua_register(L, "transfer_item", transfer_item);
  lua_register(L, "creature_tile_has_item", creature_tile_has_item);
  lua_register(L, "pick_up_item", pick_up_item);
  lua_register(L, "identify_item", identify_item);
  lua_register(L, "identify_item_type", identify_item_type);
  lua_register(L, "calendar_add_seconds", calendar_add_seconds);
  lua_register(L, "calendar_add_minutes", calendar_add_minutes);
  lua_register(L, "calendar_add_hours", calendar_add_hours);
  lua_register(L, "calendar_add_days", calendar_add_days);
  lua_register(L, "calendar_add_years", calendar_add_years);
  lua_register(L, "add_kill_to_creature_mortuary", add_kill_to_creature_mortuary);
  lua_register(L, "report_coords", report_coords);
  lua_register(L, "get_player_world_map_coords", get_player_world_map_coords);
  lua_register(L, "cast_spell", cast_spell);
  lua_register(L, "bless_equipment", bless_equipment);
  lua_register(L, "curse_equipment", curse_equipment);
  lua_register(L, "bless_inventory", bless_inventory);
  lua_register(L, "curse_inventory", curse_inventory);
  lua_register(L, "set_winner", set_winner);
  lua_register(L, "get_winner", get_winner);
  lua_register(L, "get_creature_colour", get_creature_colour);
  lua_register(L, "set_creature_colour", set_creature_colour);
  lua_register(L, "set_creature_evade", set_creature_evade);
  lua_register(L, "set_trap", set_trap);
  lua_register(L, "get_nearby_hostile_creatures", get_nearby_hostile_creatures);
  lua_register(L, "remove_creature_additional_property", remove_creature_additional_property);
  lua_register(L, "set_creature_additional_property", set_creature_additional_property);
  lua_register(L, "get_creature_additional_property", get_creature_additional_property);
  lua_register(L, "get_creature_additional_property_csv", get_creature_additional_property_csv);
  lua_register(L, "is_creature_in_view_map", is_creature_in_view_map);
  lua_register(L, "redraw", redraw);
  lua_register(L, "get_race_ids", get_race_ids);
  lua_register(L, "get_unarmed_slays", get_unarmed_slays);
  lua_register(L, "add_unarmed_slay", add_unarmed_slay);
  lua_register(L, "get_class_id", get_class_id);
  lua_register(L, "get_race_name", get_race_name);
  lua_register(L, "set_inscription", set_inscription);
  lua_register(L, "get_map_dimensions", get_map_dimensions);
  lua_register(L, "get_coords_with_tile_type_in_range", get_coords_with_tile_type_in_range);
  lua_register(L, "get_custom_map_id", get_custom_map_id);
  lua_register(L, "ranged_attack", ranged_attack);
  lua_register(L, "get_spellbooks", get_spellbooks);
  lua_register(L, "generate_shop", generate_shop);
  lua_register(L, "set_shop_shopkeeper_id", set_shop_shopkeeper_id);
  lua_register(L, "repop_shop", repop_shop);
  lua_register(L, "repop_shops", repop_shops);
  lua_register(L, "get_num_unpaid_items", get_num_unpaid_items);
  lua_register(L, "get_unpaid_amount", get_unpaid_amount);
  lua_register(L, "set_items_paid", set_items_paid);
  lua_register(L, "bargain_discount", bargain_discount);
  lua_register(L, "bargain_premium", bargain_premium);
  lua_register(L, "get_item_type", get_item_type);
  lua_register(L, "get_shop_id", get_shop_id);
  lua_register(L, "get_stocked_item_types", get_stocked_item_types);
  lua_register(L, "get_sale_price", get_sale_price);
  lua_register(L, "set_item_unpaid", set_item_unpaid);
  lua_register(L, "set_item_num_generated", set_item_num_generated);
  lua_register(L, "is_in_shop", is_in_shop);
  lua_register(L, "is_item_unpaid", is_item_unpaid);
  lua_register(L, "load_map", load_map);
  lua_register(L, "has_artifact_in_inventory", has_artifact_in_inventory);
  lua_register(L, "tile_has_creature", tile_has_creature);
  lua_register(L, "tile_has_feature", tile_has_feature);
  lua_register(L, "tile_remove_feature", tile_remove_feature);
  lua_register(L, "tile_is_feature_hidden", tile_is_feature_hidden);
  lua_register(L, "get_creature_original_id", get_creature_original_id);
  lua_register(L, "remove_threat_from_all", remove_threat_from_all);
  lua_register(L, "generate_city_feature", generate_city_feature);
  lua_register(L, "get_staircase_coords", get_staircase_coords);
  lua_register(L, "get_num_conducts", get_num_conducts);
  lua_register(L, "break_conduct", break_conduct);
  lua_register(L, "add_membership", add_membership);
  lua_register(L, "has_membership", has_membership);
  lua_register(L, "is_membership_excluded", is_membership_excluded);
  lua_register(L, "dig_rectangles", dig_rectangles);
  lua_register(L, "get_object_ids_by_type", get_object_ids_by_type);
  lua_register(L, "create_menu", create_menu);
  lua_register(L, "set_sentinel", set_sentinel);
  lua_register(L, "get_sid", get_sid);
  lua_register(L, "set_automove_coords", set_automove_coords);
  lua_register(L, "set_decision_strategy_property", set_decision_strategy_property);
  lua_register(L, "set_event_script", set_event_script);
  lua_register(L, "get_random_hostile_creature_id", get_random_hostile_creature_id);
  lua_register(L, "generate_item", generate_item);
  lua_register(L, "generate_creature", generate_creature);
  lua_register(L, "set_creature_id", set_creature_id);
  lua_register(L, "add_all_items_to_player_tile", add_all_items_to_player_tile);
  lua_register(L, "get_primordial_castings", get_primordial_castings);
  lua_register(L, "creature_exists", creature_exists);
  lua_register(L, "set_weather", set_weather);
  lua_register(L, "genocide", genocide);
  lua_register(L, "genocide_creature", genocide_creature);
  lua_register(L, "genocide_hostile", genocide_hostile);
  lua_register(L, "generate_ancient_beast", generate_ancient_beast);
  lua_register(L, "generate_hireling", generate_hireling);
  lua_register(L, "generate_adventurer", generate_adventurer);
  lua_register(L, "generate_vegetable_garden", generate_vegetable_garden);
  lua_register(L, "generate_enclosure", generate_enclosure);
  lua_register(L, "generate_hermitage", generate_hermitage);
  lua_register(L, "set_colour", set_colour);
  lua_register(L, "add_npc_level_message", add_npc_level_message);
  lua_register(L, "set_leader", set_leader);
  lua_register(L, "get_leader_id", get_leader_id);
  lua_register(L, "remove_leader", remove_leader);
  lua_register(L, "get_name", get_name);
  lua_register(L, "set_hirelings_hired", set_hirelings_hired);
  lua_register(L, "get_hirelings_hired", get_hirelings_hired);
  lua_register(L, "set_adventurers_joined", set_adventurers_joined);
  lua_register(L, "get_adventurers_joined", get_adventurers_joined);
  lua_register(L, "get_trained_magic_skills", get_trained_magic_skills);
  lua_register(L, "get_highest_melee_skill", get_highest_melee_skill);
  lua_register(L, "order_follow", order_follow);
  lua_register(L, "order_at_ease", order_at_ease);
  lua_register(L, "reset_creatures_and_creature_locations", reset_creatures_and_creature_locations);
  lua_register(L, "set_creature_speech_text_sid", set_creature_speech_text_sid);
  lua_register(L, "get_creature_speech_text_sid", get_creature_speech_text_sid);
  lua_register(L, "set_creature_text_details_sid", set_creature_text_details_sid);
  lua_register(L, "creature_has_humanoid_followers", creature_has_humanoid_followers);
  lua_register(L, "count_creature_humanoid_followers", count_creature_humanoid_followers);
  lua_register(L, "set_chat_script", set_chat_script);
  lua_register(L, "count_creatures_with_race", count_creatures_with_race);
  lua_register(L, "count_creatures_with_property", count_creatures_with_property);
  lua_register(L, "get_time_of_day", get_time_of_day);
  lua_register(L, "update_creatures", update_creatures);
  lua_register(L, "get_random_preset_village", get_random_preset_village);
  lua_register(L, "get_random_village", get_random_village);
  lua_register(L, "tokenize", tokenize);
  lua_register(L, "generate_name", generate_name);
  lua_register(L, "remove_chat_script", remove_chat_script);
  lua_register(L, "get_setting", get_setting);
  lua_register(L, "set_current_age", set_current_age);
  lua_register(L, "set_max_age", set_max_age);
  lua_register(L, "set_hungerless", set_hungerless);
  lua_register(L, "generate_npc_background", generate_npc_background);
  lua_register(L, "show_bestiary_text", show_bestiary_text);
  lua_register(L, "get_stack_size_current_state", get_stack_size_current_state);
  lua_register(L, "bad_fn_do_not_call", bad_fn_do_not_call);
  lua_register(L, "erase_map_linkage", erase_map_linkage);
  lua_register(L, "has_trainable_skill", has_trainable_skill);
  lua_register(L, "train_skills", train_skills);
  lua_register(L, "set_feature_uses", set_feature_uses);
  lua_register(L, "set_creature_size", set_creature_size);
  lua_register(L, "get_creature_size", get_creature_size);
  lua_register(L, "get_nutrition", get_nutrition);
  lua_register(L, "get_hidden_treasure_message", get_hidden_treasure_message);
  lua_register(L, "get_map_type", get_map_type);
  lua_register(L, "is_tile_available_for_creature", is_tile_available_for_creature);
  lua_register(L, "set_creature_godless", set_creature_godless);
  lua_register(L, "play_sound_effect", play_sound_effect);
  lua_register(L, "is_sound_enabled", is_sound_enabled);
  lua_register(L, "is_music_enabled", is_music_enabled);
  lua_register(L, "play_event_music", play_event_music);
  lua_register(L, "play_map_music", play_map_music);
  lua_register(L, "set_map_music", set_map_music);
  lua_register(L, "play_music_event", play_music_event);
  lua_register(L, "play_music_location", play_music_location);
  lua_register(L, "get_music_location_for_event", get_music_location_for_event);
  lua_register(L, "get_music_location_for_map_type", get_music_location_for_map_type);
  lua_register(L, "does_item_exist_on_map", does_item_exist_on_map);
  lua_register(L, "set_tile_unprotected_movement_is_death", set_tile_unprotected_movement_is_death);
}

// Lua API helper functions
string read_sid_and_replace_values(lua_State* ls, int offset)
{
  string message;

  int num_args = lua_gettop(ls);
  int first_val = 1 + offset;

  if (num_args > 0 && lua_isstring(ls, first_val))
  {
    vector<string> replacement_sids;
    string message_sid = lua_tostring(ls, first_val);

    // Check to see if a string replacement array has been provided.
    if ((num_args - offset) == 2)
    {
      replacement_sids = LuaUtils::get_string_array_from_table(ls, first_val + 1);
    }

    message = StringTable::get(message_sid);

    for (const auto& value : replacement_sids)
    {
      boost::replace_first(message, "%s", value);
    }

    if (!message.empty())
    {
      message[0] = static_cast<char>(toupper(message[0]));
    }
  }

  return message;
}

// Lua API functions:

// Functions callable by Lua that wrap the actual C++ functions for adding
// messages, getting/updating data, etc.

// Clear the message manager, add a new message, and force the user to 
// continue via a "..." type prompt.
// 
// Arguments are:
// - 1: string containing the SID
// - 2: string array containing replacement values (optional)
int add_message_with_pause(lua_State* ls)
{
  int num_args = lua_gettop(ls);
  if (num_args > 0 && lua_isstring(ls, 1))
  {
    // By default, clear the message buffer
    bool clear_buffer = true;

    if (num_args == 2 && lua_isboolean(ls, 2))
    {
      clear_buffer = (lua_toboolean(ls, 2) != 0);
    }

    string message = read_sid_and_replace_values(ls);

    IMessageManager& manager = MMF::instance();

    if (clear_buffer)
    {
      manager.clear_if_necessary();
    }

    bool interactive = (Game::instance().get_loading() == false);

    if (interactive)
    {
      manager.add_new_message_with_pause(message);
    }
    else
    {
      manager.add_new_message(message);
    }

    manager.send();

    // Check for interactive - most of the time, this function will be
    // called in a quest context, and is safe. But it can also be
    // called when eg generating the cosmos, and we shouldn't try to
    // get confirmation in these cases. Generators typically run in
    // their own threads and can't get events when running in SDL
    // mode.
    if (interactive)
    {
      Game& game = Game::instance();
      game.get_current_player()->get_decision_strategy()->get_confirmation();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_message_with_pause");
  }

  return 0;
}

int clear_messages(lua_State* ls)
{
  if (lua_gettop(ls) == 0)
  {
    IMessageManager& manager = MMF::instance();
    manager.clear_if_necessary();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to clear_messages");
  }

  return 0;
}
// Clear the message manager and add a new message.
// Arguments expected: 1-2.
// Argument types: 
// - 1: string (resource SID)
// - 2: string array, containing replacement values (optional)
int clear_and_add_message(lua_State* ls)
{
  int num_args = lua_gettop(ls);
  if (num_args > 0 && lua_isstring(ls, 1))
  {
    string message = read_sid_and_replace_values(ls);

    IMessageManager& manager = MMF::instance();
    manager.clear_if_necessary();
    manager.add_new_message(message);
    manager.send();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to clear_and_add_message");
  }

  return 0;
}

// Add a new message.
// Arguments expected: 1-2.
// Argument types: string (resource SID, required), table of strings (opt.)
// Assumption: table of strings is an array.a
int add_message(lua_State* ls)
{
  int num_args = lua_gettop(ls);
  if (num_args > 0 && lua_isstring(ls, 1))
  {
    bool do_send = true;

    if (num_args >= 2 && lua_isboolean(ls, 2))
    {
      do_send = lua_toboolean(ls, 2);
    }

    string message = read_sid_and_replace_values(ls);

    IMessageManager& manager = MMF::instance();
    manager.add_new_message(message);

    if (do_send)
    {
      manager.send();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_message");
  }

  return 0;
}

// Adds a new message directly - no SID lookup.
// Expected argument: 1.
// Argument type: string.
int add_message_direct(lua_State* ls)
{
  int num_args = lua_gettop(ls);
  if (num_args == 1 && lua_isstring(ls, 1))
  {
    string message = lua_tostring(ls, 1);

    IMessageManager& manager = MMF::instance();
    manager.add_new_message(message);
    manager.send();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_message_direct");
  }

  return 0;
}

// Clear the message manager, and add a new message.
// Arguments expected: 1-2
// Argument type: 
//    1: string (not a resource string)
//    2: array of strings for replacement (optional)
// The expectation is that this function should be used only for
// debugging purposes, where strings won't be in the .ini files - use the regular 
// "add_message" function otherwise!
int add_debug_message(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args > 0 && lua_isstring(ls, 1))
  {
    vector<string> replacement_sids;
    string debug = lua_tostring(ls, 1);

    if (num_args == 2)
    {
      replacement_sids = LuaUtils::get_string_array_from_table(ls, 2);
    }

    for (const auto& value : replacement_sids)
    {
      boost::replace_first(debug, "%s", value);
    }

    IMessageManager& manager = MMF::instance();
    manager.clear_if_necessary();
    manager.add_new_message(debug);
    manager.send();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_debug_message");
  }

  return 0;
}

// Add a message with a confirmation prompt at the end.
// Arguments: message SID.
// Return value: boolean
int add_confirmation_message(lua_State* ls)
{
  bool confirm = false;
  int num_args = lua_gettop(ls);

  if ((num_args > 0) && (lua_isstring(ls, 1)))
  {
    bool default_value = false;

    if (num_args > 1 && lua_isboolean(ls, 2))
    {
      default_value = lua_toboolean(ls, 2);
    }

    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();
    string message = read_sid_and_replace_values(ls);

    IMessageManager& manager = MMF::instance();
    manager.add_new_confirmation_message(TextMessages::get_confirmation_message(message));
    confirm = player->get_decision_strategy()->get_confirmation(default_value);

    manager.send();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_confirmation_message");
  }

  lua_pushboolean(ls, confirm);
  return 1;
}

// Add a message to prompt for text.
// Arguments: message SID (with optional replacements).
// Return value: string (the text entered)
int add_prompt_message(lua_State* ls)
{
  string prompt_val;

  if ((lua_gettop(ls) > 0) && (lua_isstring(ls, 1)))
  {
    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();
    string message = read_sid_and_replace_values(ls);

    IMessageManager& manager = MMF::instance();
    manager.clear_if_necessary();
    prompt_val = manager.add_new_message_with_prompt(message);

    manager.send();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_prompt_message");
  }

  lua_pushstring(ls, prompt_val.c_str());
  return 1;
}

// Add a message with a prompt for a keypress.
// Arguments: message SID (with optional replacements).
// Return value: string (the keypress entered)
int add_char_message(lua_State* ls)
{
  string key_val;

  if ((lua_gettop(ls) > 0) && (lua_isstring(ls, 1)))
  {
    Game& game = Game::instance();
    DisplayPtr display = game.get_display();
    CreaturePtr player = game.get_current_player();
    string message = read_sid_and_replace_values(ls);

    IMessageManager& manager = MMF::instance();
    manager.clear_if_necessary();
    manager.add_new_message(message);
    manager.send();

    if (display != nullptr)
    {
      display->refresh_current_window();
    }

    key_val = static_cast<char>(player->get_decision_strategy()->get_controller()->get_char_as_int());
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_char_message");
  }

  lua_pushstring(ls, key_val.c_str());
  return 1;
}

int add_fov_message(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 3 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isstring(ls, 3))
  {
    string creature_id = lua_tostring(ls, 1);
    string aff_creature_id = lua_tostring(ls, 2);
    string message_sid = lua_tostring(ls, 3);
    CreaturePtr creature = get_creature(creature_id);
    string message = StringTable::get(message_sid);

    if (num_args == 4)
    {
      message = read_sid_and_replace_values(ls, 2);
    }

    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, aff_creature_id == CreatureID::CREATURE_ID_PLAYER);
    manager.add_new_message(message);
    manager.send();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_fov_message");
  }

  return 0;
}

int add_message_for_creature(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  // Need at least a creature ID and a SID.
  if (num_args > 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    string message = read_sid_and_replace_values(ls, 1 /* offset of 1 because first arg in stack is creature ID */);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature->get_is_player());
      manager.add_new_message(message);
      manager.send();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_message_for_creature");
  }

  return 0;
}

// Add a quest to the in-progress list.  Arguments are:
// - a string representing the quest ID
// - a table representing the "Quest" lua object.
int add_new_quest(lua_State* ls)
{
  if ((lua_gettop(ls) == 2) && (lua_istable(ls, -1)) && (lua_isstring(ls, -2)))
  {
    Game& game = Game::instance();
    ScriptEngine& se = game.get_script_engine_ref();

    string quest_id = lua_tostring(ls, 1);
    string quest_title_sid = se.get_table_str(ls, "quest_title_sid");
    vector<string> quest_title_parameter_sids = String::create_string_vector_from_csv_string(se.get_table_str(ls, "quest_title_parameter_sids"));
    string questmaster_id = se.get_table_str(ls, "questmaster_id");
    string questmaster_name_sid = se.get_table_str(ls, "questmaster_name_sid");
    string map_name_sid = se.get_table_str(ls, "map_name_sid");
    string quest_description_sid = se.get_table_str(ls, "quest_description_sid");
    string quest_description_param_csv = se.get_table_str(ls, "quest_description_parameter_sids");
    vector<string> quest_description_parameter_sids = String::create_string_vector_from_csv_string(quest_description_param_csv);

    Quest new_quest(quest_id, 
                    quest_title_sid, 
                    quest_title_parameter_sids, 
                    questmaster_id,
                    questmaster_name_sid, 
                    map_name_sid, 
                    quest_description_sid, 
                    quest_description_parameter_sids);

    game.get_quests_ref().add_new_quest(quest_id, new_quest);

    // Break the player's questless conduct.
    //
    // Quests should always be handled via Lua code.  If there's ever code to
    // add quests from within the engine, refactor the code below.
    CreaturePtr player = game.get_current_player();

    if (player != nullptr)
    {
      player->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_QUESTLESS);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_new_quest");
  }

  // Return nothing.
  return 0;
}

// Check to see if a current quest is in progress.
// Argument is a string representing the quest ID.
int is_on_quest(lua_State* ls)
{
  bool quest_in_progress = false;

  if ((lua_gettop(ls) == 1) && (lua_isstring(ls, -1)))
  {
    string quest_id = lua_tostring(ls, 1);

    // Check to see if the given quest ID is in progress.
    Game& game = Game::instance();
    Quests& quests = game.get_quests_ref();
    quest_in_progress = quests.is_quest_in_progress(quest_id);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to is_on_quest");
  }

  lua_pushboolean(ls, quest_in_progress);
  return 1;
}

// Check the global mortuary on the game object to determine the death count
// for a particular creature.
//
// Argument is the creature ID.
int get_num_creature_killed_global(lua_State* ls)
{
  int num_killed = 0;

  if ((lua_gettop(ls) == 1) && (lua_isstring(ls, -1)))
  {
    string creature_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    Mortuary& mort = game.get_mortuary_ref();
    num_killed = mort.get_num_creature_killed(creature_id);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_num_creature_killed_global");
  }

  lua_pushinteger(ls, num_killed);
  return 1;
}

// Check the global mortuary on the game object to determine the death count
// for uniques.
//
// Argument is the creature ID.
int get_num_uniques_killed_global(lua_State* ls)
{
  int num_killed = 0;

  if ((lua_gettop(ls) == 0))
  {
    Game& game = Game::instance();
    Mortuary& mort = game.get_mortuary_ref();
    num_killed = mort.get_num_uniques_killed();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_num_uniques_killed_global");
  }

  lua_pushinteger(ls, num_killed);
  return 1;
}

// Checks to see if a given creature base ID is a unique.
int is_unique(lua_State* ls)
{
  bool unique = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string cr_base_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    CreatureGenerationValuesMap& cgv = game.get_creature_generation_values_ref();
    auto cr_it = cgv.find(cr_base_id);

    if (cr_it != cgv.end())
    {
      unique = cr_it->second.is_unique();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to is_unique");
  }

  lua_pushboolean(ls, unique);
  return 1;
}

// Add an object to the player's tile.
// Arguments:
// - 1: base item ID
// - 2: quantity (optional, 1 is assumed)
// - 3: properties to add to item once created (optional, empty assumed)
//
// Return value: true if added, false otherwise.
int add_object_to_player_tile(lua_State* ls)
{
  bool added = false;
  int num_args = lua_gettop(ls);

  if (lua_isstring(ls, 1))
  {
    string base_item_id = lua_tostring(ls, 1);
    uint quantity = 1;
    std::map<string, string> properties;
    int num_enchants = 0;
    int num_smiths = 0;

    if (num_args >= 2 && lua_isnumber(ls, 2))
    {
      quantity = static_cast<uint>(lua_tointeger(ls, 2));
    }

    if (num_args >= 3 && lua_isstring(ls, 3))
    {
      properties = String::create_properties_from_string(lua_tostring(ls, 3));
    }

    if (num_args >= 4 && lua_isnumber(ls, 4))
    {
      num_enchants = lua_tointeger(ls, 4);
    }

    if (num_args >= 5 && lua_isnumber(ls, 5))
    {
      num_smiths = lua_tointeger(ls, 5);
    }

    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (map && map->get_map_type() != MapType::MAP_TYPE_WORLD)
    {
      CreaturePtr player = game.get_current_player();
      TilePtr player_tile = MapUtils::get_tile_for_creature(map, player);
      
      ItemPtr item = ItemManager::create_item(base_item_id, quantity);

      if (item != nullptr)
      {
        if (item->get_status() == ItemStatus::ITEM_STATUS_CURSED)
        {
          item->set_status(ItemStatus::ITEM_STATUS_UNCURSED);
        }

        item->enchant(0, num_enchants);
        item->smith(num_smiths);

        for (const auto& prop_pair : properties)
        {
          item->set_additional_property(prop_pair.first, prop_pair.second);
        }

        IInventoryPtr items = player_tile->get_items();

        if (items != nullptr)
        {
          items->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_object_to_player_tile");
  }

  lua_pushboolean(ls, added);
  return 1;
}

int add_object_with_resists_to_player_tile(lua_State* ls)
{
  bool added = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (map && map->get_map_type() != MapType::MAP_TYPE_WORLD)
    {
      CreaturePtr player = game.get_current_player();
      TilePtr player_tile = MapUtils::get_tile_for_creature(map, player);

      string item_id = lua_tostring(ls, 1);
      string rarray_csv = lua_tostring(ls, 2);
      vector<string> resists = String::create_string_vector_from_csv_string(rarray_csv);

      // Make sure it's the right format - dtype then resist val.
      if (resists.size() % 2 == 0)
      {
        ItemPtr item = ItemManager::create_item(item_id);

        if (item != nullptr)
        {
          Resistances& iresists = item->get_resistances_ref();

          for (size_t i = 0; i < resists.size(); i += 2)
          {
            DamageType dtype = static_cast<DamageType>(String::to_int(resists.at(i)));
            double val = String::to_double(resists.at(i + 1));

            iresists.set_resistance_value(dtype, iresists.get_resistance_value(dtype) + val);
          }
        }

        IInventoryPtr items = player_tile->get_items();

        if (items != nullptr)
        {
          items->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_FRONT);
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_object_with_resists_to_player_tile");
  }

  lua_pushboolean(ls, added);
  return 1;
}

// Add a number of objects to the player's tile. IDs are comma separated.
// This function is really meant to be used for quicker debugging, though
// it might also work if number of enchants/properties/etc aren't needed.
int add_objects_to_player_tile(lua_State* ls)
{
  int added_cnt = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string object_ids = lua_tostring(ls, 1);
    vector<string> ids = String::create_string_vector_from_csv_string(object_ids);
    CreaturePtr player = Game::instance().get_current_player();
    MapPtr map = Game::instance().get_current_map();
    TilePtr player_tile = MapUtils::get_tile_for_creature(map, player);

    if (player_tile != nullptr && map != nullptr && map->get_map_type() != MapType::MAP_TYPE_WORLD)
    {
      IInventoryPtr items = player_tile->get_items();

      if (items != nullptr)
      {
        for (const string& id : ids)
        {
          string obj_id = boost::trim_copy(id);
          ItemPtr item = ItemManager::create_item(obj_id);

          items->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
          added_cnt++;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_objects_to_player_tile");
  }

  lua_pushboolean(ls, added_cnt > 0);
  return 1;
}

// Add an object to a particular tile.
//
// Argument 1: object base id
//          2: map id
//          3: row
//          4: col
//          5: quantity (optional, 1 assumed)
//          6: disallow cursed (defaults to false)
//
// Return value: true if added, false otherwise.
int add_object_to_map(lua_State* ls)
{
  bool result = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 4 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    string base_item_id = lua_tostring(ls, 1);
    string map_id = lua_tostring(ls, 2);
    int row = lua_tointeger(ls, 3);
    int col = lua_tointeger(ls, 4);

    uint quantity = 1;

    // Set the quantity if it was specified.    
    if (num_args >= 5 && lua_isnumber(ls, 5))
    {
      quantity = static_cast<uint>(lua_tointeger(ls, 5));
    }

    bool disallow_cursed = false;
    if (num_args >= 6 && lua_isboolean(ls, 6))
    {
      disallow_cursed = lua_toboolean(ls, 6);
    }

    Game& game = Game::instance();
    MapPtr map = game.get_map_registry_ref().get_map(map_id);

    if (map && map->get_map_type() != MapType::MAP_TYPE_WORLD)
    {
      TilePtr tile = map->at(row, col);
      result = ItemManager::create_item_with_probability(100, 100, tile->get_items(), base_item_id, quantity, disallow_cursed);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_object_to_map");
  }

  lua_pushboolean(ls, result);
  return 1;
}

int add_object_to_creature(lua_State* ls)
{
  bool obj_added = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 3 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isstring(ls, 3))
  {
    string map_id = lua_tostring(ls, 1);
    string creature_id = lua_tostring(ls, 2);
    string object_id = lua_tostring(ls, 3);
    uint quantity = 1;
    string prop;
    
    if (num_args >= 4 && lua_isstring(ls, 4))
    {
      prop = lua_tostring(ls, 4);
    }

    if (num_args >= 5 && lua_isnumber(ls, 5))
    {
      quantity = static_cast<uint>(lua_tointeger(ls, 5));
    }

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      CreaturePtr creature = map->get_creature(creature_id);

      if (creature != nullptr)
      {
        ItemPtr item = ItemManager::create_item(object_id, quantity);

        if (item != nullptr)
        {
          std::map<string, string> properties = String::create_properties_from_string(prop);

          for (const auto& p_pair : properties)
          {
            item->set_additional_property(p_pair.first, p_pair.second);
          }

          creature->get_inventory()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
          obj_added = true;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_object_to_creature");
  }

  lua_pushboolean(ls, obj_added);
  return 1;
}

int add_object_on_tile_to_creature(lua_State* ls)
{
  bool added_obj = false;

  if (lua_gettop(ls) >= 4 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isstring(ls, 3) && lua_isstring(ls, 4))
  {
    int y = lua_tointeger(ls, 1);
    int x = lua_tointeger(ls, 2);
    string item_id = lua_tostring(ls, 3);
    string creature_id = lua_tostring(ls, 4);

    MapPtr map = Game::instance().get_current_map();
    CreaturePtr creature = get_creature(creature_id);

    if (map != nullptr && creature != nullptr)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr)
      {
        IInventoryPtr tile_items = tile->get_items();
        ItemPtr i = tile_items->get_from_id(item_id);

        // Get the item weight. See if this would push the creature
        // to Overburdened. If so, don't add it.
        CarryingCapacityCalculator ccc;

        if (creature->get_weight_carried() + i->get_total_weight().get_weight() < ccc.calculate_overburdened_weight(creature))
        {
          if (i != nullptr)
          {
            added_obj = creature->get_inventory()->merge_or_add(i, InventoryAdditionType::INVENTORY_ADDITION_BACK);

            if (added_obj)
            {
              tile_items->remove(item_id);
            }
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_object_on_tile_to_creature");
  }

  lua_pushboolean(ls, added_obj);
  return 1;
}

// Add an object to a particular tile.
//
// Argument 1: object base id
//          2: row
//          3: col
//          4: quantity (optional, 1 assumed)
//
// Return value: true if added, false otherwise.
int add_object_to_tile(lua_State* ls)
{
  bool result = false;
  int num_args = lua_gettop(ls);

  if (lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && (num_args == 3 || (num_args == 4 && lua_isnumber(ls, 4))))
  {
    string base_item_id = lua_tostring(ls, 1);
    int row = lua_tointeger(ls, 2);
    int col = lua_tointeger(ls, 3);

    uint quantity = 1;

    // Set the quantity if it was specified.    
    if (num_args == 4)
    {
      quantity = static_cast<uint>(lua_tointeger(ls, 4));
    }

    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (map && map->get_map_type() != MapType::MAP_TYPE_WORLD)
    {
      TilePtr tile = map->at(row, col);
      result = ItemManager::create_item_with_probability(100, 100, tile->get_items(), base_item_id, quantity);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_object_to_tile");
  }

  lua_pushboolean(ls, result);
  return 1;
}

int add_randart_to_player_tile(lua_State* ls)
{
  if (lua_gettop(ls) == 0)
  {
    MapPtr map = Game::instance().get_current_map();
    Coordinate c = map->get_location(CreatureID::CREATURE_ID_PLAYER);
    GeneratorUtils::generate_randarts(map, c, 1);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_randart_to_player_tile");
  }

  return 0;
}

// Add a key to the player tile.
// arg 1 = item id
// arg 2 = lock id
int add_key_to_player_tile(lua_State* ls)
{
  bool added = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string key_id = lua_tostring(ls, 1);
    string lock_id = lua_tostring(ls, 2);

    ItemPtr item = ItemManager::create_item(key_id);
    ToolPtr key = dynamic_pointer_cast<Tool>(item);

    if (key != nullptr)
    {
      key->set_lock_id(lock_id);

      MapPtr map = Game::instance().get_current_map();

      if (map && map->get_map_type() != MapType::MAP_TYPE_WORLD)
      {
        CreaturePtr player = Game::instance().get_current_player();
        TilePtr player_tile = MapUtils::get_tile_for_creature(map, player);

        player_tile->get_items()->merge_or_add(key, InventoryAdditionType::INVENTORY_ADDITION_BACK);
        added = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_key_to_player_tile");
  }

  lua_pushboolean(ls, added);
  return 1;
}

int add_configurable_feature_to_map(lua_State* ls)
{
  bool added = false;
  int num_args = lua_gettop(ls);
  Game& game = Game::instance();
  FeaturePtr feature;
  string map_id;
  Coordinate c(0, 0);
  bool created_feature = false;

  // Create an ad-hoc configurable feautre
  if (num_args == 7 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isstring(ls, 4) && lua_isnumber(ls, 5) && lua_isnumber(ls, 6) && lua_isstring(ls, 7))
  {
    string symbol = lua_tostring(ls, 1);
    Colour colour = static_cast<Colour>(lua_tointeger(ls, 2));
    MaterialType material = static_cast<MaterialType>(lua_tointeger(ls, 3));
    string desc_sid = lua_tostring(ls, 4);
    c = make_pair(lua_tointeger(ls, 5), lua_tointeger(ls, 6));
    map_id = lua_tostring(ls, 7);

    feature = FeatureGenerator::generate_configurable_feature(material, Symbol(symbol[0], colour), desc_sid);
    created_feature = (feature != nullptr);
  }
  // Reference a configurable feature from the game XML.
  else if (num_args == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isstring(ls, 4))
  {
    string config_feature_id = lua_tostring(ls, 1);
    c = make_pair(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    map_id = lua_tostring(ls, 4);

    feature = FeatureGenerator::generate_configurable_feature(config_feature_id);
    created_feature = (feature != nullptr);
  }

  // Create a feature if we've read a map id, coordinate, etc.
  if (!map_id.empty())
  {
    MapPtr map = game.get_map_registry_ref().get_map(map_id);
    if (map && map->get_map_type() != MapType::MAP_TYPE_WORLD)
    {
      if (feature != nullptr)
      {
        TilePtr cf_tile = map->at(c);

        if (cf_tile != nullptr)
        {
          cf_tile->set_feature(feature);
          added = true;
        }
      }
    }
  }

  if (!created_feature)
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_configurable_feature_to_map or could not create feature");
  }

  lua_pushboolean(ls, added);
  return 1;
}

// Add a feature (using the class ID) to the player's tile.
int add_feature_to_player_tile(lua_State* ls)
{
  bool added = false;

  if ((lua_gettop(ls) == 1) && (lua_isnumber(ls, 1)))
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (map && map->get_map_type() != MapType::MAP_TYPE_WORLD)
    {
      ClassIdentifier class_id = static_cast<ClassIdentifier>(lua_tointeger(ls, 1));
      FeaturePtr feature = FeatureGenerator::create_feature(class_id);

      if (feature != nullptr)
      {
        CreaturePtr player = game.get_current_player();
        TilePtr player_tile = MapUtils::get_tile_for_creature(map, player);

        player_tile->set_feature(feature);
        added = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_feature_to_player_tile");
  }
  
  lua_pushboolean(ls, added);
  return 1;
}

int set_feature_additional_property(lua_State* ls)
{
  bool prop_added = false;
  int num_args = lua_gettop(ls);

  if (num_args == 5 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isstring(ls, 4) && lua_isstring(ls, 5))
  {
    string map_id = lua_tostring(ls, 1);
    int row = lua_tointeger(ls, 2);
    int col = lua_tointeger(ls, 3);
    string prop_name = lua_tostring(ls, 4);
    string prop_val = lua_tostring(ls, 5);
    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(row, col);

      if (tile != nullptr && tile->has_feature())
      {
        FeaturePtr feature = tile->get_feature();
        feature->set_additional_property(prop_name, prop_val);

        prop_added = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_feature_additional_property");
  }

  lua_pushboolean(ls, prop_added);
  return 1;
}

int add_feature_to_map(lua_State* ls)
{
  bool feature_added = 0;
  int num_args = lua_gettop(ls);

  if (num_args >= 3 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3))
  {
    MapPtr map;
    string map_id;

    int y = lua_tointeger(ls, 2);
    int x = lua_tointeger(ls, 3);

    if (num_args == 4 && lua_isstring(ls, 4))
    {
      map_id = lua_tostring(ls, 4);
    }

    TilePtr tile = get_tile(map_id, make_pair(y, x));

    ClassIdentifier class_id = static_cast<ClassIdentifier>(lua_tointeger(ls, 1));
    FeaturePtr feature = FeatureGenerator::create_feature(class_id);

    if (feature != nullptr)
    {
      if (tile != nullptr)
      {
        tile->set_feature(feature);
        feature_added = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_feature_to_map");
  }

  lua_pushboolean(ls, feature_added);
  return 1;
}

// This function isn't intended to be used in-game - it's meant for
// mass debugging of features.
int add_all_base_features_to_map(lua_State* ls)
{
  int num_added = 0;

  if (lua_gettop(ls) == 2 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2))
  {
    int y = lua_tointeger(ls, 1);
    int x = lua_tointeger(ls, 2);

    FeatureSymbolMap fsm = FeatureGenerator::get_feature_symbol_map();
    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      Dimensions d = map->size();
      int max_y = d.get_y();
      int max_x = d.get_x();

      for (auto f_pair : fsm)
      {
        ClassIdentifier cid = f_pair.first;
        FeaturePtr f = FeatureGenerator::create_feature(cid);

        if (x >= max_x)
        {
          x = 0;
          y++;
        }

        if (y < max_y)
        {
          if (f != nullptr)
          {
            map->at(y, x)->set_feature(f);

            x++;
            num_added++;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to add_all_base_features_to_map");
  }

  lua_pushinteger(ls, num_added);
  return 1;
}
// Mark a quest as completed.
// Argument is the quest ID.
int mark_quest_completed(lua_State* ls)
{
  if ((lua_gettop(ls) == 1) && (lua_isstring(ls, -1)))
  {
    string quest_id = lua_tostring(ls, 1);
    Game& game = Game::instance();
    Quests& quests = game.get_quests_ref();

    quests.set_quest_completed(quest_id);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to mark_quest_completed");
  }

  return 0;
}

// Remove an active quest (typically used for mutually exclusive quests)
// Argument is the quest ID.
int remove_active_quest(lua_State* ls)
{
  bool args_ok = ((lua_gettop(ls) == 1) && (lua_isstring(ls, -1)));

  if (args_ok)
  {
    string quest_id = lua_tostring(ls, 1);
    Game& game = Game::instance();
    Quests& quests = game.get_quests_ref();

    quests.remove_active_quest(quest_id);
  }

  if (!args_ok)
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to remove_active_quest");
  }

  return 0;
}

// Check to see if a quest has been completed.
// Argument is the quest ID
int is_quest_completed(lua_State* ls)
{
  bool quest_completed = false;

  if ((lua_gettop(ls) == 1) && (lua_isstring(ls, -1)))
  {
    string quest_id = lua_tostring(ls, 1);
    Game& game = Game::instance();
    Quests& quests = game.get_quests_ref();

    quest_completed = quests.is_quest_completed(quest_id);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to is_quest_completed");
  }

  lua_pushboolean(ls, quest_completed);
  return 1;
}

int get_quest_details(lua_State* ls)
{
  string quest_title_sid;
  string questmaster_name_sid;
  string map_name_sid;
  string quest_description_sid;
  string quest_description_parameter_sids;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string quest_id = lua_tostring(ls, 1);

    QuestMap inp_quests = Game::instance().get_quests_ref().get_in_progress_quests();
    auto inp_it = inp_quests.find(quest_id);

    if (inp_it != inp_quests.end())
    {
      Quest q = inp_it->second;
        
      quest_title_sid = q.get_quest_title_sid();
      questmaster_name_sid = q.get_questmaster_name_sid();
      map_name_sid = q.get_map_name_sid();
      quest_description_sid = q.get_quest_description_sid();
      quest_description_parameter_sids = String::create_csv_from_string_vector(q.get_quest_description_parameter_sids());
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_quest_details");
  }

  lua_pushstring(ls, quest_title_sid.c_str());
  lua_pushstring(ls, questmaster_name_sid.c_str());
  lua_pushstring(ls, map_name_sid.c_str());
  lua_pushstring(ls, quest_description_sid.c_str());
  lua_pushstring(ls, quest_description_parameter_sids.c_str());

  return 5;
}

// Check to see if the player has an item.
// Argument is the object's base ID.
int player_has_item(lua_State* ls)
{
  bool has_item = false;
  int num_args = lua_gettop(ls);
  std::map<string, string> properties;

  if (num_args >= 1 && lua_isstring(ls, 1))
  {
    if (num_args >= 2 && lua_isstring(ls, 2))
    {
      properties = String::create_properties_from_string(lua_tostring(ls, 2));
    }

    string base_item_id = lua_tostring(ls, 1);
    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();

    has_item = ItemManager::has_item(player, base_item_id, properties);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to player_has_item");
  }

  lua_pushboolean(ls, has_item);
  return 1;
}

// Remove an object from the player's equipment or inventory
// Argument is the object's base ID.
int remove_object_from_player(lua_State* ls)
{
  int num_args = lua_gettop(ls);
  int quantity = 1;
  map<string, string> properties;

  if (num_args >= 1 && lua_isstring(ls, 1))
  {
    string object_base_id = lua_tostring(ls, 1);

    if (num_args >= 2 && lua_isnumber(ls, 2))
    {
      quantity = lua_tointeger(ls, 2);
    }

    if (num_args >= 3 && lua_isstring(ls, 3))
    {
      properties = String::create_properties_from_string(lua_tostring(ls, 3));
    }

    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();

    ItemManager im;
    im.remove_item_from_inv_or_eq(player, object_base_id, quantity, properties);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to remove_object_from_player");
  }

  return 0;
}

// Check to see if an item is generated.
// Argument is the base item ID.
int is_item_generated(lua_State* ls)
{
  bool item_generated = false;

  get_num_item_generated(ls);
  item_generated = (lua_tointeger(ls, -1) > 0);

  // We don't need this value anymore - calling function should get the 
  // boolean return value.
  lua_pop(ls, -1);

  lua_pushboolean(ls, item_generated);
  return 1;
}

// Check to see how many of a particular item have been generated.
// Argument is the base item ID.
int get_num_item_generated(lua_State* ls)
{
  int num_gen = 0;

  if ((lua_gettop(ls) == 1) && (lua_isstring(ls, -1)))
  {
    string object_base_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    GenerationValuesMap& item_generation_values = game.get_item_generation_values_ref();
    GenerationValuesMap::iterator i_it = item_generation_values.find(object_base_id);

    if (i_it != item_generation_values.end())
    {
      num_gen = i_it->second.get_current();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_num_item_generated");
  }

  lua_pushnumber(ls, num_gen);
  return 1;
}

// Set a skill value for a particular creature.
// Three arguments are expected:
// - creature_id
// - skill enumeration value
// - new value (int) for that skill
int set_skill_value(lua_State* ls)
{
  if ((lua_gettop(ls) == 3) && (lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3)))
  {
    string creature_id = lua_tostring(ls, 1);
    int skill_i = lua_tointeger(ls, 2);
    SkillType skill_name = static_cast<SkillType>(skill_i);
    int skill_value = lua_tointeger(ls, 3);

    CreaturePtr creature = get_creature(creature_id);

    if (creature)
    {
      creature->get_skills().set_value(skill_name, skill_value);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_skill_value");
  }


  return 0;
}

// Get a skill value for a particular creature.
// Three arguments are expected:
// - creature_id of a creature on the current map
// - skill enumeration value
// Return value is the current value (int) for that skill.
int get_skill_value(lua_State* ls)
{
  int skill_value = 0;

  if ((lua_gettop(ls) == 2) && (lua_isstring(ls, 1) && lua_isnumber(ls, 2)))
  {
    string creature_id = lua_tostring(ls, 1);
    int skill_i = lua_tointeger(ls, 2);
    SkillType skill_name = static_cast<SkillType>(skill_i);

    CreaturePtr creature = get_creature(creature_id);

    if (creature)
    {
      skill_value = creature->get_skills().get_value(skill_name);

      if (skill_value == -1)
      {
        Log::instance().error("Unknown skill: " + to_string(static_cast<int>(skill_name)));
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_skill_value");
  }

  lua_pushnumber(ls, skill_value);
  return 1;
}

int get_magic_skills(lua_State* ls)
{
  map<SkillType, int> magic_skills = {{SkillType::SKILL_MAGIC_ARCANE, 0},
                                      {SkillType::SKILL_MAGIC_CANTRIPS, 0},
                                      {SkillType::SKILL_MAGIC_DIVINE, 0},
                                      {SkillType::SKILL_MAGIC_MYSTIC, 0},
                                      {SkillType::SKILL_MAGIC_PRIMORDIAL, 0}};

  vector<SkillType> magic_keys = {SkillType::SKILL_MAGIC_ARCANE, SkillType::SKILL_MAGIC_CANTRIPS, SkillType::SKILL_MAGIC_DIVINE, SkillType::SKILL_MAGIC_MYSTIC, SkillType::SKILL_MAGIC_PRIMORDIAL};

  if ((lua_gettop(ls) == 1) && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      for (const auto& magic_key : magic_keys)
      {
        magic_skills[magic_key] = creature->get_skills().get_value(magic_key);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_magic_skills");
  }

  // Create a table with keys for each magic skill
  lua_createtable(ls, 0, magic_keys.size());

  for (const auto& msk_pair : magic_skills)
  {
    string table_key = to_string(static_cast<int>(msk_pair.first));
    LuaUtils::set_field(ls, table_key.c_str(), msk_pair.second);
  }

  return 1;
}

// Check a particular skill for a particular creature.
// - First argument is the creature ID
// - Second argument is the SkillType value
int check_skill(lua_State* ls)
{
  bool check_value = false;
  int num_args = lua_gettop(ls);

  if ((num_args == 2) && (lua_isstring(ls, 1) && lua_isnumber(ls, 2)))
  {
    string creature_id = lua_tostring(ls, 1);
    int skill_id = lua_tointeger(ls, 2);
    SkillType skill_name = static_cast<SkillType>(skill_id);

    CreaturePtr creature = get_creature(creature_id);

    if (creature)
    {
      SkillManager sm;

      check_value = sm.check_skill(creature, skill_name);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to check_skill");
  }

  lua_pushboolean(ls, check_value);
  return 1;
}

int set_all_skills_value(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int val = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->get_skills().set_all_to(val);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_all_skills_value");
  }

  return 0;
}

int RNG_range(lua_State* ls)
{
  int rng_val = 0;

  if ((lua_gettop(ls) == 2) && (lua_isnumber(ls, 1) && lua_isnumber(ls, 2)))
  {
    int min = lua_tointeger(ls, 1);
    int max = lua_tointeger(ls, 2);

    rng_val = RNG::range(min, max);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to RNG_range");
  }

  lua_pushnumber(ls, rng_val);
  return 1;
}

int RNG_percent_chance(lua_State* ls)
{
  int rng_val = 0;

  if ((lua_gettop(ls) == 1) && (lua_isnumber(ls, 1)))
  {
    int percent = lua_tointeger(ls, 1);

    rng_val = RNG::percent_chance(percent);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to RNG_range");
  }

  lua_pushboolean(ls, rng_val);
  return 1;
}

int RNG_dice(lua_State* ls)
{
  int rng_val = 0;
  int num_args = lua_gettop(ls);

  if ((num_args >= 2) && (lua_isnumber(ls, 1)) && (lua_isnumber(ls, 2)))
  {
    int num_dice = lua_tointeger(ls, 1);
    int dice_sides = lua_tointeger(ls, 2);
    int modifier = 0;

    if (num_args == 3 && lua_isnumber(ls, 3))
    {
      modifier = lua_tointeger(ls, 3);
    }

    rng_val = RNG::dice(num_dice, dice_sides, modifier);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to RNG_dice");
  }

  lua_pushinteger(ls, rng_val);
  return 1;
}

// Add a given number of spell castings to the spell knowledge of a
// particular creature.
int add_spell_castings(lua_State* ls)
{
  if ((lua_gettop(ls) == 3) && (lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isnumber(ls, 3)))
  {
    string creature_id = lua_tostring(ls, 1);
    string spell_id = lua_tostring(ls, 2);
    int addl_castings = lua_tointeger(ls, 3);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      SpellbookReadStrategy srs;
      srs.add_spell_castings(creature, spell_id, addl_castings);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_spell_castings");
  }

  return 0;
}

// This function is really only intended for debugging purposes,
// not for mad skills.
int add_all_spells_castings(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int addl_castings = lua_tointeger(ls, 2);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Game& game = Game::instance();
      const SpellMap& spells = game.get_spells_ref();

      for (auto& sp_pair : spells)
      {
        string spell_id = sp_pair.first;
        SpellbookReadStrategy srs;
        srs.add_spell_castings(creature, spell_id, addl_castings);
      }
    }
 }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_all_spells_castings");
  }

  return 0;
}

int count_spells_known(lua_State* ls)
{
  int spells_known = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      spells_known = creature->get_spell_knowledge().count_spells_known();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to count_spells_known");
  }

  lua_pushinteger(ls, spells_known);
  return 1;
}

// Add a certain number of experience points to a particular creature.
int gain_experience(lua_State* ls)
{
  if ((lua_gettop(ls) == 2) && (lua_isstring(ls, 1) && lua_isnumber(ls, 2)))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);
    int experience = lua_tointeger(ls, 2);

    if (creature != nullptr)
    {
      ExperienceManager em;
      em.gain_experience(creature, experience);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to gain_experience");
  }

  return 0;
}

// Get a particular creature's experience value
int get_experience_value(lua_State* ls)
{
  int xp_val = 0;

  if ((lua_gettop(ls) == 1) && (lua_isstring(ls, 1)))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      xp_val = static_cast<int>(creature->get_experience_value());
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_experience_value");
  }

  lua_pushinteger(ls, xp_val);
  return 1;
}

// Add a creature to the map at a particular (y, x) coordinate
int add_creature_to_map(lua_State* ls)
{
  int num_args = lua_gettop(ls);
  string new_creature_id;

  if ((num_args >= 3) && (lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3)))
  {
    Game& game = Game::instance();
    MapPtr map; 
    
    if (num_args >= 4 && lua_isstring(ls, 4))
    {
      string map_id = lua_tostring(ls, 4);
      map = game.get_map_registry_ref().get_map(map_id);
    }
    else
    {
      map = game.get_current_map();
    }

    // Hostility override is optional, and generally only used in places where
    // generated creatures must be hostile towards the player.
    std::shared_ptr<bool> hostility_override;
    if (num_args >= 5 && lua_isboolean(ls, 5))
    {
      hostility_override = std::make_shared<bool>(lua_toboolean(ls, 5) != 0);
    }

    bool ignore_maximum = false;
    if (num_args == 6 && lua_isboolean(ls, 6))
    {
      ignore_maximum = lua_toboolean(ls, 6);
    }

    string creature_id = lua_tostring(ls, 1);

    CreatureFactory cf;
    CreaturePtr creature = cf.create_by_creature_id(game.get_action_manager_ref(), creature_id, map, nullptr, ignore_maximum);
    Coordinate coords(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    HostilityManager hm;

    if (creature && map && MapUtils::are_coordinates_within_dimensions(coords, map->size()))
    {
      TilePtr tile = map->at(coords);

      if (tile != nullptr && MapUtils::is_tile_available_for_creature(creature, tile))
      {
        GameUtils::add_new_creature_to_map(game, creature, map, coords);

        if (hostility_override != nullptr)
        {
          hm.set_hostility_to_player(creature, *hostility_override);
        }

        new_creature_id = creature->get_id();
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_creature_to_map");
  }

  lua_pushstring(ls, new_creature_id.c_str());
  return 1;
}

// Returns a boolean - true if a creature was removed, false otherwise.
int remove_creature_from_map(lua_State* ls)
{
  bool creature_removed = false;
  int num_args = lua_gettop(ls);

  if ((num_args >= 1) && (lua_isstring(ls, 1)))
  {
    Game& game = Game::instance();
    string map_id;
    MapPtr map;

    if (num_args == 2 && lua_isstring(ls, 2))
    {
      map_id = lua_tostring(ls, 2);
    }

    if (map_id.empty())
    {
      map = game.get_current_map();
    }
    else
    {
      map = game.get_map_registry_ref().get_map(map_id);
    }

    string creature_id_or_base = lua_tostring(ls, 1);
    CreatureMap creatures = map->get_creatures();

    if (!creature_id_or_base.empty())
    {
      for (const auto& creature_pair : creatures)
      {
        CreaturePtr creature = creature_pair.second;

        if (creature != nullptr &&
          (creature->get_id() == creature_id_or_base || creature->get_original_id() == creature_id_or_base))
        {
          MapUtils::remove_creature(map, creature);

          creature_removed = true;
          break;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to remove_creature_from_map");
  }

  lua_pushboolean(ls, creature_removed);
  return 1;
}

// Add a particular status to a particular creature for a particular duration
// in minutes.
//
// Returns true if the status was added, false in all other cases.
int add_status_to_creature(lua_State* ls)
{
  if ((lua_gettop(ls) >= 2) && (lua_isstring(ls, 1) && (lua_isstring(ls, 2))))
  {
    string creature_id = lua_tostring(ls, 1);
    string status_id = lua_tostring(ls, 2);
    int danger_level = 1;

    if (lua_gettop(ls) == 3 && lua_isnumber(ls, 3))
    {
      danger_level = lua_tointeger(ls, 3);
    }

    CreaturePtr creature = get_creature(creature_id);

    if (creature && !creature->has_status(status_id))
    {
      StatusEffectPtr se = StatusEffectFactory::create_status_effect(/* don't know originator */ nullptr, status_id, "");
      se->apply_change(creature, danger_level);

      lua_pushboolean(ls, true);
      return 1;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_status_to_creature");
  }

  lua_pushboolean(ls, false);
  return 1;
}

int add_status_to_creature_at(lua_State* ls)
{
  bool added_status = false;

  if ((lua_gettop(ls) >= 3) && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isstring(ls, 3))
  {
    Game& game = Game::instance();

    int y = lua_tointeger(ls, 1);
    int x = lua_tointeger(ls, 2);
    string status_id = lua_tostring(ls, 3);
    int danger_level = 1;

    if (lua_gettop(ls) == 4 && lua_isnumber(ls, 4))
    {
      danger_level = lua_tointeger(ls, 4);
    }

    MapPtr cur_map = game.get_current_map();

    if (cur_map != nullptr)
    {
      TilePtr tile = cur_map->at(y, x);

      if (tile != nullptr && tile->has_creature())
      {
        CreaturePtr creature = tile->get_creature();

        StatusEffectPtr se = StatusEffectFactory::create_status_effect(/* don't know originator */ nullptr, status_id, "");
        se->apply_change(creature, danger_level);

        added_status = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_status_to_creature_at");
  }

  lua_pushboolean(ls, added_status);
  return 1;
}

int remove_negative_statuses_from_creature(lua_State* ls)
{
  int stat_count = 0;

  if ((lua_gettop(ls) == 1) && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);
    CreatureUtils::remove_negative_statuses_from_creature(creature);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to remove_negative_statuses_from_creature");
  }

  return stat_count;
}

// Get all the status IDs currently in force for the given creature.
int get_creature_statuses(lua_State* ls)
{
  vector<string> statuses;

  if ((lua_gettop(ls) == 1) && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      CreatureStatusMap csm = creature->get_statuses();

      for (const auto& csm_pair : csm)
      {
        Status status = csm_pair.second;

        if (status.get_value() == true)
        {
          statuses.push_back(status.get_id());
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_statuses");
  }

  for (const string& status : statuses)
  {
    lua_pushstring(ls, status.c_str());
  }

  return static_cast<int>(statuses.size());
}

// Does the creature have a particular status in force?
int creature_has_status(lua_State* ls)
{
  bool has_status = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string status_id = lua_tostring(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      has_status = creature->has_status(status_id);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to creature_has_status");
  }

  lua_pushboolean(ls, has_status);
  return 1;
}

// Set a creature's base (bare-handed) damage.
int set_creature_base_damage(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if ((num_args >= 3) && (lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3)))
  {
    string creature_id = lua_tostring(ls, 1);
    int num_dice = lua_tointeger(ls, 2);
    int num_sides = lua_tointeger(ls, 3);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Damage damage = creature->get_base_damage();
      damage.set_num_dice(num_dice);
      damage.set_dice_sides(num_sides);

      if (num_args == 4 && lua_isnumber(ls, 4))
      {
        int modifier = lua_tointeger(ls, 4);
        damage.set_modifier(modifier);
      }

      creature->set_base_damage(damage);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_base_damage");
  }

  return 0;
}

// Get a creature's base damage
int get_creature_base_damage(lua_State* ls)
{
  int num_dice = 0;
  int num_sides = 0;
  int modifier = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Damage damage = creature->get_base_damage();

      num_dice = damage.get_num_dice();
      num_sides = damage.get_dice_sides();
      modifier = damage.get_modifier();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_base_damage");
  }

  lua_pushinteger(ls, num_dice);
  lua_pushinteger(ls, num_sides);
  lua_pushinteger(ls, modifier);

  return 3;
}

// Set the creature's piety towards a deity with the given ID.
int set_creature_piety(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string deity_id;
    string creature_id = lua_tostring(ls, 1);
    int piety = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (num_args == 3 && lua_isstring(ls, 3))
    {
      deity_id = lua_tostring(ls, 3);
    }
    else
    {
      if (creature != nullptr)
      {
        deity_id = creature->get_religion().get_active_deity_id();
      }
    }

    if (creature != nullptr)
    {
      DeityRelations& dr = creature->get_religion_ref().get_deity_relations_ref();
      auto dr_it = dr.find(deity_id);

      if (dr_it != dr.end())
      {
        DeityStatus& ds = dr_it->second;
        ds.set_piety(piety);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_piety");
  }

  return 0;
}

// Get the creature's piety towards a deity with the given ID.
int get_creature_piety(lua_State* ls)
{
  int piety = 0;
  int num_args = lua_gettop(ls);

  if (num_args >= 1 && lua_isstring(ls, 1))
  {
    string deity_id;
    string creature_id = lua_tostring(ls, 1);

    CreaturePtr creature = get_creature(creature_id);

    if (num_args == 2 && lua_isstring(ls, 2))
    {
      deity_id = lua_tostring(ls, 2);
    }
    else
    {
      if (creature != nullptr)
      {
        deity_id = creature->get_religion().get_active_deity_id();
      }
    }

    if (creature != nullptr)
    {
      DeityRelations dr = creature->get_religion().get_deity_relations();
      auto dr_it = dr.find(deity_id);

      if (dr_it != dr.end())
      {
        DeityStatus ds = dr_it->second;
        piety = ds.get_piety();
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_piety");
  }

  lua_pushnumber(ls, piety);
  return 1;
}

// Increment the creature's piety towards their current deity.
int add_piety(lua_State* ls)
{
  int new_piety = -1;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int piety_increment = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      string deity_id = creature->get_religion_ref().get_active_deity_id();

      DeityRelations& dr = creature->get_religion_ref().get_deity_relations_ref();
      auto dr_it = dr.find(deity_id);

      if (dr_it != dr.end())
      {
        DeityStatus& ds = dr_it->second;
        new_piety = ds.get_piety() + piety_increment;

        ds.set_piety(new_piety);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_piety");
  }

  lua_pushinteger(ls, new_piety);
  return 1;
}

// Set the creature's deity status portion of the piety regen bonus
int set_creature_piety_regen_bonus(lua_State* ls)
{
  bool set_val = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));
    int bonus = lua_tointeger(ls, 2);

    if (creature != nullptr)
    {
      Religion& r = creature->get_religion_ref();
      DeityRelations& dr = r.get_deity_relations_ref();
      auto dr_it = dr.find(r.get_active_deity_id());

      if (dr_it != dr.end())
      {
        DeityStatus& ds = dr_it->second;
        ds.set_piety_regen_bonus(bonus);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_piety_regen_bonus");
  }

  lua_pushboolean(ls, set_val);
  return 1;
}

int get_creature_piety_regen_bonus(lua_State* ls)
{
  int regen_bonus = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      Religion& r = creature->get_religion_ref();
      DeityRelations& dr = r.get_deity_relations_ref();
      auto dr_it = dr.find(r.get_active_deity_id());

      if (dr_it != dr.end())
      {
        DeityStatus& ds = dr_it->second;
        regen_bonus = ds.get_piety_regen_bonus();
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_piety_regen_bonus");
  }

  lua_pushnumber(ls, regen_bonus);
  return 1;
}

// Set a resistance on a creature.
int set_creature_intrinsic_resist(lua_State* ls)
{
  if (lua_gettop(ls) == 3 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3))
  {
    string creature_id = lua_tostring(ls, 1);
    DamageType dt = static_cast<DamageType>(lua_tointeger(ls, 2));
    double resist_val = lua_tonumber(ls, 3);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->get_intrinsic_resistances_ref().set_resistance_value(dt, resist_val);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_intrinsic_resist");
  }

  return 0;
}

// Set a creature's speed.
int set_creature_speed(lua_State* ls)
{
  if ((lua_gettop(ls) == 2) && (lua_isstring(ls, 1) && lua_isnumber(ls, 2)))
  {
    string creature_id = lua_tostring(ls, 1);
    int new_base_speed = lua_tointeger(ls, 2);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Statistic cr_speed = creature->get_speed();

      int cur_speed = cr_speed.get_current();

      cr_speed.set_base(new_base_speed);
      cr_speed.set_current(cur_speed - (cur_speed - new_base_speed));

      creature->set_speed(cr_speed);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_speed");
  }

  return 0;
}

// Get a creature's speed.
int get_creature_speed(lua_State* ls)
{
  int speed = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      speed = creature->get_speed().get_base();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_speed");
  }

  lua_pushnumber(ls, speed);
  return 1;
}

int set_creature_str(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int val = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->get_strength_ref().set_base_current(val);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_str");
  }

  return 0;
}

int set_creature_dex(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int val = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->get_dexterity_ref().set_base_current(val);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_dex");
  }

  return 0;
}

int set_creature_agi(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int val = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->get_agility_ref().set_base_current(val);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_agi");
  }

  return 0;
}

int set_creature_hea(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int val = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->get_health_ref().set_base_current(val);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_hea");
  }

  return 0;
}

int set_creature_int(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int val = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->get_intelligence_ref().set_base_current(val);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_int");
  }

  return 0;
}

int set_creature_wil(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int val = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->get_willpower_ref().set_base_current(val);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_wil");
  }

  return 0;
}

int set_creature_cha(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int val = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->get_charisma_ref().set_base_current(val);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_cha");
  }

  return 0;
}

// Return the y and x coordinates for the given creature on the current map.
int get_creature_yx(lua_State* ls)
{
  int y = -1;
  int x = -1;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    // Find the creature in the map
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    string creature_id_or_base = lua_tostring(ls, 1);
    
    Coordinate c(-1,-1);
    const CreatureMap& creatures = current_map->get_creatures_ref();

    for (const auto& creature_pair : creatures)
    {
      CreaturePtr creature = creature_pair.second;

      if (creature != nullptr)
      {
        if (creature &&
          (creature->get_id() == creature_id_or_base || creature->get_original_id() == creature_id_or_base))
        {
          c = current_map->get_location(creature->get_id());

          // Set the return coordinates to the values from the lookup.
          y = c.first;
          x = c.second;

          break;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_yx");
  }

  lua_pushnumber(ls, y);
  lua_pushnumber(ls, x);
  return 2;
}

// Get the ID for a creature at the given coordinates
int get_creature_id(lua_State* ls)
{
  string creature_id;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2))
  { 
    int cy = lua_tointeger(ls, 1);
    int cx = lua_tointeger(ls, 2);
    string map_id;

    if (num_args == 3 && lua_isstring(ls, 3))
    {
      map_id = lua_tostring(ls, 3);
    }

    Game& game = Game::instance();
    MapPtr map;
    
    if (map_id.empty())
    {
      map = game.get_current_map();
    }
    else
    {
      map = game.get_map_registry_ref().get_map(map_id);
    }

    TilePtr tile = map->at(cy, cx);

    if (tile != nullptr && tile->has_creature())
    {
      CreaturePtr creature = tile->get_creature();
      creature_id = creature->get_id();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_id");
  }

  lua_pushstring(ls, creature_id.c_str());
  return 1;
}

int get_creature_ids(lua_State* ls)
{
  string ids_str;
  int num_args = lua_gettop(ls);
  if (num_args >= 1 && lua_isstring(ls, 1))
  {
    string map_id = lua_tostring(ls, 1);
    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);
    bool include_original_id_details = false;

    if (num_args >= 2 && lua_isboolean(ls, 2))
    {
      include_original_id_details = lua_toboolean(ls, 2);
    }

    if (map != nullptr)
    {
      vector<string> creature_ids;
      CreatureMap creatures = map->get_creatures();

      for (auto& c_pair : creatures)
      {
        CreaturePtr creature = c_pair.second;

        if (creature != nullptr)
        {
          string id_details = creature->get_id();
          
          if (include_original_id_details)
          {
            id_details = id_details + ":" + creature->get_original_id();
          }

          creature_ids.push_back(id_details);
        }
      }

      ids_str = String::create_csv_from_string_vector(creature_ids);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_ids");
  }

  lua_pushstring(ls, ids_str.c_str());
  return 1;
}

int get_creature_base_id(lua_State* ls)
{
  string creature_base_id;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2))
  {
    int cy = lua_tointeger(ls, 1);
    int cx = lua_tointeger(ls, 2);
    string map_id;

    if (num_args == 3 && lua_isstring(ls, 3))
    {
      map_id = lua_tostring(ls, 3);
    }

    Game& game = Game::instance();
    MapPtr map;

    if (map_id.empty())
    {
      map = game.get_current_map();
    }
    else
    {
      map = game.get_map_registry_ref().get_map(map_id);
    }

    TilePtr tile = map->at(cy, cx);

    if (tile != nullptr && tile->has_creature())
    {
      CreaturePtr creature = tile->get_creature();
      creature_base_id = creature->get_original_id();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_base_id");
  }

  lua_pushstring(ls, creature_base_id.c_str());
  return 1;
}

int get_creature_num_broken_conducts(lua_State* ls)
{
  int num_broken = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      num_broken = creature->get_conducts_ref().get_num_broken_conducts();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_num_broken_conducts");
  }

  lua_pushinteger(ls, num_broken);
  return 1;
}

// Return the ID of the current map
int get_current_map_id(lua_State* ls)
{
  string map_id;

  if (lua_gettop(ls) == 0)
  {
    map_id = Game::instance().get_current_map()->get_map_id();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_current_map_id");
  }

  lua_pushstring(ls, map_id.c_str());
  return 1;
}

int get_map_id(lua_State* ls)
{
  string map_id;

  if (lua_gettop(ls) == 2 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2))
  {
    int y = lua_tointeger(ls, 1);
    int x = lua_tointeger(ls, 2);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(MapID::MAP_ID_WORLD_MAP);

    if (map != nullptr)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr)
      {
        map_id = tile->get_custom_map_id();
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_map_id");
  }

  lua_pushstring(ls, map_id.c_str());
  return 1;
}

int get_map_exists(lua_State* ls)
{
  bool exists = false;

  if (lua_gettop(ls) == 2 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2))
  {
    int y = lua_tointeger(ls, 1);
    int x = lua_tointeger(ls, 2);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(MapID::MAP_ID_WORLD_MAP);

    if (map != nullptr)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr && !tile->get_custom_map_id().empty())
      {
        exists = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_map_exists");
  }

  lua_pushboolean(ls, exists);
  return 1;
}

int gain_level(lua_State* ls)
{
  if ((lua_gettop(ls) == 1) && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);
    ExperienceManager em;

    if (creature)
    {
      em.gain_experience(creature, em.get_current_experience_needed_for_level(creature, creature->get_level().get_current() + 1));
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to gain_level");
  }

  return 0;
}

int goto_level(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    uint glevel = lua_tointeger(ls, 2);
    CreaturePtr creature = get_creature(creature_id);
    uint level = creature->get_level().get_current();

    ExperienceManager em;

    if (creature)
    {
      for (uint cur_level = level; cur_level < glevel && cur_level < CreatureConstants::MAX_CREATURE_LEVEL; cur_level++)
      {
        em.gain_experience(creature, em.get_current_experience_needed_for_level(creature, cur_level + 1));
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to goto_level");
  }

  return 0;
}

int get_creature_level(lua_State* ls)
{
  int level = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature)
    {
      level = creature->get_level().get_current();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_level");
  }

  lua_pushinteger(ls, level);
  return 1;
}

int is_player(lua_State* ls)
{
  bool is_creature_player = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    is_creature_player = (creature_id == CreatureID::CREATURE_ID_PLAYER);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments supplied to is_player");
  }

  lua_pushboolean(ls, is_creature_player);
  return 1;
}

int incr_str(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isboolean(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    bool add_msg = lua_toboolean(ls, 2) != 0;

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      CreatureUtils::incr_str(creature, add_msg);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to incr_str");
  }

  return 0;
}

int incr_str_to_unburdened(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isboolean(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    bool add_msg = lua_toboolean(ls, 2) != 0;

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      BurdenLevel bl = BurdenLevelConverter::to_burden_level(creature);
      Statistic& str = creature->get_strength_ref();

      while (bl != BurdenLevel::BURDEN_LEVEL_UNBURDENED && str.get_current() != str.get_max())
      {
        CreatureUtils::incr_str(creature, add_msg);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to incr_str_to_unburdened");
  }

  return 0;
}

int incr_dex(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isboolean(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    bool add_msg = lua_toboolean(ls, 2) != 0;

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      CreatureUtils::incr_dex(creature, add_msg);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to incr_dex");
  }

  return 0;
}

int incr_agi(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isboolean(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    bool add_msg = lua_toboolean(ls, 2) != 0;

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      CreatureUtils::incr_agi(creature, add_msg);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to incr_agi");
  }

  return 0;
}

int incr_hea(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isboolean(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    bool add_msg = lua_toboolean(ls, 2) != 0;

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      CreatureUtils::incr_hea(creature, add_msg);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to incr_hea");
  }

  return 0;
}

int incr_int(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isboolean(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    bool add_msg = lua_toboolean(ls, 2) != 0;

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      CreatureUtils::incr_int(creature, add_msg);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to incr_int");
  }

  return 0;
}

int incr_wil(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isboolean(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    bool add_msg = lua_toboolean(ls, 2) != 0;

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      CreatureUtils::incr_wil(creature, add_msg);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to incr_wil");
  }

  return 0;
}

int incr_cha(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isboolean(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    bool add_msg = lua_toboolean(ls, 2) != 0;

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      CreatureUtils::incr_cha(creature, add_msg);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to incr_cha");
  }

  return 0;
}

int mark_stat(lua_State* ls)
{
  bool marked_stat = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    PrimaryStatisticType primary_stat = static_cast<PrimaryStatisticType>(lua_tointeger(ls, 2));

    CreaturePtr creature = get_creature(creature_id);

    int num_marks = 1;
    if (num_args >= 3 && lua_isnumber(ls, 3))
    {
      num_marks = lua_tointeger(ls, 3);
    }

    bool override_denom = false;
    if (num_args >= 4 && lua_isboolean(ls, 4))
    {
      override_denom = lua_toboolean(ls, 4) != 0;
    }

    if (creature != nullptr)
    {
      Statistic& stat = creature->get_statistic_ref(primary_stat);

      StatisticsMarker sm;
      StatisticsMarkerProbabilityDetails smpd(override_denom, 1);

      for (int i = 0; i < num_marks; i++)
      {
        marked_stat = sm.mark_statistic(stat, smpd);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to mark_stat");
  }

  lua_pushboolean(ls, marked_stat);
  return 1;
}

int mark_str(lua_State* ls)
{
  bool marked_str = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      StatisticsMarker sm;
      marked_str = sm.mark_strength(creature);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to mark_str");
  }

  lua_pushboolean(ls, marked_str);
  return 1;
}

int mark_dex(lua_State* ls)
{
  bool marked_dex = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      StatisticsMarker sm;
      marked_dex = sm.mark_dexterity(creature);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to mark_dex");
  }

  lua_pushboolean(ls, marked_dex);
  return 1;
}

int mark_agi(lua_State* ls)
{
  bool marked_agi = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      StatisticsMarker sm;
      marked_agi = sm.mark_agility(creature);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to mark_agi");
  }

  lua_pushboolean(ls, marked_agi);
  return 1;
}

int mark_hea(lua_State* ls)
{
  bool marked_hea = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      StatisticsMarker sm;
      marked_hea = sm.mark_health(creature);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to mark_hea");
  }

  lua_pushboolean(ls, marked_hea);
  return 1;
}

int mark_int(lua_State* ls)
{
  bool marked_int = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      StatisticsMarker sm;
      marked_int = sm.mark_intelligence(creature);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to mark_int");
  }

  lua_pushboolean(ls, marked_int);
  return 1;
}

int mark_wil(lua_State* ls)
{
  bool marked_wil = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      StatisticsMarker sm;
      marked_wil = sm.mark_willpower(creature);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to mark_wil");
  }

  lua_pushboolean(ls, marked_wil);
  return 1;
}

int mark_cha(lua_State* ls)
{
  bool marked_cha = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      StatisticsMarker sm;
      marked_cha = sm.mark_charisma(creature);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to mark_cha");
  }

  lua_pushboolean(ls, marked_cha);
  return 1;
}

int is_stat_max_marked(lua_State* ls)
{
  bool max_marked = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    PrimaryStatisticType pr_stat = static_cast<PrimaryStatisticType>(lua_tointeger(ls, 2));

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      max_marked = creature->get_statistic_ref(pr_stat).get_max_marks();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to is_stat_max_marked");
  }

  lua_pushboolean(ls, max_marked);
  return 1;
}

// Set a custom map id into the given map id at the given row and col.
int map_set_custom_map_id(lua_State* ls)
{
  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isstring(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    Coordinate c(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    string custom_map_id = lua_tostring(ls, 4);
    TilePtr tile = get_tile(map_id, c);

    if (tile)
    {
      tile->set_custom_map_id(custom_map_id);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_set_custom_map_id");
  }

  return 0;
}

// Set an extra description SID into the given map id at the given row and col.
int map_set_edesc(lua_State* ls)
{
  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isstring(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    Coordinate c(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    string extra_desc_sid = lua_tostring(ls, 4);
    TilePtr tile = get_tile(map_id, c);

    if (tile)
    {
      tile->set_extra_description_sid(extra_desc_sid);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_set_edesc");
  }

  return 0;
}

// Set a property (k,v pair) on the given map.
int map_set_property(lua_State* ls)
{
  if (lua_gettop(ls) == 3 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isstring(ls, 3))
  {
    string map_id = lua_tostring(ls, 1);
    string k = lua_tostring(ls, 2);
    string v = lua_tostring(ls, 3);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      map->set_property(k, v);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_set_property");
  }

  return 0;
}

// Get a property on the given map.
int map_get_property(lua_State* ls)
{
  string prop_val;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string map_id = lua_tostring(ls, 1);
    string k = lua_tostring(ls, 2);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      prop_val = map->get_property(k);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_get_property");
  }

  lua_pushstring(ls, prop_val.c_str());
  return 1;
}

// Set the tile subtype appropriately.
int map_set_tile_subtype(lua_State* ls)
{
  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    Coordinate c(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    TileType subtype = static_cast<TileType>(lua_tointeger(ls, 4));
    TilePtr tile = get_tile(map_id, c);

    if (tile)
    {
      tile->set_tile_subtype(subtype);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_set_tile_subtype");
  }

  return 0;
}

int map_set_tile_property(lua_State* ls)
{
  bool added_property = false;

  if (lua_gettop(ls) == 5 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isstring(ls, 4) && lua_isstring(ls, 5))
  {
    string map_id = lua_tostring(ls, 1);
    Coordinate c(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    string p_name = lua_tostring(ls, 4);
    string p_val = lua_tostring(ls, 5);

    TilePtr tile = get_tile(map_id, c);

    if (tile)
    {
      tile->set_additional_property(p_name, p_val);
      added_property = true;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_set_tile_property");
  }

  lua_pushboolean(ls, added_property);
  return 1;
}

// Add a location to the given map
int map_add_location(lua_State* ls)
{
  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    string loc = lua_tostring(ls, 2);
    Coordinate c(lua_tointeger(ls, 3), lua_tointeger(ls, 4));

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map)
    {
      map->add_or_update_location(loc, c);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_add_location");
  }

  return 0;
}

int map_fill_random(lua_State* ls)
{
  if (lua_gettop(ls) == 8 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4) && lua_isnumber(ls, 5) && lua_isnumber(ls, 6) && lua_isnumber(ls, 7) && lua_isnumber(ls, 8))
  {
    string map_id = lua_tostring(ls, 1);
    int start_row = lua_tointeger(ls, 2);
    int start_col = lua_tointeger(ls, 3);
    int end_row = lua_tointeger(ls, 4);
    int end_col = lua_tointeger(ls, 5);
    TileType orig_tt = static_cast<TileType>(lua_tointeger(ls, 6));
    TileType new_tt = static_cast<TileType>(lua_tointeger(ls, 7));
    int pct_chance = lua_tointeger(ls, 8);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      for (int row = start_row; row <= end_row; row++)
      {
        for (int col = start_col; col <= end_col; col++)
        {
          TilePtr tile = map->at(row, col);

          if (tile && tile->get_tile_type() == orig_tt && RNG::percent_chance(pct_chance))
          {
            TileGenerator tg;
            TilePtr new_tile = tg.generate(new_tt);

            // Copy over the common details
            new_tile->transform_from(tile);
            map->insert(row, col, new_tile);
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_fill_random");
  }

  return 0;
}

int map_fill_staggered(lua_State* ls)
{
  if (lua_gettop(ls) == 8 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4) && lua_isnumber(ls, 5) && lua_isnumber(ls, 6) && lua_isnumber(ls, 7) && lua_isnumber(ls, 8))
  {
    string map_id = lua_tostring(ls, 1);
    int start_row = lua_tointeger(ls, 2);
    int start_col = lua_tointeger(ls, 3);
    int end_row = lua_tointeger(ls, 4);
    int end_col = lua_tointeger(ls, 5);
    TileType orig_tt = static_cast<TileType>(lua_tointeger(ls, 6));
    TileType new_tt = static_cast<TileType>(lua_tointeger(ls, 7));
    int modulo = lua_tointeger(ls, 8);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      for (int row = start_row; row <= end_row; row++)
      {
        for (int col = start_col; col <= end_col; col++)
        {
          TilePtr tile = map->at(row, col);

          if (tile && tile->get_tile_type() == orig_tt && ((row + col) % modulo == 0))
          {
            TileGenerator tg;
            TilePtr new_tile = tg.generate(new_tt);

            // Copy over the common details
            new_tile->transform_from(tile);
            map->insert(row, col, new_tile);
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_fill_staggered");
  }

  return 0;
}

// Returns true if the tile was transformed, false otherwise.
int map_transform_tile(lua_State* ls)
{
  int result = false;

  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    Coordinate c(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    int lua_tile_type = lua_tointeger(ls, 4);

    if (lua_tile_type >= static_cast<int>(TileType::TILE_TYPE_FIRST) && lua_tile_type < static_cast<int>(TileType::TILE_TYPE_LAST))
    {
      MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

      if (map != nullptr)
      {
        TilePtr tile = map->at(c);

        if (tile != nullptr)
        {
          TileGenerator tg;

          TileType new_tile_type = static_cast<TileType>(lua_tile_type);
          TilePtr new_tile = tg.generate(new_tile_type);

          // Copy over the common details
          new_tile->transform_from(tile);
          map->insert(c.first, c.second, new_tile);
        }
        else
        {
          ostringstream ss;
          ss << "map_transform_tile - Null tile referenced in map_transform_tile: " << c.first << ", " << c.second;
          Log::instance().error(ss.str());
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_transform_tile");
  }

  lua_pushboolean(ls, result);
  return 1;
}

// Returns true if the exit was removed, false otherwise.
int map_remove_tile_exit(lua_State* ls)
{
  int result = false;

  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    Coordinate c(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    Direction dir = static_cast<Direction>(lua_tointeger(ls, 4));

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(c);

      if (tile != nullptr)
      {
        TileExitMap& tem = tile->get_tile_exit_map_ref();
        size_t n_removed = tem.erase(dir);

        if (n_removed > 0)
        {
          result = true;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_remove_tile_exit");
  }

  lua_pushboolean(ls, result);
  return 1;
}

// Returns true if the given exit was added to the given tile, false otherwise.
int map_add_tile_exit(lua_State* ls)
{
  int result = false;

  if (lua_gettop(ls) >= 5
    && lua_isstring(ls, 1)
    && lua_isnumber(ls, 2)
    && lua_isnumber(ls, 3)
    && lua_isnumber(ls, 4)
    && lua_isstring(ls, 5))
  {
    Coordinate link_to = { -1, -1 };
    bool apply_coordinate = false;

    if (lua_gettop(ls) == 7 && lua_isnumber(ls, 6) && lua_isnumber(ls, 7))
    {
      link_to.first = lua_tointeger(ls, 6);
      link_to.second = lua_tointeger(ls, 7);
      apply_coordinate = true;
    }

    string map_id = lua_tostring(ls, 1);
    Coordinate c(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    int lua_direction = lua_tointeger(ls, 4);
    string exit_map_id = lua_tostring(ls, 5);

    if (lua_direction >= CDIRECTION_SOUTH_WEST && lua_direction <= CDIRECTION_DOWN)
    {
      MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

      if (map != nullptr)
      {
        Direction d = static_cast<Direction>(lua_direction);
        MapExitPtr exit = MapExitUtils::add_exit_to_tile(map, c, d, exit_map_id);

        if (apply_coordinate && exit != nullptr)
        {
          exit->set_coordinate(link_to);
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_transform_tile");
  }

  lua_pushboolean(ls, result);
  return 1;
}

// Set the entire current map explored.
int map_set_explored(lua_State* ls)
{
  if (lua_gettop(ls) == 0)
  {
    Game& game = Game::instance();
    MapPtr cur_map = game.get_current_map();

    if (cur_map != nullptr)
    {
      TilesContainer& tiles = cur_map->get_tiles_ref();

      for (const auto& tile_pair : tiles)
      {
        TilePtr tile = tile_pair.second;

        if (tile != nullptr)
        {
          tile->set_explored(true);
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_set_explored");
  }

  return 0;
}

int map_get_name_sid(lua_State* ls)
{
  string map_name_sid;
  int num_args = lua_gettop(ls);

  if (num_args <= 1)
  {
    Game& game = Game::instance();
    MapPtr map_to_check;
    
    if (num_args == 0)
    {
      map_to_check = game.get_current_map();
    }
    else
    {
      string map_id;

      if (lua_isstring(ls, 1))
      {
        map_id = lua_tostring(ls, 1);
      }

      map_to_check = game.get_map_registry_ref().get_map(map_id);
    } 

    if (map_to_check != nullptr)
    {
      map_name_sid = map_to_check->get_name_sid();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_get_name_sid");
  }

  lua_pushstring(ls, map_name_sid.c_str());
  return 1;
}

int map_get_dimensions(lua_State* ls)
{
  int height = -1;
  int width = -1;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string map_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    MapPtr map = game.get_map_registry_ref().get_map(map_id);
    
    if (map != nullptr)
    {
      Dimensions dim = map->size();
      height = dim.get_y();
      width = dim.get_x();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_get_dimensions");
  }

  lua_pushinteger(ls, height);
  lua_pushinteger(ls, width);

  return 2;
}

int map_get_available_creature_coords(lua_State* ls)
{
  Log& log = Log::instance();
  log.trace("map_get_available_creature_coords - starting");
  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));

  int num_args = lua_gettop(ls);

  lua_newtable(ls);

  if (num_args == 5 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4) && lua_isnumber(ls, 5))
  {
    string map_id = lua_tostring(ls, 1);
    int y1 = lua_tointeger(ls, 2);
    int x1 = lua_tointeger(ls, 3);
    int y2 = lua_tointeger(ls, 4);
    int x2 = lua_tointeger(ls, 5);

    Game& game = Game::instance();
    MapPtr map = game.get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      int cnt = 1;

      for (int y = y1; y < y2; y++)
      {
        for (int x = x1; x < x2; x++)
        {
          TilePtr tile = map->at(y, x);

          if (tile && MapUtils::is_tile_available_for_creature(nullptr, tile))
          {
            lua_newtable(ls);
            lua_pushnumber(ls, y);
            lua_rawseti(ls, -2, 1);
            lua_pushnumber(ls, x);
            lua_rawseti(ls, -2, 2);
            lua_rawseti(ls, -2, cnt);

            cnt++;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_get_available_creature_coords");
  }

  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));
  log.trace("map_get_available_creature_coords - exiting");
  return 1;
}

int map_get_tile(lua_State* ls)
{
  if (lua_gettop(ls) == 3 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3))
  {
    // Create a table with 0 array elements and 3 keyed elements.
    lua_createtable(ls, 0, 3);

    string map_id = lua_tostring(ls, 1);
    int row = lua_tointeger(ls, 2);
    int col = lua_tointeger(ls, 3);

    Game& game = Game::instance();
    MapPtr map = game.get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(row, col);

      // As additional fields are needed in future, add them to the table.
      // Remember to update the last argument to lua_createtable, above.
      if (tile != nullptr)
      {
        LuaUtils::set_field(ls, "tile_type", static_cast<int>(tile->get_tile_type()));
        LuaUtils::set_field(ls, "tile_super_type", static_cast<int>(tile->get_tile_super_type()));
        LuaUtils::set_field(ls, "map_type", static_cast<int>(map->get_map_type()));
      }
    }

    return 1;
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_get_tile");
  }

  return 0;
}

int map_do_tiles_in_range_match_type(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args == 6 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4) && lua_isnumber(ls, 5) && lua_isnumber(ls, 6))
  {
    string map_id = lua_tostring(ls, 1);
    int y1 = lua_tointeger(ls, 2);
    int x1 = lua_tointeger(ls, 3);
    int y2 = lua_tointeger(ls, 4);
    int x2 = lua_tointeger(ls, 5);
    TileType tt = static_cast<TileType>(lua_tointeger(ls, 6));

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      for (int y = y1; y <= y2; y++)
      {
        for (int x = x1; x <= x2; x++)
        {
          TilePtr tile = map->at(y,x);

          if (tile != nullptr)
          {
            if (tile->get_tile_type() != tt)
            {
              lua_pushboolean(ls, false);
              return 1;
            }
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_do_tiles_in_range_match_type");
  }

  lua_pushboolean(ls, true);
  return 1;
}

int map_creature_ids_have_substring(lua_State* ls)
{
  bool has_substring = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string map_id = lua_tostring(ls, 1);
    string creature_id_substr = lua_tostring(ls, 2);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      CreatureMap creatures = map->get_creatures();

      for (const auto& cr_pair : creatures)
      {
        CreaturePtr map_creature = cr_pair.second;

        if (map_creature != nullptr)
        {
          string creature_id = map_creature->get_original_id();

          if (creature_id.find(creature_id_substr) != string::npos)
          {
            has_substring = true;
            break;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to map_creature_ids_have_substring");
  }

  lua_pushboolean(ls, has_substring);
  return 1;
}

// log some text in the given log level.
// returns true if it was logged, false otherwise
// (log is not in that level, etc)
int log(lua_State* ls)
{
  int logged = false;

  if (lua_gettop(ls) == 2 && lua_isnumber(ls, 1) && lua_isstring(ls, 2))
  {
    Log& log = Log::instance();

    int log_level = lua_tointeger(ls, 1);
    string log_msg = lua_tostring(ls, 2);

    if (log_level >= static_cast<int>(LoggingLevel::LOG_LOWEST) && log_level <= static_cast<int>(LoggingLevel::LOG_HIGHEST))
    {
      LoggingLevel ll = static_cast<LoggingLevel>(log_level);
      logged = log.log_using_level(ll, log_msg);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to log");
  }

  lua_pushboolean(ls, logged);
  return 1;
}

// No arguments expected - ignore any.
// Returns the player's title, or an empty string if that can't be determined.
int get_player_title(lua_State* ls)
{
  string title;

  Game& game = Game::instance();
  CreaturePtr player = game.get_current_player();

  if (player)
  {
    ClassManager cm;

    title = cm.get_title(player);
  }

  lua_pushstring(ls, title.c_str());
  return 1;
}

// Set the fleeing flag on a creature. This bypasses the usual checks and
// doesn't give any notifications. It is only intended for debugging.
int set_creature_at_fleeing(lua_State* ls)
{
  bool set_flag = false;

  if (lua_gettop(ls) == 2 && lua_isnumber(ls, 2) && lua_isnumber(ls, 2))
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    
    if (current_map != nullptr)
    {
      int row = lua_tointeger(ls, 1);
      int col = lua_tointeger(ls, 2);

      TilePtr tile = current_map->at(row, col);

      if (tile != nullptr)
      {
        CreaturePtr creature = tile->get_creature();

        if (creature != nullptr)
        {
          // Set the fleeing flag and set HP arbitrarily low.
          creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_COWARD, std::to_string(true));
          creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_FLEEING, std::to_string(true));

          // Ensure they're set hostile to the player
          HostilityManager hm;
          hm.set_hostility_to_player(creature, true, ThreatConstants::ACTIVE_THREAT_RATING);

          Statistic& hp = creature->get_hit_points_ref();
          hp.set_current(1);

          set_flag = true;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_at_fleeing");
  }

  lua_pushboolean(ls, set_flag);
  return 1;
}

int set_creature_current_hp(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int new_hp = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Statistic hp = creature->get_hit_points();
      hp.set_current(new_hp);

      creature->set_hit_points(hp);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_current_hp");
  }

  return 0;
}

int get_creature_current_hp(lua_State* ls)
{
  int current_hp = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      current_hp = creature->get_hit_points().get_current();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_current_hp");
  }

  lua_pushinteger(ls, current_hp);
  return 1;
}

int set_creature_base_hp(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int new_hp = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Statistic hp = creature->get_hit_points();
      hp.set_base(new_hp);

      creature->set_hit_points(hp);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_base_hp");
  }

  return 0;
}

int get_creature_base_hp(lua_State* ls)
{
  int base_hp = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      base_hp = creature->get_hit_points().get_base();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_base_hp");
  }

  lua_pushinteger(ls, base_hp);
  return 1;
}

int set_creature_current_ap(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int new_ap = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Statistic ap = creature->get_arcana_points();
      ap.set_current(new_ap);

      creature->set_arcana_points(ap);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_current_ap");
  }

  return 0;
}

int get_creature_current_ap(lua_State* ls)
{
  int current_ap = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      current_ap = creature->get_arcana_points().get_current();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_current_ap");
  }

  lua_pushinteger(ls, current_ap);
  return 1;
}

int set_creature_base_ap(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int new_ap = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Statistic ap = creature->get_arcana_points();
      ap.set_base(new_ap);

      creature->set_arcana_points(ap);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_base_ap");
  }

  return 0;
}

int get_creature_base_ap(lua_State* ls)
{
  int base_ap = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      base_ap = creature->get_arcana_points().get_base();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_base_ap");
  }

  lua_pushinteger(ls, base_ap);
  return 1;
}

int set_creature_name(lua_State* ls)
{
  bool changed_name = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string name = lua_tostring(ls, 2);

    if (!name.empty())
    {
      string map_id;

      if (num_args == 3 && lua_isstring(ls, 3))
      {
        map_id = lua_tostring(ls, 3);
      }

      CreaturePtr creature;
      
      if (map_id.empty())
      {
        creature = get_creature(creature_id);
      }
      else
      {
        creature = get_creature_from_map(creature_id, map_id);
      }

      if (creature != nullptr)
      {
        name = Naming::clean_name_or_use_default(name, creature->get_sex());
        creature->set_name(name);
        changed_name = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_name");
  }

  lua_pushboolean(ls, changed_name);
  return 1;
}

int get_creature_name(lua_State* ls)
{
  string creature_name;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature_name = creature->get_name();
    }
  }

  lua_pushstring(ls, creature_name.c_str());
  return 1;
}

int destroy_creature_equipment(lua_State* ls)
{
  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);

    CreaturePtr creature = get_creature(creature_id);

    if (creature)
    {
      Equipment& eq = creature->get_equipment();
      for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
      {
        EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(e);
        eq.remove_item(ewl);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to destroy_creature_equipment");
  }
  
  return 0;
}

int destroy_creature_inventory(lua_State* ls)
{
  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);

    CreaturePtr creature = get_creature(creature_id);

    if (creature)
    {
      IInventoryPtr inv = creature->get_inventory();

      if (inv)
      {
        inv->clear();
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to destroy_creature_inventory");
  }

  return 0;
}

int get_deity_summons(lua_State* ls)
{
  vector<string> summons;
  int num_return_vals = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string deity_id = lua_tostring(ls, 1);

    ReligionManager rm;
    Deity* deity = rm.get_deity(deity_id);

    if (deity != nullptr)
    {
      summons = deity->get_summons();
      uint summons_size = summons.size();
      num_return_vals = 1;
          
      // Create an array with n-array elements and 0 non-array elements.
      lua_createtable(ls, summons_size, 0);

      for (uint i = 0; i < summons_size; i++)
      {
        string cur_summon = summons.at(i);

        lua_pushstring(ls, cur_summon.c_str());
        lua_rawseti(ls, -2, i + 1);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_deity_summons");
  }

  return num_return_vals;
}

int get_num_deities(lua_State* ls)
{
  int num_deities = 0;

  if (lua_gettop(ls) == 0)
  {
    Game& game = Game::instance();
    num_deities = static_cast<int>(game.get_deities_cref().size());
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_num_deities");
  }

  lua_pushnumber(ls, num_deities);
  return 1;
}

// Return the number of deities removed.
int clear_deities(lua_State* ls)
{
  int num_cleared = 0;

  if (lua_gettop(ls) == 0)
  {
    DeityMap& deities = Game::instance().get_deities_ref();
    num_cleared = deities.size();

    deities.clear();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to clear_deities");
  }

  return num_cleared;
}

int summon_monsters_around_creature(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 4 && lua_istable(ls, 1) && lua_isstring(ls, 2) && lua_isnumber(ls, 3))
  {
    vector<string> monsters = LuaUtils::get_string_array_from_table(ls, 1);
    string creature_id = lua_tostring(ls, 2);
    string leader_id = creature_id;
    int num_to_summon = lua_tointeger(ls, 3);
    bool override_hostility = lua_toboolean(ls, 4) != 0;
    bool followers = false;
    string deity_id;

    if (num_args >= 5 && lua_isstring(ls, 5))
    {
      deity_id = lua_tostring(ls, 5);
    }

    if (num_args >= 6 && lua_isboolean(ls, 6))
    {
      followers = lua_toboolean(ls, 6);
    }

    if (!monsters.empty())
    {
      Game& game = Game::instance();
      MapPtr current_map = game.get_current_map();
      Coordinate creature_coord = current_map->get_location(creature_id);
      vector<Coordinate> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(current_map->size(), creature_coord.first, creature_coord.second);

      shuffle(adjacent_coords.begin(), adjacent_coords.end(), RNG::get_engine());

      int cnt = 0;
      for (const Coordinate& c : adjacent_coords)
      {
        if (cnt == num_to_summon)
        {
          break;
        }

        TilePtr tile = current_map->at(c);

        if (tile && !tile->has_creature())
        {
          string summon_id = monsters.at(RNG::range(0, monsters.size() - 1));

          CreatureFactory cf;
          CreaturePtr creature = cf.create_by_creature_id(game.get_action_manager_ref(), summon_id, current_map);

          if (creature != nullptr)
          {
            if (override_hostility)
            {
              HostilityManager hm;
              hm.set_hostility_to_player(creature, true, ThreatConstants::ACTIVE_THREAT_RATING);
            }

            if (!deity_id.empty())
            {
              creature->get_religion_ref().set_active_deity_id(deity_id);
            }

            if (followers)
            {
              CreatureUtils::set_leadership(creature, leader_id, current_map);
            }

            GameUtils::add_new_creature_to_map(game, creature, current_map, c);
          }

          cnt++;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to summon_monsters_around_creature");
  }

  return 0;
}

int summon_items_around_creature(lua_State* ls)
{
  int num_items = 0;

  if (lua_gettop(ls) == 3 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isnumber(ls, 3))
  {
    string creature_id = lua_tostring(ls, 1);
    vector<string> item_ids = String::create_string_vector_from_csv_string(lua_tostring(ls, 2));
    int pct_chance_gen_item = lua_tointeger(ls, 3);

    MapPtr current_map = Game::instance().get_current_map();
    Coordinate creature_coord = current_map->get_location(creature_id);
    vector<Coordinate> adjacent_coords = CoordUtils::get_adjacent_map_coordinates(current_map->size(), creature_coord.first, creature_coord.second);

    shuffle(adjacent_coords.begin(), adjacent_coords.end(), RNG::get_engine());

    if (!item_ids.empty())
    {
      for (const Coordinate& c : adjacent_coords)
      {
        if (RNG::percent_chance(pct_chance_gen_item))
        {
          string item_id = item_ids.at(RNG::range(0, item_ids.size()-1));
          ItemPtr item = ItemManager::create_item(item_id);
          TilePtr tile = current_map->at(c);

          if (tile != nullptr && item != nullptr)
          {
            tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
            num_items++;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to summon_items_around_creature");
  }

  lua_pushinteger(ls, num_items);
  return 1;
}

// Check to see whether the given creature on the current map is a specified
// class.
int creature_is_class(lua_State* ls)
{
  bool creature_is_class = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string class_id = lua_tostring(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    creature_is_class = (creature && creature->get_class_id() == class_id);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to creature_is_class");
  }

  lua_pushboolean(ls, creature_is_class);
  return 1;
}

// Check to see how many items (by item ID) exist in a particular creature's
// inventory.
//
// Argument 1: creature ID
// Argument 2: item ID
int get_item_count(lua_State* ls)
{
  uint count = 0;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string item_id = lua_tostring(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      IInventoryPtr inv = creature->get_inventory();
      count = inv->count_items(item_id);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_item_count");
  }

  lua_pushinteger(ls, count);
  return 1;
}

int count_currency(lua_State* ls)
{
  uint count = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      count = creature->get_inventory()->count_currency();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to count_currency");
  }

  lua_pushinteger(ls, count);
  return 1;
}

// Check to see how many unidentified items exist in the player's inventory.
// We're explicitly not considering the creature's equipment.
int get_unidentified_item_count(lua_State* ls)
{
  uint unid_count = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      // Count unid'd items in Inv
      IInventoryPtr inv = creature->get_inventory();
      ItemIdentifier iid;

      for (const auto& item : inv->get_items_cref())
      {
        if (item != nullptr && !iid.get_item_identified(item->get_base_id()))
        {
          unid_count += item->get_quantity();
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_unidentified_item_count");
  }

  lua_pushinteger(ls, static_cast<signed int>(unid_count));
  return 1;
}

// Check an item base ID to see if that item is already identified.
int is_item_identified(lua_State* ls)
{
  int is_identified = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    ItemIdentifier iid;
    string item_base_id = lua_tostring(ls, 1);

    is_identified = iid.get_item_identified(item_base_id);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to is_item_identified");
  }

  lua_pushboolean(ls, is_identified);
  return 1;
}

int get_item_value(lua_State* ls)
{
  int value = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string item_base_id = lua_tostring(ls, 1);
    const ItemMap items = Game::instance().get_items_ref();
    const auto i_it = items.find(item_base_id);

    if (i_it != items.end())
    {
      ItemPtr item = i_it->second;

      if (item != nullptr)
      {
        value = static_cast<int>(item->get_value());
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_item_value");
  }

  lua_pushinteger(ls, value);
  return 1;
}

// Select an item from the given creature's equipment or inventory.
//
// Returns three values:
// 
// - 1: whether an item was selected (boolean)
// - 2: the item's id (guid)
// - 3: the item's base id
int select_item(lua_State* ls)
{
  bool selected_item = false;
  string item_id;
  string item_base_id;

  if (lua_gettop(ls) >= 1 && lua_isstring(ls, 1))
  {
  string creature_id = lua_tostring(ls, 1);
  CreaturePtr creature = get_creature(creature_id);

  if (creature != nullptr)
  {
    int item_filter = CITEM_FILTER_NONE;

    if (lua_gettop(ls) == 2 && lua_isnumber(ls, 2))
    {
      item_filter = lua_tointeger(ls, 2);
    }

    Game& game = Game::instance();
    list<IItemFilterPtr> selected_filter = ItemFilterFactory::create_script_filter(item_filter);
    ItemPtr item = game.get_action_manager_ref().inventory(creature, creature->get_inventory(), selected_filter, {}, false, false);

    if (item != nullptr)
    {
      selected_item = true;
      item_id = item->get_id();
      item_base_id = item->get_base_id();
    }

    // Redraw the screen, since we will have moved from the inventory
    // back to the main map, and need to redraw before any confirmation
    // messages.
    game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
    game.get_display()->redraw();
  }
  }
  else
  {
  LuaUtils::log_and_raise(ls, "Incorrect arguments to select_item");
  }

  lua_pushboolean(ls, selected_item);
  lua_pushstring(ls, item_id.c_str());
  lua_pushstring(ls, item_base_id.c_str());

  return 3;
}

// Set a creature hostile towards another.
// Argument 1: Creature to set the hostility on.
// Argument 2: Creature to be hostile towards.
int set_hostility(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string hostile_creature_id = lua_tostring(ls, 1);
    string hostile_towards_id = lua_tostring(ls, 2);
    CreaturePtr creature = get_creature(hostile_creature_id);
    bool hostile = true;

    if (num_args >= 3 && lua_isstring(ls, 3))
    {
      string map_id = lua_tostring(ls, 3);
      MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

      if (map != nullptr)
      {
        creature = map->get_creature(hostile_creature_id);
      }
    }

    if (num_args >= 4 && lua_isboolean(ls, 4))
    {
      hostile = lua_toboolean(ls, 4);
    }

    if (creature != nullptr)
    {
      HostilityManager hm;

      if (hostile)
      {
        hm.set_hostility_to_creature(creature, hostile_towards_id);
      }
      else
      {
        hm.remove_hostility_to_creature(creature, hostile_towards_id);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_hostility");
  }

  return 0;
}

int set_map_hostility(lua_State* ls)
{
  int num_made_hostile = 0;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string map_id = lua_tostring(ls, 1);
    string hostile_to = lua_tostring(ls, 2);
    bool apply_to_followers = false;

    if (num_args == 3 && lua_isboolean(ls, 3))
    {
      apply_to_followers = lua_toboolean(ls, 3);
    }

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      const CreatureMap& creatures = map->get_creatures_ref();
      HostilityManager hm;

      for (const auto& c_pair : creatures)
      {
        if (c_pair.second != nullptr)
        {
          CreaturePtr creature = c_pair.second;

          if (creature->get_leader_id() != hostile_to || apply_to_followers)
          {
            hm.set_hostility_to_creature(creature, hostile_to, ThreatConstants::ACTIVE_THREAT_RATING);
            num_made_hostile++;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_map_hostility");
  }

  lua_pushinteger(ls, num_made_hostile);
  return 1;
}

int is_creature_hostile(lua_State* ls)
{
  bool is_hostile = true;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string hostile_to = lua_tostring(ls, 2);
    CreaturePtr creature_to_check = get_creature(lua_tostring(ls, 1));

    if (creature_to_check != nullptr)
    {
      is_hostile = creature_to_check->hostile_to(hostile_to);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to is_creature_hostile");
  }

  lua_pushboolean(ls, is_hostile);
  return 1;
}

int teleport(lua_State* ls)
{
  bool teleported = false;

  if (lua_gettop(ls) >= 1 && lua_isstring(ls, 1))
  {
    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    ActionManager& am = game.get_action_manager_ref();

    string creature_id = lua_tostring(ls, 1);

    if (current_map != nullptr)
    {
      pair<Coordinate, TilePtr> creature_loc = current_map->get_location_and_tile(creature_id);
      CreaturePtr creature = get_creature(creature_id);

      if (creature != nullptr)
      {
        // This version of the function should generally only be used for debug
        // testing.
        if (lua_gettop(ls) == 3 && lua_isnumber(ls, 2) && lua_isnumber(ls, 3))
        {
          int y = lua_tointeger(ls, 2);
          int x = lua_tointeger(ls, 3);

          MapPtr map = game.get_current_map();
          
          if (map != nullptr)
          {
            TilePtr tile = map->at(y, x);

            if (tile != nullptr && !tile->has_creature())
            {
              MapUtils::add_or_update_location(map, creature, make_pair(y, x), MapUtils::get_tile_for_creature(map, creature));
              teleported = true;
            }
          }
        }
        else
        {
          EffectPtr teleport_effect = EffectFactory::create_effect(EffectType::EFFECT_TYPE_TELEPORT, {}, {}, "", "");
          teleported = teleport_effect->effect(creature, &am, ItemStatus::ITEM_STATUS_BLESSED, creature_loc.first, creature_loc.second);
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to teleport");
  }

  lua_pushboolean(ls, teleported);
  return 1;
}

int get_creature_short_description_sid(lua_State* ls)
{
  string short_description_sid;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      short_description_sid = creature->get_short_description_sid();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_short_description_sid");
  }

  lua_pushstring(ls, short_description_sid.c_str());
  return 1;
}

// Get the appropriate creature description, based on whether the viewing
// creature can actually see or not.
int get_creature_description(lua_State* ls)
{
  string creature_desc;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string viewing_creature_id = lua_tostring(ls, 1);
    string creature_id = lua_tostring(ls, 2);
    bool ignore_checks = false;

    if (num_args >= 3 && lua_isboolean(ls, 3))
    {
      ignore_checks = lua_toboolean(ls, 3);
    }

    CreaturePtr viewing_creature = get_creature(viewing_creature_id);
    CreaturePtr creature = get_creature(creature_id);

    // Ignoring checks is used when information about a general creature is
    // needed (eg, for quests), rather than a specific creature (looking
    // at a particular goblin in a dungeon).
    if (ignore_checks)
    {
      const CreatureMap& c_map = Game::instance().get_creatures_ref();
      auto c_it = c_map.find(creature_id);

      if (c_it != c_map.end())
      {
        viewing_creature = c_it->second;
        creature = c_it->second;
      }
    }

    CreatureDescriber cd(viewing_creature, creature, true);
    creature_desc = cd.describe();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_description");
  }

  lua_pushstring(ls, creature_desc.c_str());
  return 1;
}

// Returns, as a pair, description and short description
int get_creature_description_sids(lua_State* ls)
{
  string desc_sid;
  string short_desc_sid;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    const CreatureMap& c_map = Game::instance().get_creatures_ref();
    string base_id = lua_tostring(ls, 1);
    auto c_it = c_map.find(base_id);

    if (c_it != c_map.end())
    {
      CreaturePtr creature = c_it->second;

      if (creature != nullptr)
      {
        desc_sid = creature->get_description_sid();
        short_desc_sid = creature->get_short_description_sid();
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_description_sids");
  }

  lua_pushstring(ls, desc_sid.c_str());
  lua_pushstring(ls, short_desc_sid.c_str());

  return 2;
}

// Argument 1: creature ID (creature that has the item)
// Argument 2: creature ID (creature to which to transfer the item)
// Argument 3: item ID
// Argument 4, optional: item quantity
int transfer_item(lua_State* ls)
{
  bool item_transferred = false;
  int num_args = lua_gettop(ls);
  bool args_ok = false;

  args_ok = (num_args >= 3 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isstring(ls, 3));

  if (num_args == 4)
  {
    args_ok = args_ok && lua_isnumber(ls, 4);
  }

  if (args_ok)
  {
    string transfer_to_creature_id = lua_tostring(ls, 1);
    string transfer_from_creature_id = lua_tostring(ls, 2);
    string item_base_id = lua_tostring(ls, 3);
    int quantity = 1;

    if (num_args == 4)
    {
      quantity = lua_tointeger(ls, 4);
    }

    CreaturePtr transfer_to_creature = get_creature(transfer_to_creature_id);
    CreaturePtr transfer_from_creature = get_creature(transfer_from_creature_id);

    if (transfer_to_creature != nullptr && transfer_from_creature != nullptr)
    {
      // Transfer the items from one inventory to the other.
      ItemManager im;
      pair<bool, vector<ItemPtr>> items = im.remove_item_from_inv_or_eq(transfer_from_creature, item_base_id, quantity);

      IInventoryPtr inv = transfer_to_creature->get_inventory();

      for (ItemPtr item : items.second)
      {
        inv->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
      }

      item_transferred = items.first;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to transfer_item");
  }

  lua_pushboolean(ls, item_transferred);
  return 1;
}

int creature_tile_has_item(lua_State* ls)
{
  bool has_item = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string object_base_id = lua_tostring(ls, 2);

    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    CreaturePtr creature = get_creature(creature_id);

    TilePtr tile = MapUtils::get_tile_for_creature(map, creature);

    IInventoryPtr inv = tile->get_items();
    ItemPtr item = inv->get_from_base_id(object_base_id);

    has_item = (item != nullptr);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to creature_tile_has_item");
  }

  lua_pushboolean(ls, static_cast<int>(has_item));
  return 1;
}

int pick_up_item(lua_State* ls)
{
  int action_cost = 0;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string object_base_id = lua_tostring(ls, 2);

    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    CreaturePtr creature = get_creature(creature_id);

    TilePtr tile = MapUtils::get_tile_for_creature(map, creature);

    IInventoryPtr inv = tile->get_items();
    ItemPtr item = inv->get_from_base_id(object_base_id);

    if (item != nullptr)
    {
      item = inv->remove_and_return(item->get_id());

      if (item != nullptr)
      {
        // Pick up the item, adding a message based on whether the item
        // went into the equipment or inventory, and from there, whether
        // the creature is the player, the player is blind, and so on.
        PickupAction pa;
        if (!pa.merge_into_equipment(creature, item))
        {
          pa.merge_or_add_into_inventory(creature, item);
        }

        action_cost = pa.get_action_cost_value(creature);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to pick_up_item");
  }

  lua_pushinteger(ls, action_cost);
  return 1;
}

int identify_item(lua_State* ls)
{
  bool identified_item = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string item_base_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    const map<string, ItemPtr>& items = game.get_items_ref();
    const auto& i_it = items.find(item_base_id);
    CreaturePtr creature = game.get_current_player();

    if (i_it != items.end())
    {
      ItemIdentifier iid;
      iid.set_item_identified(creature, i_it->second, item_base_id, true, true);
      identified_item = true;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to identify_item");
  }

  lua_pushboolean(ls, identified_item);
  return 1;
}

int identify_item_type(lua_State* ls)
{
  int num_identified = 0;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int iitype = lua_tointeger(ls, 2);
    ItemType item_type = static_cast<ItemType>(iitype);
    CreaturePtr creature = get_creature(creature_id);

    Game& game = Game::instance();
    const map<string, ItemPtr>& items = game.get_items_ref();

    if (creature && creature->get_is_player())
    {
      for (const auto& item_pair : items)
      {
        ItemIdentifier iid;
        ItemPtr item = item_pair.second;

        if (iitype == -1 || ((item->get_type() == item_type) && (!iid.get_item_identified(item, true))))
        {
          iid.set_item_identified(creature, item, item->get_base_id(), true);
          num_identified++;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to identify_item_type");
  }

  lua_pushinteger(ls, num_identified);
  return 1;
}

int calendar_add_seconds(lua_State* ls)
{
  int added_time = 0;

  if (lua_gettop(ls) == 1 && lua_isnumber(ls, 1))
  {
    int seconds = lua_tointeger(ls, 1);

    add_seconds_to_calendar(seconds, added_time);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to calendar_add_seconds");
  }

  lua_pushboolean(ls, added_time);
  return 1;
}

int calendar_add_minutes(lua_State* ls)
{
  int added_time = 0;

  if (lua_gettop(ls) == 1 && lua_isnumber(ls, 1))
  {
    int minutes = lua_tointeger(ls, 1);
    int seconds = minutes * 60;

    add_seconds_to_calendar(seconds, added_time);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to calendar_add_minutes");
  }

  lua_pushboolean(ls, added_time);
  return 1;
}

int calendar_add_hours(lua_State* ls)
{
  int added_time = 0;

  if (lua_gettop(ls) == 1 && lua_isnumber(ls, 1))
  {
    int hours = lua_tointeger(ls, 1);
    int seconds = hours * 60 * 60;

    add_seconds_to_calendar(seconds, added_time);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to calendar_add_hours");
  }

  lua_pushboolean(ls, added_time);
  return 1;
}

int calendar_add_days(lua_State* ls)
{
  int added_time = 0;

  if (lua_gettop(ls) == 1 && lua_isnumber(ls, 1))
  {
    int days = lua_tointeger(ls, 1);
    int seconds = days * 60 * 60 * 24;

    add_seconds_to_calendar(seconds, added_time);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to calendar_add_days");
  }

  lua_pushboolean(ls, added_time);
  return 1;
}

int calendar_add_years(lua_State* ls)
{
  int added_time = 0;

  if (lua_gettop(ls) == 1 && lua_isnumber(ls, 1))
  {
    int years = lua_tointeger(ls, 1);
    int seconds = years * 60 * 60 * 24 * 365;

    add_seconds_to_calendar(seconds, added_time);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to calendar_add_years");
  }

  lua_pushboolean(ls, added_time);
  return 1;
}

// THIS IS ONLY MEANT TO BE A DEBUG FUNCTION FOR TESTING PURPOSES.
// THIS SHOULDN'T BE CALLED FROM REAL CODE!
int add_kill_to_creature_mortuary(lua_State* ls)
{
  if (lua_gettop(ls) >= 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string killed_id = lua_tostring(ls, 2);

    int quantity = 1;

    if (lua_gettop(ls) == 3)
    {
      quantity = lua_tointeger(ls, 3);
    }

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      string creature_short_desc_sid;
      const CreatureMap& creatures = Game::instance().get_creatures_ref();
      const auto c_it = creatures.find(killed_id);

      if (c_it != creatures.end() && c_it->second != nullptr)
      {
        creature_short_desc_sid = c_it->second->get_short_description_sid();
      }

      Mortuary& mort = creature->get_mortuary_ref();

      for (int i = 0; i < quantity; i++)
      {
        mort.add_creature_kill(killed_id, creature_short_desc_sid);
      }

      Game& game = game.instance();
      Mortuary& global_mort = game.get_mortuary_ref();

      for (int i = 0; i < quantity; i++)
      {
        global_mort.add_creature_kill(killed_id, creature_short_desc_sid);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_kill_to_creature_mortuary");
  }

  return 0;
}

int report_coords(lua_State* ls)
{
  if (lua_gettop(ls) >= 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();
    CreaturePtr creature = get_creature(creature_id);
    
    if (creature != nullptr)
    {
      Coordinate c = MapUtils::get_coordinate_for_creature(current_map, creature);
      ostringstream msg;
      msg << "(" << c.first << "," << c.second << ")";

      IMessageManager& manager = MMF::instance();
      manager.clear_if_necessary();
      manager.add_new_message(msg.str());
      manager.send();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to report_coords");
  }

  return 0;
}

int get_player_world_map_coords(lua_State* ls)
{
  int y = -1;
  int x = -1;

  if (lua_gettop(ls) == 0)
  {
    Game& game = Game::instance();
    MapPtr world_map = game.get_current_world()->get_world(game.get_map_registry_ref());

    if (world_map != nullptr)
    {
      Coordinate c = world_map->get_location(CreatureID::CREATURE_ID_PLAYER);
      y = c.first;
      x = c.second;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_player_world_map_coords");
  }

  lua_pushinteger(ls, y);
  lua_pushinteger(ls, x);

  return 2;
}

int cast_spell(lua_State* ls)
{
  bool spell_cast = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string spell_id = lua_tostring(ls, 2);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr && !spell_id.empty())
    {
      // Try to have the given creature cast the desired spell.
      SpellcastingAction sa;
      ActionCostValue acv = sa.cast_spell(creature, spell_id);

      if (acv > 0)
      {
        spell_cast = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to cast_spell");
  }
    
  lua_pushboolean(ls, spell_cast);
  return 1;
}

int bless_equipment(lua_State* ls)
{
  int blessed_eq = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    blessed_eq = set_all_eq_to(creature, ItemStatus::ITEM_STATUS_BLESSED);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to bless_equipment");
  }

  lua_pushboolean(ls, blessed_eq);
  return 1;
}

int curse_equipment(lua_State* ls)
{
  int cursed_eq = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    cursed_eq = set_all_eq_to(creature, ItemStatus::ITEM_STATUS_CURSED);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to curse_equipment");
  }

  lua_pushboolean(ls, cursed_eq);
  return 1;
}

int bless_inventory(lua_State* ls)
{
  int blessed_inv = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      blessed_inv = set_all_inv_to(creature, ItemStatus::ITEM_STATUS_BLESSED);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to curse_inventory");
  }

  lua_pushboolean(ls, blessed_inv);
  return 1;
}

int curse_inventory(lua_State* ls)
{
  int cursed_inv = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      cursed_inv = set_all_inv_to(creature, ItemStatus::ITEM_STATUS_CURSED);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to curse_inventory");
  }

  lua_pushboolean(ls, cursed_inv);
  return 1;
}

int set_winner(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    int win_type = 0;

    if (num_args == 2 && lua_isnumber(ls, 2))
    {
      win_type = lua_tointeger(ls, 2);
    }

    if (creature != nullptr)
    {
      // Because there are multiple win conditions, and the player has the
      // option to continue playing after most of them, set a flag that says
      // whether a particular win condition is satisfied.
      string win_property = CreatureProperties::CREATURE_PROPERTIES_WINNER + "_" + to_string(win_type);
      creature->set_additional_property(win_property, to_string(true));

      Game& game = Game::instance();
      MapPtr cur_map = game.get_current_map();
      game.get_sound()->play_music(cur_map);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_winner");
  }

  return 0;
}

// Does the creature have a particular win satisfied?
int get_winner(lua_State* ls)
{
  bool winner = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string cr_id = lua_tostring(ls, 1);
    int win_type = lua_tointeger(ls, 2);
    CreaturePtr creature = get_creature(cr_id);

    if (creature != nullptr)
    {
      string win_property = CreatureProperties::CREATURE_PROPERTIES_WINNER + "_" + to_string(win_type);

      if (creature->has_additional_property(win_property))
      {
        winner = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_winner");
  }

  lua_pushboolean(ls, winner);
  return 1;
}

int get_creature_colour(lua_State* ls)
{
  int colour = static_cast<int>(Colour::COLOUR_BLACK);

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      colour = static_cast<int>(creature->get_symbol().get_colour());
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_colour");
  }

  lua_pushinteger(ls, colour);
  return 1;
}

int set_creature_colour(lua_State* ls)
{
  if (lua_gettop(ls) >= 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    Colour new_colour = static_cast<Colour>(lua_tointeger(ls, 2));

    MapPtr map = Game::instance().get_current_map();

    if (lua_gettop(ls) >= 3 && lua_isstring(ls, 3))
    {
      map = Game::instance().get_map_registry_ref().get_map(lua_tostring(ls, 3));
    }

    CreaturePtr creature;
    
    if (map != nullptr)
    {
      creature = map->get_creature(creature_id);

      if (creature != nullptr)
      {
        creature->get_symbol_ref().set_colour(new_colour);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_colour");
  }

  return 0;
}

int set_creature_evade(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    int evade = lua_tointeger(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->set_base_evade(evade);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_evade");
  }

  return 0;
}

int set_trap(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 3 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isboolean(ls, 3))
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    int row = lua_tointeger(ls, 1);
    int col = lua_tointeger(ls, 2);
    bool trap_triggered = lua_toboolean(ls, 3) != 0;

    string trap_id;

    if (num_args >= 4 && lua_isstring(ls, 4))
    {
      trap_id = lua_tostring(ls, 4);
    }

    if (num_args >= 5 && lua_isstring(ls, 5))
    {
      string map_id = lua_tostring(ls, 5);
      map = Game::instance().get_map_registry_ref().get_map(map_id);
    }

    // Create a trap with the given ID.
    if (trap_id.empty())
    { 
      GeneratorUtils::generate_trap(map, row, col, game.get_trap_info_ref(), trap_triggered);
    }
    else
    {
      GeneratorUtils::generate_trap(map, row, col, game.get_trap_info_ref(), trap_id, trap_triggered);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_trap");
  }

  return 0;
}

// Returns a variable number of arguments (the number of nearby creatures
// the creature is hostile to), with each returned value being a hostile 
// creature's id.
int get_nearby_hostile_creatures(lua_State* ls)
{
  int num_hostiles = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);
    MapPtr view_map = creature->get_decision_strategy()->get_fov_map();
    const CreatureMap& creatures = view_map->get_creatures();

    for (const auto& creature_pair : creatures)
    {
      CreaturePtr view_creature = creature_pair.second;

      if (view_creature != nullptr)
      {
        if (creature->hostile_to(creature_pair.first))
        {
          num_hostiles++;
          lua_pushstring(ls, creature_pair.first.c_str());
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_nearby_hostile_creatures");
  }

  return num_hostiles;
}

int remove_creature_additional_property(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string property = lua_tostring(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature)
    {
      creature->remove_additional_property(property);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to remove_creature_additional_property");
  }

  return 0;
}

int set_creature_additional_property(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 3 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isstring(ls, 3))
  {
    string creature_id = lua_tostring(ls, 1);
    string prop_name = lua_tostring(ls, 2);
    string prop_value = lua_tostring(ls, 3);
    Game& game = Game::instance();
    MapPtr cur_map;
    
    if (num_args == 4 && lua_isstring(ls, 4))
    {
      cur_map = game.get_map_registry_ref().get_map(lua_tostring(ls, 4));
    }
    else
    {
      cur_map = game.get_current_map();
    }

    if (cur_map != nullptr)
    {
      CreaturePtr creature = cur_map->get_creature(creature_id);

      if (creature != nullptr)
      {
        creature->set_additional_property(prop_name, prop_value);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_creature_additional_property");
  }

  return 0;
}

// Return a creature property just as the string is stored
int get_creature_additional_property(lua_State* ls)
{
  string creature_prop;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string prop_name = lua_tostring(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature_prop = creature->get_additional_property(prop_name);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_additional_property");
  }

  lua_pushstring(ls, creature_prop.c_str());
  return 1;
}

int get_creature_additional_property_csv(lua_State* ls)
{
  int num_strs = 0;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string prop_name = lua_tostring(ls, 2);

    CreaturePtr creature = get_creature(creature_id);
    string creature_prop_csv;

    if (creature != nullptr)
    {
      creature_prop_csv = creature->get_additional_property(prop_name);

      vector<string> prop_v = String::create_string_vector_from_csv_string(creature_prop_csv);

      for (const string& p : prop_v)
      {
        num_strs++;
        lua_pushstring(ls, p.c_str());
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_additional_property_csv");
  }

  return num_strs;
}

int is_creature_in_view_map(lua_State* ls)
{
  bool creature_in_map = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string map_creature_id = lua_tostring(ls, 1);
    string creature_id = lua_tostring(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      map<string, CreaturePtr> creatures = creature->get_decision_strategy()->get_fov_map()->get_creatures();

      for (const auto& c_pair : creatures)
      {
        if (c_pair.first == map_creature_id)
        {
          creature_in_map = true;
          break;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to is_creature_in_view_map");
  }

  lua_pushboolean(ls, creature_in_map);
  return 1;
}

int redraw(lua_State* ls)
{
  if (lua_gettop(ls) == 0)
  {
    Game& game = Game::instance();
    game.update_display();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to redraw");
  }

  return 0;
}

int get_race_ids(lua_State* ls)
{
  int race_cnt = 0;
  int n_args = lua_gettop(ls);

  if (n_args <= 2)
  {
    bool include_user_playable = false;
    bool include_non_slayable = false;

    if (n_args >= 1 && lua_isboolean(ls, 1))
    {
      include_user_playable = (lua_toboolean(ls, 1) != 0);
    }

    if (n_args >= 2 && lua_isboolean(ls, 2))
    {
      include_non_slayable = (lua_toboolean(ls, 2) != 0);
    }

    RaceManager rm;
    vector<string> race_ids = rm.get_race_ids(include_user_playable, include_non_slayable);

    for (const auto& race_id : race_ids)
    {
      lua_pushstring(ls, race_id.c_str());
      race_cnt++;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_race_ids");
  }

  return race_cnt;
}

int get_unarmed_slays(lua_State* ls)
{
  int slay_cnt = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      vector<string> slays = creature->get_base_damage().get_slays_races();

      for (const string& slay : slays)
      {
        lua_pushstring(ls, slay.c_str());
        slay_cnt++;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_unarmed_slays");
  }

  return slay_cnt;
}

int add_unarmed_slay(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string slay_race_id = lua_tostring(ls, 2);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Damage damage = creature->get_base_damage();
      vector<string> slays = damage.get_slays_races();

      if (std::find(slays.begin(), slays.end(), slay_race_id) == slays.end())
      {
        slays.push_back(slay_race_id);
      }

      damage.set_slays_races(slays);
      creature->set_base_damage(damage);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_unarmed_slay");
  }

  return 0;
}

int get_class_id(lua_State* ls)
{
  string class_id;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      class_id = creature->get_class_id();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_class_id");
  }

  lua_pushstring(ls, class_id.c_str());
  return 1;
}

int get_race_name(lua_State* ls)
{
  string race_name;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string race_id = lua_tostring(ls, 1);
    RaceManager rm;
    Race* race = rm.get_race(race_id);

    if (race != nullptr)
    {
      race_name = StringTable::get(race->get_race_name_sid());
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_race_name");
  }

  lua_pushstring(ls, race_name.c_str());
  return 1;
}

int set_inscription(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isstring(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    int row = lua_tointeger(ls, 2);
    int col = lua_tointeger(ls, 3);
    string inscription = lua_tostring(ls, 4);

    Game& game = Game::instance();
    MapPtr map = game.get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(row, col);

      if (tile != nullptr)
      {
        tile->set_inscription_sid(inscription);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_inscription");
  }

  return 0;
}

int get_map_dimensions(lua_State* ls)
{
  int rows = 0;
  int cols = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string map_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    MapRegistry& mr = game.get_map_registry_ref();
    MapPtr map = mr.get_map(map_id);

    if (map != nullptr)
    {
      Dimensions dim = map->size();
      rows = dim.get_y();
      cols = dim.get_x();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_map_dimensions");
  }

  lua_pushnumber(ls, rows);
  lua_pushnumber(ls, cols);

  return 2;
}

int get_coords_with_tile_type_in_range(lua_State* ls)
{
  Log& log = Log::instance();
  log.trace("get_coords_with_tile_type_in_range - starting");
  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));

  // Get the args before creating the return table.
  int num_args = lua_gettop(ls);

  // Create the table - might be empty when we return it.
  lua_newtable(ls);

  if (num_args == 6 && lua_isstring(ls, 1) 
                    && lua_isnumber(ls, 2) // y1
                    && lua_isnumber(ls, 3) // x1
                    && lua_isnumber(ls, 4) // y2
                    && lua_isnumber(ls, 5) // x2
                    && lua_isnumber(ls, 6)) // tile type
  {
    string map_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    MapRegistry& mr = game.get_map_registry_ref();
    MapPtr map = mr.get_map(map_id);

    if (map != nullptr)
    {
      int y1 = lua_tointeger(ls, 2);
      int x1 = lua_tointeger(ls, 3);
      int y2 = lua_tointeger(ls, 4);
      int x2 = lua_tointeger(ls, 5);
      TileType tt = static_cast<TileType>(lua_tointeger(ls, 6));
      int cnt = 1;

      for (int y = y1; y < y2; y++)
      {
        for (int x = x1; x < x2; x++)
        {
          TilePtr tile = map->at(y, x);

          if (tile && tile->get_tile_type() == tt)
          {
            lua_newtable(ls);
            lua_pushnumber(ls, y);
            lua_rawseti(ls, -2, 1);
            lua_pushnumber(ls, x);
            lua_rawseti(ls, -2, 2);
            lua_rawseti(ls, -2, cnt);

            cnt++;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_coords_with_tile_type_in_range");
  }

  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));
  log.trace("get_coords_with_tile_type_in_range - exiting");
  return 1;
}

int get_custom_map_id(lua_State* ls)
{
  string custom_map_id;

  if (lua_gettop(ls) == 3 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3))
  {
    string map_id = lua_tostring(ls, 1);
    int row = lua_tointeger(ls, 2);
    int col = lua_tointeger(ls, 3);

    TilePtr tile = get_tile(map_id, make_pair(row, col));

    if (tile != nullptr)
    {
      custom_map_id = tile->get_custom_map_id();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_custom_map_id");
  }

  lua_pushstring(ls, custom_map_id.c_str());
  return 1;
}

int ranged_attack(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 4 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    string attacking_creature_id = lua_tostring(ls, 1);
    string attacked_creature_id = lua_tostring(ls, 2);
    int damage_amount = lua_tointeger(ls, 3);
    DamageType dtype = static_cast<DamageType>(lua_tointeger(ls, 4));
    bool piercing = false;

    if (num_args >= 5)
    {
      piercing = lua_toboolean(ls, 5) != 0;
    }

    CreaturePtr attacking_creature;
    CreaturePtr attacked_creature;

    if (!attacking_creature_id.empty())
    {
      attacking_creature = get_creature(attacking_creature_id);
    }

    if (!attacked_creature_id.empty())
    {
      attacked_creature = get_creature(attacked_creature_id);
    }

    DamagePtr damage = std::make_shared<Damage>();
    damage->set_damage_type(dtype);
    damage->set_num_dice(damage_amount);
    damage->set_dice_sides(1);
    damage->set_piercing(piercing);

    CombatManager cm;
    cm.attack(attacking_creature, attacked_creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY, AttackSequenceType::ATTACK_SEQUENCE_INITIAL, false, damage);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to ranged_attack");
  }

  return 0;
}

int get_spellbooks(lua_State* ls)
{
  vector<string> spellbook_ids;

  if (lua_gettop(ls) == 0)
  {
    Game& game = Game::instance();
    const ItemMap& items = game.get_items_ref();

    for (const auto& item_pair : items)
    {
      ItemPtr item = item_pair.second;

      if (item != nullptr && item->get_type() == ItemType::ITEM_TYPE_SPELLBOOK)
      {
        SpellbookPtr book = dynamic_pointer_cast<Spellbook>(item);

        if (book != nullptr)
        {
          if (!book->get_spell_id().empty())
          {
            spellbook_ids.push_back(item_pair.first);
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_spellbooks");
  }

  size_t sp_size = spellbook_ids.size();

  // Create an array with n-array elements and 0 non-array elements.
  lua_createtable(ls, static_cast<int>(sp_size), 0);

  for (uint i = 0; i < sp_size; i++)
  {
    string cur_spbk_id = spellbook_ids.at(i);

    lua_pushstring(ls, cur_spbk_id.c_str());
    lua_rawseti(ls, -2, i + 1);
  }

  return 1;
}

int generate_shop(lua_State* ls)
{
  bool generated = false;

  if (lua_gettop(ls) == 7 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4) && lua_isnumber(ls, 5) && lua_isnumber(ls, 6) && lua_isboolean(ls, 7))
  {
    MapPtr map = Game::instance().get_map_registry_ref().get_map(lua_tostring(ls, 1));
    int start_y = lua_tointeger(ls, 2);
    int start_x = lua_tointeger(ls, 3);
    int height = lua_tointeger(ls, 4);
    int width = lua_tointeger(ls, 5);
    TileType wall_type = static_cast<TileType>(lua_tointeger(ls, 6));
    bool gen_door = lua_toboolean(ls, 7);

    Coordinate door_coords = SettlementGeneratorUtils::get_door_location(start_y, start_y + height, start_x, start_x + width, DirectionUtils::get_random_cardinal_direction());
    Building bldg({ start_y, start_x }, { start_y + height, start_x + width }, door_coords);
    GeneratorUtils::generate_building(map, start_y, start_x, height, width, wall_type, TileType::TILE_TYPE_DUNGEON, false);

    if (gen_door)
    {
      GeneratorUtils::generate_door(map, door_coords.first, door_coords.second);
    }

    ShopGenerator sg;
    sg.generate_shop(map, bldg);
    
    generated = true;
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to generate_shop");
  }

  lua_pushboolean(ls, generated);
  return 1;
}

int set_shop_shopkeeper_id(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string shop_id = lua_tostring(ls, 1);
    string shopkeeper_id = lua_tostring(ls, 2);
    string map_id;

    if (num_args == 3 && lua_isstring(ls, 3))
    {
      map_id = lua_tostring(ls, 3);
    }

    MapPtr map;

    if (map_id.empty())
    {
      map = Game::instance().get_current_map();
    }
    else
    {
      map = Game::instance().get_map_registry_ref().get_map(map_id);
    }

    if (map != nullptr)
    {
      std::map<string, Shop>& shops = map->get_shops_ref();
      auto m_it = shops.find(shop_id);

      if (m_it != shops.end())
      {
        m_it->second.set_shopkeeper_id(shopkeeper_id);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_shop_shopkeeper_id");
  }

  return 0;
}

int repop_shop(lua_State* ls)
{
  bool repopped = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 1 && lua_isstring(ls, 1))
  {
    string shop_id = lua_tostring(ls, 1);
    string map_id;

    if (num_args == 2 && lua_isstring(ls, 2))
    {
      map_id = lua_tostring(ls, 2);
    }

    MapPtr map;

    if (map_id.empty())
    {
      map = Game::instance().get_current_map();
    }
    else
    {
      map = Game::instance().get_map_registry_ref().get_map(map_id);
    }

    MapItemGenerator mig;
    repopped = mig.repop_shop(map, shop_id);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to repop_shop");
  }

  lua_pushboolean(ls, repopped);
  return 1;
}

int repop_shops(lua_State* ls)
{
  bool repopped = false;
  int num_args = lua_gettop(ls);

  if (num_args == 0)
  {
    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      const auto& shops = map->get_shops_ref();
      MapItemGenerator mig;

      for (const auto& s_pair : shops)
      {
        repopped = mig.repop_shop(map, s_pair.first);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to repop_shops");
  }

  lua_pushboolean(ls, repopped);
  return 1;
}

int get_num_unpaid_items(lua_State* ls)
{
  int num_unpaid = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      EquipmentMap eqm = creature->get_equipment().get_equipment();
      IInventoryPtr inv = creature->get_inventory();

      for (auto eqm_pair : eqm)
      {
        ItemPtr item = eqm_pair.second;

        if (item != nullptr && item->get_unpaid())
        {
          num_unpaid++;
        }
      }

      if (inv != nullptr)
      {
        list<ItemPtr> raw_items = inv->get_items_cref();
        for (ItemPtr item : raw_items)
        {
          if (item && item->get_unpaid())
          {
            num_unpaid++;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_num_unpaid_items");
  }

  lua_pushinteger(ls, num_unpaid);
  return 1;
}

int get_unpaid_amount(lua_State* ls)
{
  int amount = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      amount = creature->get_unpaid_amount();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_unpaid_amount");
  }

  lua_pushinteger(ls, amount);
  return 1;
}

int set_items_paid(lua_State* ls)
{
  if (lua_gettop(ls) && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->set_items_paid();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_items_paid");
  }

  return 0;
}

int bargain_discount(lua_State* ls)
{
  bool got_discount = false;
  int discount_amount = 0;

  if (lua_gettop(ls) && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      BuySellCalculator bsc;

      int pct_chance_bargain = bsc.calc_pct_chance_bargain(creature);
      int discount_pct = bsc.calc_pct_discount_buy(creature);

      if (RNG::percent_chance(pct_chance_bargain))
      {
        got_discount = true;
        discount_amount = discount_pct;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to bargain_discount");
  }

  lua_pushboolean(ls, got_discount);
  lua_pushinteger(ls, discount_amount);

  return 2;
}

int bargain_premium(lua_State* ls)
{
  bool got_prem = false;
  int prem_amount = 0;

  if (lua_gettop(ls) && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      BuySellCalculator bsc;

      int pct_chance_bargain = bsc.calc_pct_chance_bargain(creature);
      int prem_pct = bsc.calc_pct_premium_sell(creature);

      if (RNG::percent_chance(pct_chance_bargain))
      {
        got_prem = true;
        prem_amount = prem_pct;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to bargain_premium");
  }

  lua_pushboolean(ls, got_prem);
  lua_pushinteger(ls, prem_amount);

  return 2;
}

int get_item_type(lua_State* ls)
{
  ItemType item_type = ItemType::ITEM_TYPE_NULL;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string item_base_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    const ItemMap items = game.get_items_ref();
    auto i_it = items.find(item_base_id);

    if (i_it != items.end())
    {
      ItemPtr item = i_it->second;

      if (item != nullptr)
      {
        item_type = item->get_type();
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_item_type");
  }

  lua_pushinteger(ls, static_cast<int>(item_type));
  return 1;
}

int get_shop_id(lua_State* ls)
{
  string shop_id;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string shopkeeper_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();

    if (current_map != nullptr)
    {
      map<string, Shop> shops = current_map->get_shops();

      for (const auto& s_pair : shops)
      {
        Shop shop = s_pair.second;
        string shop_sk_id = shop.get_shopkeeper_id();

        if (shop_sk_id == shopkeeper_id)
        {
          shop_id = shop.get_shop_id();
          break;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_shop_id");
  }

  lua_pushstring(ls, shop_id.c_str());
  return 1;
}

int get_stocked_item_types(lua_State* ls)
{
  vector<ItemType> stocked_item_types;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string shop_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    MapPtr current_map = game.get_current_map();

    if (current_map != nullptr)
    {
      map<string, Shop> shops = current_map->get_shops();

      for (const auto& s_pair : shops)
      {
        Shop shop = s_pair.second;

        if (shop.get_shop_id() == shop_id)
        {
          stocked_item_types = shop.get_stocked_item_types();
          break;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_stocked_item_types");
  }

  size_t itypes_size = stocked_item_types.size();

  // Create an array with n-array elements and 0 non-array elements.
  lua_createtable(ls, static_cast<int>(itypes_size), 0);

  for (uint i = 0; i < itypes_size; i++)
  {
    ItemType cur_itype = stocked_item_types.at(i);

    lua_pushinteger(ls, static_cast<int>(cur_itype));
    lua_rawseti(ls, -2, i + 1);
  }

  return 1;
}

int get_sale_price(lua_State* ls)
{
  int sale_price = 0;

  if (lua_gettop(ls) == 3 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isstring(ls, 3))
  {
    int drop_y = lua_tointeger(ls, 1);
    int drop_x = lua_tointeger(ls, 2);
    string item_id = lua_tostring(ls, 3);

    MapPtr map = Game::instance().get_current_map();
    
    if (map != nullptr)
    {
      TilePtr tile = map->at(drop_y, drop_x);

      if (tile != nullptr)
      {
        ItemPtr item = tile->get_items()->get_from_id(item_id);

        BuySellCalculator bsc;
        sale_price = bsc.get_sale_price(item);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_sale_price");
  }

  lua_pushinteger(ls, sale_price);
  return 1;
}

int set_item_unpaid(lua_State* ls)
{
  int num_args = lua_gettop(ls);
  if (num_args >= 2 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2))
  {
    int drop_y = lua_tointeger(ls, 1);
    int drop_x = lua_tointeger(ls, 2);
    string item_id;

    if (num_args >= 3 && lua_isstring(ls, 3))
    {
      item_id = lua_tostring(ls, 3);
    }

    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      TilePtr tile = map->at(drop_y, drop_x);

      if (tile != nullptr)
      {
        if (!item_id.empty())
        {
          ItemPtr item = tile->get_items()->get_from_id(item_id);

          if (item != nullptr)
          {
            item->set_unpaid(true);
          }
        }
        else
        {
          list<ItemPtr>& raw_items = tile->get_items()->get_items_ref();

          for (ItemPtr item : raw_items)
          {
            if (item != nullptr)
            {
              item->set_unpaid(true);
            }
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_item_unpaid");
  }

  return 0;
}

// Intended to be used for debugging work only.
int set_item_num_generated(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    GenerationValuesMap& gvm = Game::instance().get_item_generation_values_ref();
    string item_id = lua_tostring(ls, 1);
    int val = lua_tointeger(ls, 2);

    auto gvm_it = gvm.find(item_id);

    if (gvm_it != gvm.end())
    {
      gvm_it->second.set_current(val);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_item_num_generated");
  }

  return 0;
}

int is_in_shop(lua_State* ls)
{
  bool in_shop = false;

  if (lua_gettop(ls) == 3 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isstring(ls, 3))
  {
    int drop_y = lua_tointeger(ls, 1);
    int drop_x = lua_tointeger(ls, 2);
    string shop_id = lua_tostring(ls, 3);

    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      pair<bool, string> adjacency = MapUtils::is_in_shop_or_adjacent(map, make_pair(drop_y, drop_x));

      if (adjacency.first && adjacency.second == shop_id)
      {
        in_shop = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to is_in_shop");
  }

  lua_pushboolean(ls, in_shop);
  return 1;
}

int is_item_unpaid(lua_State* ls)
{
  bool is_unpaid = true;

  if (lua_gettop(ls) == 3 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isstring(ls, 3))
  {
    int drop_y = lua_tointeger(ls, 1);
    int drop_x = lua_tointeger(ls, 2);
    string item_id = lua_tostring(ls, 3);

    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      TilePtr tile = map->at(drop_y, drop_x);

      if (tile != nullptr)
      {
        ItemPtr item = tile->get_items()->get_from_id(item_id);

        if (item != nullptr)
        {
          is_unpaid = item->get_unpaid();
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to is_item_unpaid");
  }

  lua_pushboolean(ls, is_unpaid);
  return 1;
}

int load_map(lua_State* ls)
{
  bool loaded_map = false;
  int num_args = lua_gettop(ls);

  if (num_args == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string map_id = lua_tostring(ls, 2);

    // First, clear any messages.
    MMF::instance().clear_if_necessary();

    // Next, load the map.  Clearing the messages first ensures that any
    // messages as a result of loading the map start at the beginning of
    // the message buffer.
    Game& game = Game::instance();
    CreaturePtr creature = get_creature(creature_id);
    MapPtr old_map = game.get_current_map();
    MapPtr new_map = game.get_map_registry_ref().get_map(map_id);
    TilePtr creature_tile = MapUtils::get_tile_for_creature(old_map, creature);
    GameUtils::move_to_new_map(creature_tile, old_map, new_map);
    Game::instance().get_sound()->play(SoundEffectID::TELEPORT);
    loaded_map = true;
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to load_map");
  }

  lua_pushboolean(ls, loaded_map);
  return 1;
}

int has_artifact_in_inventory(lua_State* ls)
{
  bool has_artifact = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      IInventoryPtr inv = creature->get_inventory();
      
      if (inv != nullptr)
      {
        const list<ItemPtr> items = inv->get_items_cref();

        for (ItemPtr i : items)
        {
          if (i && i->get_artifact())
          {
            has_artifact = true;
            break;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to has_artifact_in_inventory");
  }

  lua_pushboolean(ls, has_artifact);
  return 1;
}

int tile_has_creature(lua_State* ls)
{
  bool has_creature = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2))
  {
    Game& game = Game::instance();

    int y = lua_tointeger(ls, 1);
    int x = lua_tointeger(ls, 2);
    string map_id;
    MapPtr map;

    if (num_args == 3 && lua_isstring(ls, 3))
    {
      map_id = lua_tostring(ls, 3);
    }

    if (map_id.empty())
    {
      map = game.get_current_map();
    }
    else
    {
      map = game.get_map_registry_ref().get_map(map_id);
    }

    if (map != nullptr)
    {
      TilePtr tile = map->at(y, x);

      has_creature = tile && tile->has_creature();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to tile_has_creature");
  }

  lua_pushboolean(ls, has_creature);
  return 1;
}

int tile_has_feature(lua_State* ls)
{
  bool has_feature = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2))
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    string map_id;

    int row = lua_tointeger(ls, 1);
    int col = lua_tointeger(ls, 2);

    if (num_args >= 3 && lua_isstring(ls, 3))
    {
      map_id = lua_tostring(ls, 3);
      map = Game::instance().get_map_registry_ref().get_map(map_id);
    }

    if (map != nullptr)
    {
      TilePtr tile = map->at(row, col);

      if (tile != nullptr && tile->has_feature())
      {
        has_feature = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to tile_has_feature");
  }

  lua_pushboolean(ls, has_feature);
  return 1;
}

int tile_remove_feature(lua_State* ls)
{
  bool removed = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2))
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    string map_id;

    int row = lua_tointeger(ls, 1);
    int col = lua_tointeger(ls, 2);

    if (num_args >= 3 && lua_isstring(ls, 3))
    {
      map_id = lua_tostring(ls, 3);
      map = Game::instance().get_map_registry_ref().get_map(map_id);
    }

    if (map != nullptr)
    {
      TilePtr tile = map->at(row, col);

      if (tile != nullptr && tile->has_feature())
      {
        tile->remove_feature();
        removed = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to tile_remove_feature");
  }

  lua_pushboolean(ls, removed);
  return 1;
}

int tile_is_feature_hidden(lua_State* ls)
{
  bool hidden = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2))
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    string map_id;

    int row = lua_tointeger(ls, 1);
    int col = lua_tointeger(ls, 2);

    if (num_args >= 3 && lua_isstring(ls, 3))
    {
      map_id = lua_tostring(ls, 3);
      map = Game::instance().get_map_registry_ref().get_map(map_id);
    }

    if (map != nullptr)
    {
      TilePtr tile = map->at(row, col);

      if (tile != nullptr && tile->has_feature())
      {
        hidden = tile->get_feature()->get_is_hidden();
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to tile_is_feature_hidden");
  }

  lua_pushboolean(ls, hidden);
  return 1;
}

int get_creature_original_id(lua_State* ls)
{
  string creature_original_id;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature_original_id = creature->get_original_id();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_creature_original_id");
  }

  lua_pushstring(ls, creature_original_id.c_str());
  return 1;
}

int remove_threat_from_all(lua_State* ls)
{
  int num_affected = 0;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_original_id = lua_tostring(ls, 1);
    string threat_id = lua_tostring(ls, 2);

    // Go through all the creatures in the game.  Any whose original ID
    // matches the provided original ID will remove the given threat ID.
    Game& game = Game::instance();
    HostilityManager hm;
    MapRegistryMap& maps = game.get_map_registry_ref().get_maps_ref();

    for (auto& map_pair : maps)
    {
      MapPtr map = map_pair.second;

      if (map != nullptr)
      {
        CreatureMap creatures = map->get_creatures();

        for (auto& creature_pair : creatures)
        {
          CreaturePtr creature = creature_pair.second;

          if (creature != nullptr && creature->get_original_id() == creature_original_id)
          {
            hm.remove_hostility_to_creature(creature, threat_id);
            num_affected++;            
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to remove_threat_from_all");
  }

  lua_pushinteger(ls, num_affected);
  return 1;
}

int stop_playing_game(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isboolean(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    bool do_dump = lua_toboolean(ls, 2) != 0;
    bool delete_savefile = true;
    CreaturePtr player = get_creature(creature_id);

    // Assumption: saving isn't done via Lua and therefore the savefile should
    // always be deleted.
    Game& game = Game::instance();
    game.stop_playing(player, do_dump, delete_savefile);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to stop_playing_game");
  }

  return 0;
}

bool set_all_eq_to(CreaturePtr creature, const ItemStatus status)
{
  bool eq_set = false;

  if (creature != nullptr)
  {
    EquipmentMap eq_map = creature->get_equipment().get_equipment();

    for (auto& eq_pair : eq_map)
    {
      ItemPtr item = eq_pair.second;

      if (item != nullptr)
      {
        item->set_status(status);
        eq_set = true;
      }
    }
  }

  return eq_set;
}

bool set_all_inv_to(CreaturePtr creature, const ItemStatus status)
{
  bool inv_set = false;

  if (creature != nullptr)
  {
    IInventoryPtr inv = creature->get_inventory();

    if (inv != nullptr)
    {
      list<ItemPtr> items = inv->get_items_ref();

      for (ItemPtr item : items)
      {
        if (item != nullptr)
        {
          item->set_status(status);
          inv_set = true;
        }
      }
    }
  }

  return inv_set;
}

int generate_city_feature(lua_State* ls)
{
  bool feature_generated = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 6 && lua_isstring(ls, 1) 
                    && lua_isnumber(ls, 2)
                    && lua_isnumber(ls, 3)
                    && lua_isnumber(ls, 4)
                    && lua_isnumber(ls, 5)
                    && lua_isnumber(ls, 6))
  {
    string map_id = lua_tostring(ls, 1);
    int row_start = lua_tointeger(ls, 2);
    int col_start = lua_tointeger(ls, 3);
    int row_end = lua_tointeger(ls, 4);
    int col_end = lua_tointeger(ls, 5);
    CitySectorType sector_type = static_cast<CitySectorType>(lua_tointeger(ls, 6));

    int sector_feature_type = -1;

    if (num_args >= 7 && lua_isnumber(ls, 7))
    {
      sector_feature_type = lua_tointeger(ls, 7);
    }

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      CitySectorGenerator csg;
      csg.generate_feature(map, make_pair(row_start, col_start), make_pair(row_end, col_end), sector_type, sector_feature_type);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to generate_city_feature");
  }

  lua_pushboolean(ls, feature_generated);
  return 1;
}

// Debug function for making dungeon dives quicker.
int get_staircase_coords(lua_State* ls)
{
  int y = 0;
  int x = 0;

  if (lua_gettop(ls) == 1 && lua_isnumber(ls, 1))
  {
    TileType tile_type = static_cast<TileType>(lua_tointeger(ls, 1));
    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      string loc_name = MapProperties::MAP_PROPERTIES_DEFAULT_DOWN_STAIRCASE;

      if (tile_type == TileType::TILE_TYPE_UP_STAIRCASE)
      {
        loc_name = MapProperties::MAP_PROPERTIES_DEFAULT_UP_STAIRCASE;
      }

      Coordinate c = map->get_location(loc_name);

      y = c.first;
      x = c.second;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_staircase_coords");
  }

  lua_pushinteger(ls, y);
  lua_pushinteger(ls, x);

  return 2;
}

int get_num_conducts(lua_State* ls)
{
  int num_conducts = 0;

  if (lua_gettop(ls) == 0)
  {
    num_conducts = static_cast<int>(ConductType::CONDUCT_SIZE);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_num_conducts");
  }

  lua_pushinteger(ls, num_conducts);
  return 1;
}

int break_conduct(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    ConductType ct = static_cast<ConductType>(lua_tointeger(ls, 2));
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->get_conducts_ref().break_conduct(ct);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to break_conduct");
  }

  return 0;
}

int add_membership(lua_State* ls)
{
  bool mem_added = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 3 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isstring(ls, 3))
  {
    string creature_id = lua_tostring(ls, 1);
    string membership_id = lua_tostring(ls, 2);
    string desc_sid = lua_tostring(ls, 3);
    set<string> excluded_memberships;

    if (num_args == 4 && lua_isstring(ls, 4))
    {
      string excl = lua_tostring(ls, 4);

      if (!excl.empty())
      {
        vector<string> excl_v = String::create_string_vector_from_csv_string(excl);
        excluded_memberships.insert(excl_v.begin(), excl_v.end());
      }
    }

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Membership mem(membership_id, desc_sid, excluded_memberships);
      mem_added = creature->get_memberships_ref().add_membership(membership_id, mem);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to add_membership");
  }

  lua_pushboolean(ls, mem_added);
  return 1;
}

int has_membership(lua_State* ls)
{
  int mem = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string membership_id = lua_tostring(ls, 2);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      mem = creature->get_memberships_ref().has_membership(membership_id);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to has_membership");
  }

  lua_pushboolean(ls, mem);
  return 1;
}

int is_membership_excluded(lua_State* ls)
{
  bool excl = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    string membership_id = lua_tostring(ls, 2);
    
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      set<string> excluded_memberships = creature->get_memberships_ref().get_excluded_memberships();
      auto e_it = excluded_memberships.find(membership_id);

      if (e_it != excluded_memberships.end())
      {
        excl = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to is_membership_excluded");
  }

  lua_pushboolean(ls, excl);
  return 1;
}

int dig_rectangles(lua_State* ls)
{
  Log& log = Log::instance();
  log.trace("dig_rectangles - starting");
  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));

  int num_args = lua_gettop(ls);
  lua_newtable(ls);

  if (num_args == 6 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4) && lua_isnumber(ls, 5) && lua_isnumber(ls, 6))
  {
    string map_id = lua_tostring(ls, 1);
    int sy = lua_tointeger(ls, 2);
    int sx = lua_tointeger(ls, 3);
    int ey = lua_tointeger(ls, 4);
    int ex = lua_tointeger(ls, 5);
    int num_rect = lua_tointeger(ls, 6);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      vector<pair<Coordinate, Coordinate>> rectangles = GeneratorUtils::generate_rectangles(map, sy, sx, ey, ex, num_rect, TileType::TILE_TYPE_DUNGEON);
      int cnt = 1;

      for (const auto& rect : rectangles)
      {
        lua_newtable(ls);
        lua_pushnumber(ls, rect.first.first);
        lua_rawseti(ls, -2, 1);
        lua_pushnumber(ls, rect.first.second);
        lua_rawseti(ls, -2, 2);
        lua_pushnumber(ls, rect.second.first);
        lua_rawseti(ls, -2, 3);
        lua_pushnumber(ls, rect.second.second);
        lua_rawseti(ls, -2, 4);
        lua_rawseti(ls, -2, cnt);

        cnt++;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to dig_rectangles");
  }

  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));
  log.trace("dig_rectangles - exiting");
  return 1;
}

int get_object_ids_by_type(lua_State* ls)
{
  int num_args = lua_gettop(ls);
  vector<string> object_ids;

  if (num_args == 3 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3))
  {
    ItemType itype = static_cast<ItemType>(lua_tointeger(ls, 1));
    int min_danger = lua_tointeger(ls, 2);
    int max_danger = lua_tointeger(ls, 3);

    GenerationValuesMap& gvm = Game::instance().get_item_generation_values_ref();

    for (auto& gvm_pair : gvm)
    {
      int danger_level = gvm_pair.second.get_danger_level();

      if (danger_level >= min_danger && danger_level <= max_danger)
      {
        ItemType item_itype_prop = static_cast<ItemType>(String::to_int(gvm_pair.second.get_property(GenerationProperties::GENERATION_PROPERTIES_ITEM_TYPE)));

        if (item_itype_prop == itype)
        {
          object_ids.push_back(gvm_pair.first);
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_object_ids_by_type");
  }

  LuaUtils::create_return_table_from_string_vector(ls, object_ids);
  return 1;
}


int create_menu(lua_State* ls)
{
  string selected_id;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isstring(ls, 1) && lua_istable(ls, 2))
  {
    string title_sid = lua_tostring(ls, 1);
    vector<string> table_options = LuaUtils::get_string_array_from_table(ls, 2);
    TextDisplayFormatter tdf;
    vector<TextDisplayPair> tdp;
    Game& game = Game::instance();

    if (num_args >= 3 && lua_isstring(ls, 3))
    {
      // We may be getting a SID here, but it might be pre-formatted text
      // as well.
      string text_sid = lua_tostring(ls, 3);
      string text = StringTable::get_default(text_sid, text_sid);
      vector<string> intro_formatted = tdf.format_text(text, Screen::get_lines_displayable_area(game.get_display()));

      for (auto& intro_s : intro_formatted)
      {
        tdp.push_back(make_pair(Colour::COLOUR_WHITE, intro_s));
      }
    }

    {
      OptionScreen os(Game::instance().get_display(), title_sid, tdp, table_options);
      string display_s = os.display();
      char screen_selection = display_s.at(0);
      selected_id = os.get_option(screen_selection);
    }

    // Redraw after the option screen has been removed from
    // the internal stack.
    Game::instance().update_display();
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to create_menu");
  }

  lua_pushstring(ls, selected_id.c_str());
  return 1;
}

int set_sentinel(lua_State* ls)
{
  bool set_sent_val = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 3 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isboolean(ls, 3))
  {
    int row = lua_tointeger(ls, 1);
    int col = lua_tointeger(ls, 2);
    bool val = lua_toboolean(ls, 3);

    MapPtr map = Game::instance().get_current_map();

    if (num_args >= 4 && lua_isstring(ls, 4))
    {
      map = Game::instance().get_map_registry_ref().get_map(lua_tostring(ls, 3));
    }

    if (map != nullptr)
    {
      TilePtr tile = map->at(row, col);

      if (tile != nullptr && tile->has_creature())
      {
        CreaturePtr creature = tile->get_creature();
        creature->get_decision_strategy()->set_property(DecisionStrategyProperties::DECISION_STRATEGY_SENTINEL, std::to_string(val));
        set_sent_val = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_sentinel");
  }

  lua_pushboolean(ls, set_sent_val);
  return 1;
}

int get_sid(lua_State* ls)
{
  string str;
  int num_args = lua_gettop(ls);

  if (num_args >= 1 && lua_isstring(ls, 1))
  {
    string sid = lua_tostring(ls, 1);
    str = StringTable::get(sid);

    if (num_args >= 2 && lua_istable(ls, 2))
    {
      str = read_sid_and_replace_values(ls);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_sid");
  }

  lua_pushstring(ls, str.c_str());
  return 1;
}

int set_automove_coords(lua_State* ls)
{
  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    string creature_id = lua_tostring(ls, 1);
    string map_id = lua_tostring(ls, 2);
    int am_y = lua_tointeger(ls, 3);
    int am_x = lua_tointeger(ls, 4);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      CreaturePtr creature = map->get_creature(creature_id);

      if (creature != nullptr)
      {
        DecisionStrategy* dec = creature->get_decision_strategy();

        if (dec != nullptr)
        {
          dec->set_automove_coords(make_pair(am_y, am_x));
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_automove_coords");
  }

  return 0;
}

int set_decision_strategy_property(lua_State* ls)
{
  if (lua_gettop(ls) == 4 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isstring(ls, 3) && lua_isstring(ls, 4))
  {
    int row = lua_tointeger(ls, 1);
    int col = lua_tointeger(ls, 2);
    string prop = lua_tostring(ls, 3);
    string val = lua_tostring(ls, 4);

    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      TilePtr tile = map->at(row, col);

      if (tile && tile->has_creature())
      {
        CreaturePtr creature = tile->get_creature();
        creature->get_decision_strategy()->set_property(prop, val);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_decision_strategy_property");
  }

  return 0;
}

int set_event_script(lua_State* ls)
{
  if (lua_gettop(ls) == 5 && 
      lua_isstring(ls, 1) && 
      lua_isstring(ls, 2) && 
      lua_isstring(ls, 3) && 
      lua_isstring(ls, 4) && 
      lua_isnumber(ls, 5))
  {
    string creature_id = lua_tostring(ls, 1);
    string map_id = lua_tostring(ls, 2);
    string script = lua_tostring(ls, 3);
    string event_id = lua_tostring(ls, 4);
    int pct_chance = lua_tointeger(ls, 5);

    CreaturePtr creature = get_creature_from_map(creature_id, map_id);

    if (creature != nullptr)
    {
      ScriptDetails sd;
      sd.set_chance(pct_chance);
      sd.set_script(script);

      creature->get_event_scripts_ref().insert(make_pair(event_id, sd));
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to set_event_script");
  }

  return 0;
}

int get_random_hostile_creature_id(lua_State* ls)
{
  string creature_id;

  if (lua_gettop(ls) == 3 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3))
  {
    MapType mt = MapType::MAP_TYPE_OVERWORLD;
    MapPtr current_map = Game::instance().get_current_map();

    if (current_map != nullptr)
    {
      mt = current_map->get_map_type();
    }

    int min_level = lua_tointeger(ls, 1);
    int max_level = lua_tointeger(ls, 2);
    TileType tile_type = static_cast<TileType>(lua_tointeger(ls, 3));

    CreatureGenerationManager cgm;
    CreatureGenerationIndex cgi = cgm.generate_creature_generation_map({ tile_type }, true, false, mt, min_level, max_level, Rarity::RARITY_COMMON, {});
    vector<string> possible_ids;
    CreatureGenerationList cgl = cgi.get();

    for (auto cgl_pair : cgl)
    {
      if (cgl_pair.get_creature_generation_values().get_friendly() == false)
      {
        possible_ids.push_back(cgl_pair.get_creature_base_id());
      }
    }

    if (possible_ids.size() > 0)
    {
      creature_id = possible_ids.at(RNG::range(0, possible_ids.size()-1));
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to get_random_hostile_creature_id");
  }

  lua_pushstring(ls, creature_id.c_str());
  return 1;
}

int generate_item(lua_State* ls)
{
  bool generated = false;
  string item_id;
  int num_args = lua_gettop(ls);

  if (num_args >= 6 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isstring(ls, 3) && lua_isnumber(ls, 4) && lua_isnumber(ls, 5))
  {
    int y = lua_tointeger(ls, 1);
    int x = lua_tointeger(ls, 2);
    string itypes = lua_tostring(ls, 3);
    int min_danger = lua_tointeger(ls, 4);
    int max_danger = lua_tointeger(ls, 5);
    int min_value = lua_tointeger(ls, 6);
    int num_enchants = 0;

    Rarity rarity = Rarity::RARITY_COMMON;
    vector<ItemType> item_type_restr;

    // JCD FIXME: If this ever gets needed elsewhere in the Lua code, maybe
    // refactor into a common conversion function.
    if (!itypes.empty())
    {
      vector<string> itypes_vs = String::create_string_vector_from_csv_string(itypes);
      
      for (const string& itype_s : itypes_vs)
      {
        ItemType itype = static_cast<ItemType>(String::to_int(itype_s));
        item_type_restr.push_back(itype);
      }
    }

    if (num_args >= 7 && lua_isnumber(ls, 7))
    {
      num_enchants = lua_tointeger(ls, 7);
    }

    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (num_args >= 8 && lua_isstring(ls, 8))
    {
      string map_id = lua_tostring(ls, 8);
      map = game.get_map_registry_ref().get_map(map_id);
    }

    ItemEnchantmentCalculator iec;
    ItemGenerationManager igm;
    ItemGenerationMap generation_map = igm.generate_item_generation_map({min_danger, max_danger, rarity, item_type_restr, min_value});
    ItemPtr item = igm.generate_item(game.get_action_manager_ref(), generation_map, rarity, item_type_restr, iec.calculate_enchantments(max_danger));
    int pct_chance_brand = iec.calculate_pct_chance_brand(1.0, item);

    if (item != nullptr)
    {
      // Any free extra enchants.
      item->enchant(pct_chance_brand, num_enchants);

      if (map != nullptr && item != nullptr)
      {
        TilePtr tile = map->at(y, x);

        if (tile != nullptr)
        {
          tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);

          generated = true;
          item_id = item->get_id();
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls,  "Invalid arguments to generate_item");
  }

  lua_pushboolean(ls, generated);
  lua_pushstring(ls, item_id.c_str());

  return 2;
}

int generate_creature(lua_State* ls)
{
  bool creature_generated = false;

  if (lua_gettop(ls) >= 6 && 
      lua_isstring(ls, 1) && 
      lua_isnumber(ls, 2) && 
      lua_isnumber(ls, 3) && 
      lua_isnumber(ls, 4) && 
      lua_isnumber(ls, 5) && 
      lua_isnumber(ls, 6))
  {
    Game& game = Game::instance();
    string map_id = lua_tostring(ls, 1);
    TileType map_terrain_type = static_cast<TileType>(lua_tointeger(ls, 2));
    int y = lua_tointeger(ls, 3);
    int x = lua_tointeger(ls, 4);
    int min_danger = lua_tointeger(ls, 5);
    int max_danger = lua_tointeger(ls, 6);
    int hostility_level = ThreatConstants::INITIAL_THREAT_RATING;
    
    if (lua_gettop(ls) >= 7 && lua_isnumber(ls, 7))
    {
      hostility_level = lua_tointeger(ls, 7);
    }

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr && !tile->has_creature())
      {
        CreatureGenerationManager cgm;
        CreatureGenerationList generation_list = cgm.generate_creature_generation_map({ map_terrain_type }, map->get_permanent(), map->is_islet(), map->get_map_type(), min_danger, max_danger, Rarity::RARITY_COMMON /* hardcode for now */, {}).get();
        CreaturePtr creature = cgm.generate_creature(game.get_action_manager_ref(), generation_list, map);
        HostilityManager hm;
        bool hostile = false;

        if (hostility_level > ThreatConstants::DISLIKE_THREAT_RATING)
        {
          hostile = true;
        }
        
        hm.set_hostility_to_player(creature, hostile, hostility_level);

        if (creature != nullptr)
        {
          creature_generated = true;
          GameUtils::add_new_creature_to_map(game, creature, map, {y, x});
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to generate_creature");
  }

  lua_pushboolean(ls, creature_generated);
  return 1;
}

int set_creature_id(lua_State* ls)
{
  bool id_set = false;

  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    int y = lua_tointeger(ls, 2);
    int x = lua_tointeger(ls, 3);
    string new_creature_id = lua_tostring(ls, 4);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr && tile->has_creature())
      {
        CreaturePtr creature = tile->get_creature();
        creature->set_id(new_creature_id);

        id_set = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_creature_id");
  }

  lua_pushboolean(ls, id_set);
  return 1;
}

int add_all_items_to_player_tile(lua_State* ls)
{
  if (lua_gettop(ls) == 0)
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (map != nullptr)
    {
      CreaturePtr player = game.get_current_player();
      TilePtr player_tile = MapUtils::get_tile_for_creature(map, player);
      IInventoryPtr inv = player_tile->get_items();
      const ItemMap& items = game.get_items_ref();

      if (inv != nullptr)
      {
        for (auto item_pair : items)
        {
          string item_id = item_pair.first;
          ItemPtr item = ItemManager::create_item(item_id);

          if (item != nullptr)
          {
            inv->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to add_all_items_to_player_tile");
  }

  return 0;
}

int get_primordial_castings(lua_State* ls)
{
  int castings = 0;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    PrimordialCalculator pc;
    string creature_id = lua_tostring(ls, 1);
    int base_castings = lua_tointeger(ls, 2);
    
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      castings = base_castings + RNG::range(0, pc.get_max_skill_castings(creature));
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_primordial castings");
  }

  lua_pushnumber(ls, castings);
  return 1;
}

int creature_exists(lua_State* ls)
{
  bool creature_exists = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      creature_exists = true;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to creature_exists");
  }

  lua_pushboolean(ls, creature_exists);
  return 1;
}

int set_weather(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    MapPtr map = Game::instance().get_current_map();
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));
    int wind_speed = lua_tointeger(ls, 2);

    if (creature != nullptr && map != nullptr)
    {
      TilePtr creature_tile = MapUtils::get_tile_for_creature(map, creature);
      WeatherPtr w = MapUtils::get_weather(map, creature_tile);

      if (w != nullptr)
      {
        w->set_wind_speed(wind_speed);

        WorldWeatherUpdater wwu;
        wwu.set_weather(map, creature_tile, *w);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_weather");
  }

  return 0;
}

// Clear all non-player creatures from the current map.
// If an argument is given, clear that race ID.
int genocide(lua_State* ls)
{
  int num_removed = 0;
  MapPtr map = Game::instance().get_current_map();
  string race_id;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    race_id = lua_tostring(ls, 1);
  }

  if (map != nullptr)
  {
    const CreatureMap creatures = map->get_creatures();

    for (auto cr_pair : creatures)
    {
      CreaturePtr creature = cr_pair.second;

      if (creature != nullptr && 
          !creature->get_is_player() &&
          (race_id.empty() || race_id == creature->get_race_id()))
      {
        MapUtils::remove_creature(map, creature);
        num_removed++;
      }
    }
  }

  lua_pushboolean(ls, num_removed);
  return 1;
}

int genocide_creature(lua_State* ls)
{
  int num_removed = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_original_id = lua_tostring(ls, 1);
    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      const CreatureMap creatures = map->get_creatures();

      for (auto cr_pair : creatures)
      {
        CreaturePtr creature = cr_pair.second;

        if (creature != nullptr &&
           !creature->get_is_player() &&
            creature->get_original_id() == creature_original_id)
        {
          MapUtils::remove_creature(map, creature);
          num_removed++;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to genocide_creature");
  }

  lua_pushinteger(ls, num_removed);
  return 1;
}

int genocide_hostile(lua_State* ls)
{
  int num_removed = 0;
  MapPtr map = Game::instance().get_current_map();
  string race_id;

  if (lua_gettop(ls) == 0)
  {
    if (map != nullptr)
    {
      const CreatureMap creatures = map->get_creatures();

      for (auto cr_pair : creatures)
      {
        CreaturePtr creature = cr_pair.second;

        if (creature != nullptr && 
            !creature->get_is_player() &&
            creature->hostile_to(CreatureID::CREATURE_ID_PLAYER))
        {
          MapUtils::remove_creature(map, creature);
          num_removed++;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to genocide_hostile");
  }

  lua_pushinteger(ls, num_removed);
  return 1;
}

int generate_ancient_beast(lua_State* ls)
{
  bool generated = false;

  if (lua_gettop(ls) == 3)
  {
    int y = lua_tointeger(ls, 1);
    int x = lua_tointeger(ls, 2);
    int dtype = lua_tointeger(ls, 3);

    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (map != nullptr)
    {
      CreatureGenerationManager cgm;
      CreatureGenerationIndex cgi = cgm.generate_ancient_beasts(CreatureGenerationManager::ANCIENT_BEASTS_MIN_DANGER_LEVEL, MapType::MAP_TYPE_UNDERWORLD, map->get_terrain_type());
      CreatureGenerationList cgl = cgi.get();

      auto cgl_val = cgl.at(dtype);

      // Clear the list and then add back the val to ensure we generate
      // the right ancient beast.
      cgl.clear();
      cgl.push_back(cgl_val);

      ActionManager& am = game.get_action_manager_ref();
      CreaturePtr generated_creature = cgm.generate_creature(am, cgl, map);
      GameUtils::add_new_creature_to_map(game, generated_creature, map, { y,x });
      generated = true;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to generate_ancient_beast");
  }

  lua_pushboolean(ls, generated);
  return 1;
}

int generate_hireling(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    Game& game = Game::instance();
    string map_id = lua_tostring(ls, 1);
    MapPtr map = game.get_map_registry_ref().get_map(map_id);
    int y = lua_tointeger(ls, 2);
    int x = lua_tointeger(ls, 3);
    int lvl = lua_tointeger(ls, 4);
    string race_id;
    string class_id;

    if (num_args >= 5 && lua_isstring(ls, 5))
    {
      race_id = lua_tostring(ls, 5);
    }

    if (num_args >= 6 && lua_isstring(ls, 6))
    {
      class_id = lua_tostring(ls, 6);
    }

    if (map != nullptr)
    {
      CreatureGenerationManager cgm;
      CreaturePtr hireling = cgm.generate_follower(game.get_action_manager_ref(), map, FollowerType::FOLLOWER_TYPE_HIRELING, lvl, race_id, class_id);

      GameUtils::add_new_creature_to_map(game, hireling, map, { y,x });
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to generate_hireling");
  }

  return 0;
}

int generate_adventurer(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    Game& game = Game::instance();
    string map_id = lua_tostring(ls, 1);
    MapPtr map = game.get_map_registry_ref().get_map(map_id);
    int y = lua_tointeger(ls, 2);
    int x = lua_tointeger(ls, 3);
    int lvl = lua_tointeger(ls, 4);
    string race_id;
    string class_id;

    if (num_args >= 5 && lua_isstring(ls, 5))
    {
      race_id = lua_tostring(ls, 5);
    }

    if (num_args >= 6 && lua_isstring(ls, 6))
    {
      class_id = lua_tostring(ls, 6);
    }

    if (map != nullptr)
    {
      CreatureGenerationManager cgm;
      CreaturePtr adv = cgm.generate_follower(game.get_action_manager_ref(), map, FollowerType::FOLLOWER_TYPE_ADVENTURER, lvl, race_id, class_id);

      GameUtils::add_new_creature_to_map(game, adv, map, { y,x });
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to generate_adventurer");
  }

  return 0;
}

int generate_vegetable_garden(lua_State* ls)
{
  bool generated = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 5 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4) && lua_isnumber(ls, 5))
  {
    string map_id = lua_tostring(ls, 1);
    int y_start = lua_tointeger(ls, 2);
    int y_end = lua_tointeger(ls, 3);
    int x_start = lua_tointeger(ls, 4);
    int x_end = lua_tointeger(ls, 5);
    bool fence = false;
    int row_spacing = 1;
    int col_spacing = 1;

    if (num_args >= 6 && lua_isboolean(ls, 6))
    {
      fence = lua_toboolean(ls, 6);
    }

    if (num_args >= 8 && lua_isnumber(ls, 7) && lua_isnumber(ls, 8))
    {
      row_spacing = lua_tointeger(ls, 7);
      col_spacing = lua_tointeger(ls, 8);
    }

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);
    FruitVegetableGardenGenerator fvgg(FruitVegetableGardenType::FVG_TYPE_VEGETABLE, "", AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, col_spacing, row_spacing, fence);

    if (map != nullptr)
    {
      fvgg.generate(map, { y_start, x_start }, { y_end, x_end });
      generated = true;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to generate_vegetable_garden");
  }

  lua_pushboolean(ls, generated);
  return 1;
}

int generate_enclosure(lua_State* ls)
{
  bool generated = false;

  if (lua_gettop(ls) == 5 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4) && lua_isnumber(ls, 5))
  {
    Coordinate st_coord = { lua_tointeger(ls, 1), lua_tointeger(ls, 2) };
    Coordinate end_coord = { lua_tointeger(ls, 3), lua_tointeger(ls, 4) };
    EnclosureContentsType etype = static_cast<EnclosureContentsType>(lua_tointeger(ls, 5));
    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      EnclosureSectorFeature esf(etype);
      generated = esf.generate(map, st_coord, end_coord);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to generate_enclosure");
  }

  lua_pushboolean(ls, generated);
  return 1;
}

int generate_hermitage(lua_State* ls)
{
  if (lua_gettop(ls) == 0)
  {
    MapPtr map = Game::instance().get_current_map();
    
    if (map != nullptr)
    {
      GeneratorUtils::generate_hermitage(map);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to generate_hermitage");
  }

  return 0;
}


int set_colour(lua_State* ls)
{
  if (lua_gettop(ls) == 4 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    int colour = lua_tointeger(ls, 1);
    int r = lua_tointeger(ls, 2);
    int g = lua_tointeger(ls, 3);
    int b = lua_tointeger(ls, 4);

    Game& game = Game::instance();
    DisplayPtr display = game.get_display();
    
    if (display != nullptr)
    {
      display->set_colour(colour, r, g, b);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_colour");
  }

  return 0;
}

int add_npc_level_message(lua_State* ls)
{
  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr && !creature->get_is_player())
    {
      Game& game = Game::instance();
      MapPtr current_map = game.get_current_map();
      string msg = TextMessages::get_npc_level_message(StringTable::get(creature->get_description_sid()));

      IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, GameUtils::is_creature_in_player_view_map(game, creature_id));
      manager.add_new_message(msg);
      manager.send();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to add_npc_level_message");
  }

  return 0;
}

int set_leader(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));
    string leader_id = lua_tostring(ls, 2);
    MapPtr current_map = Game::instance().get_current_map();

    CreatureUtils::set_leadership(creature, leader_id, current_map);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_leader");
  }
  
  return 0;
}

int get_leader_id(lua_State* ls)
{
  string leader_id;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      leader_id = creature->get_leader_id();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_leader_id");
  }

  lua_pushstring(ls, leader_id.c_str());
  return 1;
}

int remove_leader(lua_State* ls)
{
  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  { 
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      creature->remove_leader();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to remove_leader");
  }

  return 0;
}

int get_name(lua_State* ls)
{
  string name;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      name = creature->get_name();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_name");
  }

  lua_pushstring(ls, name.c_str());
  return 1;
}

int set_hirelings_hired(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    { 
      int hired = lua_tointeger(ls, 2);
      creature->set_hirelings_hired(hired);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_hirelings_hired");
  }

  return 0;
}

int get_hirelings_hired(lua_State* ls)
{
  int hired = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      hired = creature->get_hirelings_hired();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_hirelings_hired");
  }

  lua_pushnumber(ls, hired);
  return 1;
}

int set_adventurers_joined(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      int joined = lua_tointeger(ls, 2);
      creature->set_adventurers_joined(joined);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_adventurers_joined");
  }

  return 0;
}

int get_adventurers_joined(lua_State* ls)
{
  int joined = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      joined = creature->get_adventurers_joined();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_adventurers_joined");
  }

  lua_pushnumber(ls, joined);
  return 1;
}


int get_trained_magic_skills(lua_State* ls)
{
  vector<int> mskills;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      auto cr_skills = creature->get_skills().get_trained_magic_skills();

      for (auto cr_skill : cr_skills)
      {
        mskills.push_back(static_cast<int>(cr_skill));
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_trained_magic_skills");
  }

  LuaUtils::create_return_table_from_int_vector(ls, mskills);
  return 1;
}

int get_highest_melee_skill(lua_State* ls)
{
  SkillType highest_st = SkillType::SKILL_UNDEFINED;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      const Skills& skills = creature->get_skills();
      int highest = -1;

      for (int i = static_cast<int>(SkillType::SKILL_MELEE_BEGIN); i < static_cast<int>(SkillType::SKILL_MELEE_LAST); i++)
      {
        SkillType s = static_cast<SkillType>(i);
        int val = skills.get_value(s);

        if (val > highest)
        {
          highest = val;
          highest_st = s;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_highest_melee skill");
  }

  lua_pushinteger(ls, static_cast<int>(highest_st));
  return 1;
}

int order_follow(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string cr_id = lua_tostring(ls, 1);
    string cr_to_foll_id = lua_tostring(ls, 2);

    CreaturePtr creature = get_creature(cr_id);

    if (creature != nullptr)
    {
      OrderAction oa;

      if (cr_id != cr_to_foll_id)
      {
        oa.set_order(creature, DecisionStrategyProperties::DECISION_STRATEGY_FOLLOW_CREATURE_ID, cr_to_foll_id);
      }
      else
      {
        oa.remove_orders(creature);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to order_follow");
  }

  return 0;
}

int order_at_ease(lua_State* ls)
{
  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string cr_id = lua_tostring(ls, 1);

    CreaturePtr creature = get_creature(cr_id);

    if (creature != nullptr)
    {
      OrderAction oa;
      oa.set_order(creature, DecisionStrategyProperties::DECISION_STRATEGY_AT_EASE, std::to_string(true));
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to order_follow");
  }

  return 0;
}

int reset_creatures_and_creature_locations(lua_State* ls)
{
  int sz = 0;

  if (lua_gettop(ls) == 0)
  {
    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      map->reset_creatures_and_creature_locations();
      sz = map->get_creatures().size();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to reset_creatures_and_creature_locations");
  }

  lua_pushinteger(ls, sz);
  return 1;
}

int set_creature_speech_text_sid(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string cr_id = lua_tostring(ls, 1);
    string text_sid = lua_tostring(ls, 2);
    CreaturePtr creature = get_creature(cr_id);

    if (creature != nullptr)
    {
      creature->set_speech_text_sid(text_sid);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_creature_speech_text_sid");
  }

  return 0;
}

int get_creature_speech_text_sid(lua_State* ls)
{
  string speech_text_sid;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      speech_text_sid = creature->get_speech_text_sid();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_creature_speech_text_sid");
  }

  lua_pushstring(ls, speech_text_sid.c_str());
  return 1;
}

int set_creature_text_details_sid(lua_State* ls)
{
  bool set_val = false;

  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isstring(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    int y = lua_tointeger(ls, 2);
    int x = lua_tointeger(ls, 3);
    string new_sid = lua_tostring(ls, 4);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr && tile->has_creature())
      {
        CreaturePtr c = tile->get_creature();

        if (c != nullptr)
        {
          c->set_text_details_sid(new_sid);
          set_val = true;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_creature_text_details_sid");
  }

  lua_pushboolean(ls, set_val);
  return 1;
}

int creature_has_humanoid_followers(lua_State* ls)
{
  bool has_hfoll = false;

  if (lua_gettop(ls) == 1 && lua_tostring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      const CreatureMap& creatures = map->get_creatures_ref();

      for (const auto& c_pair : creatures)
      {
        CreaturePtr c = c_pair.second;

        if (c != nullptr && c->get_leader_id() == creature_id)
        {
          RaceManager rm;

          if (rm.is_race_or_descendent(c->get_race_id(), RaceConstants::RACE_CONSTANTS_RACE_ID_HUMANOID))
          {
            has_hfoll = true;
            break;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to creature_has_humanoid_followers");
  }

  lua_pushboolean(ls, has_hfoll);
  return 1;
}

int count_creature_humanoid_followers(lua_State* ls)
{
  int num_hf = 0;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      const CreatureMap& creatures = map->get_creatures_ref();

      for (const auto& c_pair : creatures)
      {
        CreaturePtr c = c_pair.second;

        if (c != nullptr && c->get_leader_id() == creature_id)
        {
          RaceManager rm;

          if (rm.is_race_or_descendent(c->get_race_id(), RaceConstants::RACE_CONSTANTS_RACE_ID_HUMANOID))
          {
            num_hf++;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to count_creature_humanoid_followers");
  }

  lua_pushinteger(ls, num_hf);
  return 1;
}

int set_chat_script(lua_State* ls)
{
  bool set = false;

  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isstring(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    int y = lua_tointeger(ls, 2);
    int x = lua_tointeger(ls, 3);
    string new_chat_script = lua_tostring(ls, 4);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr && tile->has_creature())
      {
        CreaturePtr c = tile->get_creature();

        if (c != nullptr)
        {
          ScriptDetails sd;
          sd.set_chance(100);
          sd.set_script(new_chat_script);

          c->get_event_scripts_ref()[CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT] = sd;
          set = true;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_chat_script");
  }

  return set;
}

int count_creatures_with_race(lua_State* ls)
{
  int cnt = 0;
  int num_args = lua_gettop(ls);

  if (num_args >= 1 && lua_isstring(ls, 1))
  {
    string race_id = lua_tostring(ls, 1);
    string map_id;

    if (num_args >= 2 && lua_isstring(ls, 2))
    {
      map_id = lua_tostring(ls, 2);
    }

    MapPtr map;
    
    if (map_id.empty())
    {
      map = Game::instance().get_current_map();
    }
    else
    {
      map = Game::instance().get_map_registry_ref().get_map(map_id);
    }

    if (map != nullptr)
    {
      const CreatureMap& creatures = map->get_creatures_ref();

      for (const auto& c_pair : creatures)
      {
        if (c_pair.second && c_pair.second->get_race_id() == race_id)
        {
          cnt++;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to count_creatures_with_race");
  }

  lua_pushinteger(ls, cnt);
  return 1;
}

int count_creatures_with_property(lua_State* ls)
{
  int cnt = 0;

  if (lua_gettop(ls) >= 1 && lua_isstring(ls, 1))
  {
    MapPtr map = Game::instance().get_current_map();
    string prop_name = lua_tostring(ls, 1);
    string prop_val;

    if (lua_gettop(ls) >= 2 && lua_isstring(ls, 2))
    {
      prop_val = lua_tostring(ls, 2);
    }

    if (lua_gettop(ls) >= 3 && lua_isstring(ls, 3))
    {
      map = Game::instance().get_map_registry_ref().get_map(lua_tostring(ls, 3));
    }

    if (map != nullptr)
    {
      const CreatureMap& creatures = map->get_creatures_ref();

      for (const auto& c_pair : creatures)
      {
        CreaturePtr creature = c_pair.second;

        if (creature != nullptr)
        {
          if ((prop_val.empty() && creature->has_additional_property(prop_name)) || 
              (!prop_val.empty() && creature->get_additional_property(prop_name) == prop_val))
          {
            cnt++;
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to count_creatures_with_property");
  }

  lua_pushinteger(ls, cnt);
  return 1;
}

int get_time_of_day(lua_State* ls)
{
  int tod = CTIME_OF_DAY_UNDEFINED;

  if (lua_gettop(ls) == 0)
  {
    TimeOfDayType todt = GameUtils::get_date(Game::instance()).get_time_of_day();
    tod = static_cast<int>(todt);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_time_of_day");
  }

  lua_pushinteger(ls, tod);
  return 1;
}

int update_creatures(lua_State* /*ls*/)
{
  MapPtr map = Game::instance().get_current_map();
  MapUtils::update_creatures(map);

  return 0;
}

int get_random_preset_village(lua_State* ls)
{
  int y = -1;
  int x = -1;
  string village_name;
  string map_location_sid;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string map_id = lua_tostring(ls, 1);
    Game& game = Game::instance();
    MapPtr world_map = game.get_current_world()->get_world(game.get_map_registry_ref());
    auto village = MapUtils::get_random_village_by_property(world_map, MapProperties::MAP_PROPERTIES_PRESET_VILLAGE_COORDINATES, { map_id });

    y = std::get<0>(village);
    x = std::get<1>(village);
    village_name = std::get<2>(village);
    map_location_sid = std::get<3>(village);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_random_preset_village");
  }

  lua_pushinteger(ls, y);
  lua_pushinteger(ls, x);
  lua_pushstring(ls, village_name.c_str());
  lua_pushstring(ls, map_location_sid.c_str());

  return 4;
}

int get_random_village(lua_State* ls)
{
  int y = -1;
  int x = -1;
  string village_name;
  string map_location_sid;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string map_id = lua_tostring(ls, 1);
    Game& game = Game::instance();
    MapPtr world_map = game.get_current_world()->get_world(game.get_map_registry_ref());
    auto village = MapUtils::get_random_village_by_property(world_map, MapProperties::MAP_PROPERTIES_VILLAGE_COORDINATES, { map_id });

    y = std::get<0>(village);
    x = std::get<1>(village);
    village_name = std::get<2>(village);
    map_location_sid = std::get<3>(village);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_random_village");
  }

  lua_pushinteger(ls, y);
  lua_pushinteger(ls, x);
  lua_pushstring(ls, village_name.c_str());
  lua_pushstring(ls, map_location_sid.c_str());

  return 4;
}

int tokenize(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string str = lua_tostring(ls, 1);
    string delim = lua_tostring(ls, 2);

    bool keep_tokens = false;

    if (num_args == 3 && lua_isboolean(ls, 3))
    {
      keep_tokens = lua_toboolean(ls, 3);
    }

    vector<string> tokens = String::tokenize(str, delim, keep_tokens);
    size_t t_sz = tokens.size();

    // Create an array with n-array elements and 0 non-array elements.
    lua_createtable(ls, static_cast<int>(t_sz), 0);

    for (uint i = 0; i < t_sz; i++)
    {
      string cur_tok = tokens.at(i);

      lua_pushstring(ls, cur_tok.c_str());
      lua_rawseti(ls, -2, i + 1);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to tokenize");
  }

  return 1;
}

int generate_name(lua_State* ls)
{
  string name = Naming::generate_name(CreatureSex::CREATURE_SEX_NOT_SPECIFIED);
  lua_pushstring(ls, name.c_str());

  return 1;
}

int remove_chat_script(lua_State* ls)
{
  bool removed = false;

  if (lua_gettop(ls) >= 1 && lua_isstring(ls, 1))
  {
    MapPtr map = Game::instance().get_current_map();

    if (lua_gettop(ls) >= 2 && lua_isstring(ls, 2))
    {
      map = Game::instance().get_map_registry_ref().get_map(lua_tostring(ls, 2));
    }

    if (map != nullptr)
    {
      CreaturePtr creature = map->get_creature(lua_tostring(ls, 1));

      if (creature != nullptr)
      {
        EventScriptsMap& scripts = creature->get_event_scripts_ref();
        auto s_it = scripts.find(CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT);

        if (s_it != scripts.end())
        {
          scripts.erase(scripts.find(CreatureEventScripts::CREATURE_EVENT_SCRIPT_CHAT));
          removed = true;
        }
      }
    }
  }

  lua_pushboolean(ls, removed);
  return 1;
}

int get_setting(lua_State* ls)
{
  string s_val;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string setting = lua_tostring(ls, 1);
    s_val = Game::instance().get_settings_ref().get_setting(setting);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_setting");
  }

  lua_pushstring(ls, s_val.c_str());
  return 1;
}

int set_current_age(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));
    int cur_age = lua_tointeger(ls, 2);

    if (creature != nullptr)
    {
      Statistic age = creature->get_age();
      age.set_current(cur_age);

      creature->set_age(age);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_current_age");
  }

  return 0;
}

int set_max_age(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));
    int max_age = lua_tointeger(ls, 2);

    if (creature != nullptr)
    {
      Statistic age = creature->get_age();
      age.set_base(max_age);

      creature->set_age(age);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_max_age");
  }

  return 0;
}

int set_hungerless(lua_State* ls)
{
  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      creature->get_hunger_clock_ref().set_requires_food(false);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_hungerless");
  }

  return 0;
}

int generate_npc_background(lua_State* ls)
{
  string background;

  if (lua_gettop(ls) >= 0)
  {
    bool include_all = true;

    if (lua_gettop(ls) == 1 && lua_isboolean(ls, 1))
    {
      include_all = lua_toboolean(ls, 1);
    }

    CreatureGenerationManager cgm;
    MapPtr current_map = Game::instance().get_current_map();

    CreaturePtr creature = cgm.generate_follower(Game::instance().get_action_manager_ref(), current_map, FollowerType::FOLLOWER_TYPE_ADVENTURER, 1);

    NPCBackgroundGenerator nbg(include_all);
    background = nbg.generate_bestiary(creature);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to generate_npc_background");
  }

  lua_pushstring(ls, background.c_str());
  return 1;
}

int show_bestiary_text(lua_State* ls)
{
  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string bestiary_text = lua_tostring(ls, 1);
    CreaturePtr placeholder = std::make_shared<Creature>();
    placeholder->set_text_details_sid(bestiary_text);

    BestiaryAction ba;
    ba.display_bestiary_information(placeholder);
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to show_bestiary_text");
  }

  return 0;
}

int get_stack_size_current_state(lua_State* /*ls*/)
{
  lua_State* L = Game::instance().get_script_engine_ref().get_current_state();
  int stack_size = lua_gettop(L);
  lua_pushinteger(L, stack_size);
  return 1;
}

// BAD FN DO NOT CALL
// BAD FN DO NOT CALL
// BAD FN DO NOT CALL
int bad_fn_do_not_call(lua_State* ls)
{
  lua_pushinteger(ls, 1);
  lua_pushinteger(ls, 7);
  lua_pushinteger(ls, 5);
  lua_pushinteger(ls, 3);

  return 0;
}
// BAD FN DO NOT CALL
// BAD FN DO NOT CALL
// BAD FN DO NOT CALL

// good fn maybe call
int erase_map_linkage(lua_State* ls)
{
  bool erased = false;

  if (lua_gettop(ls) == 1 && lua_isnumber(ls, 1))
  {
    MapPtr current_map = Game::instance().get_current_map();
    Direction d = static_cast<Direction>(lua_tointeger(ls, 1));

    if (current_map != nullptr)
    {
      TileExitMap tem = current_map->get_map_exits();
      tem.erase(d);

      current_map->set_map_exits(tem);
      erased = true;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to erase_map_linkage");
  }

  lua_pushboolean(ls, erased);
  return 1;
}

int has_trainable_skill(lua_State* ls)
{
  bool has_skill = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      has_skill = creature->get_skills().has_trainable_skill();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Incorrect arguments to has_trainable_skill");
  }

  lua_pushboolean(ls, has_skill);
  return 1;
}

int train_skills(lua_State* ls)
{
  bool trained = false;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    int num_trains = lua_tointeger(ls, 2);
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      creature->set_skill_points(creature->get_skill_points() + num_trains);
      Game::instance().get_action_manager_ref().show_skills(creature, SkillsSelectionType::SKILLS_SELECTION_IMPROVE_SKILL);
      trained = true;
    }
  }

  lua_pushboolean(ls, trained);
  return 1;
}

int set_feature_uses(lua_State* ls)
{
  bool set_val = false;

  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isnumber(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    int y = lua_tointeger(ls, 2);
    int x = lua_tointeger(ls, 3);
    int uses = lua_tointeger(ls, 4);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr)
      {
        FeaturePtr feature = tile->get_feature();

        if (feature != nullptr)
        {
          feature->set_uses(uses);
          set_val = true;
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_feature_uses");
  }

  lua_pushboolean(ls, set_val);
  return 1;
}

int set_creature_size(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    CreatureSize cs = static_cast<CreatureSize>(lua_tointeger(ls, 2));
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->set_size(cs);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_creature_size");
  }

  return 0;
}

int get_creature_size(lua_State* ls)
{
  CreatureSize cs = CreatureSize::CREATURE_SIZE_NA;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      cs = creature->get_size();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_creature_size");
  }

  lua_pushinteger(ls, static_cast<int>(cs));
  return 1;
}

int get_nutrition(lua_State* ls)
{
  int nutrition = 0;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    CreaturePtr creature = get_creature(lua_tostring(ls, 1));

    if (creature != nullptr)
    {
      ItemPtr item = creature->get_inventory()->get_from_id(lua_tostring(ls, 2));

      if (item != nullptr)
      {
        ConsumablePtr cons = dynamic_pointer_cast<Consumable>(item);

        if (cons != nullptr)
        {
          nutrition = cons->get_nutrition();
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_nutrition");
  }

  lua_pushinteger(ls, nutrition);
  return 1;
}

int get_hidden_treasure_message(lua_State* ls)
{
  string msg;

  if (lua_gettop(ls) == 1 && lua_isboolean(ls, 1))
  {
    msg = TextMessages::get_hidden_treasure_message(lua_toboolean(ls, 1));
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_hidden_treasure_message");
  }

  lua_pushstring(ls, msg.c_str());
  return 1;
}

int get_map_type(lua_State* ls)
{
  MapType mt = MapType::MAP_TYPE_WORLD;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    MapPtr map = Game::instance().get_map_registry_ref().get_map(lua_tostring(ls, 1));

    if (map != nullptr)
    {
      mt = map->get_map_type();
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_map_type");
  }

  lua_pushinteger(ls, static_cast<int>(mt));
  return 1;
}

int is_tile_available_for_creature(lua_State* ls)
{
  bool avail = false;

  if (lua_gettop(ls) == 3 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3))
  {
    string map_id = lua_tostring(ls, 1);
    int y = lua_tointeger(ls, 2);
    int x = lua_tointeger(ls, 3);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr && MapUtils::is_tile_available_for_creature(nullptr, tile))
      {
        avail = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to is_tile_available_for_creature");
  }

  lua_pushboolean(ls, avail);
  return 1;
}

int set_creature_godless(lua_State* ls)
{
  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      Religion r;
      r.set_active_deity_id(ReligionConstants::DEITY_ID_GODLESS);

      creature->set_religion(r);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_creature_godless");
  }

  return 0;
}

int play_sound_effect(lua_State* ls)
{
  bool played = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string sound_id = lua_tostring(ls, 1);
    SoundPtr sound = Game::instance().get_sound();

    if (sound != nullptr)
    {
      sound->play(sound_id);
      played = true;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to play_sound_effect");
  }

  lua_pushboolean(ls, played);
  return 1;
}

int is_sound_enabled(lua_State* ls)
{
  bool enabled = false;

  if (lua_gettop(ls) == 0)
  {
    SoundPtr sound = Game::instance().get_sound();

    if (sound != nullptr)
    {
      enabled = sound->get_enable_sound();
    }
  }

  lua_pushboolean(ls, enabled);
  return 1;
}

int is_music_enabled(lua_State* ls)
{
  bool enabled = false;

  if (lua_gettop(ls) == 0)
  {
    SoundPtr sound = Game::instance().get_sound();

    if (sound != nullptr)
    {
      enabled = sound->get_enable_music();
    }
  }

  lua_pushboolean(ls, enabled);
  return 1;
}

int play_event_music(lua_State* ls)
{
  bool played = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string event_id = lua_tostring(ls, 1);
    SoundPtr sound = Game::instance().get_sound();

    if (sound != nullptr && !event_id.empty())
    {
      sound->play_music_for_event(event_id);
      played = true;
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to play_event_music");
  }

  lua_pushboolean(ls, played);
  return 1;
}

int play_map_music(lua_State* ls)
{
  bool played = false;
  int num_args = lua_gettop(ls);

  if (num_args == 0 || (num_args == 1 && lua_isstring(ls, 1)))
  {
    MapPtr map;

    if (num_args == 0)
    {
      map = Game::instance().get_current_map();
    }
    else
    {
      map = Game::instance().get_map_registry_ref().get_map(lua_tostring(ls, 1));
    }

    if (map != nullptr)
    {
      SoundPtr sound = Game::instance().get_sound();

      if (sound != nullptr)
      {
        sound->play_music(map);
        played = true;
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to play_map_music");
  }

  lua_pushboolean(ls, played);
  return 1;
}

int set_map_music(lua_State* ls)
{
  bool added = false;
  int num_args = lua_gettop(ls);

  if (num_args >= 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string map_id = lua_tostring(ls, 1);
    string music_location = lua_tostring(ls, 2);
    SoundPtr sound = Game::instance().get_sound();

    bool play_music = false;

    if (num_args == 3 && lua_isboolean(ls, 3))
    {
      play_music = lua_toboolean(ls, 3);
    }

    if (sound != nullptr && !map_id.empty())
    {
      MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

      if (map != nullptr)
      {
        map->set_property(MapProperties::MAP_PROPERTIES_SONG_LOCATION, music_location);
        added = true;

        if (play_music)
        {
          sound->play_music(map);
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_map_music");
  }

  lua_pushboolean(ls, added);
  return 1;
}

int play_music_event(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 1 && lua_isstring(ls, 1))
  {
    string event_id = lua_tostring(ls, 1);
    bool loop = true;

    if (num_args == 2 && lua_isboolean(ls, 2))
    {
      loop = lua_toboolean(ls, 2);
    }

    SoundPtr sound = Game::instance().get_sound();

    if (sound != nullptr)
    {
      sound->play_music_for_event(event_id, loop);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to play_music_event");
  }

  return 0;
}

int play_music_location(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args >= 1 && lua_isstring(ls, 1))
  {
    string location = lua_tostring(ls, 1);
    SoundPtr sound = Game::instance().get_sound();
    bool loop = true;

    if (num_args == 2 && lua_isboolean(ls, 2))
    {
      loop = lua_toboolean(ls, 2);
    }

    if (sound != nullptr)
    {
      sound->play_music_location(location, loop);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to play_music_location");
  }

  return 0;
}

int get_music_location_for_event(lua_State* ls)
{
  string location;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string event = lua_tostring(ls, 1);
    Game& game = Game::instance();
    SoundPtr sound = game.get_sound();
    CreaturePtr player = game.get_current_player();
    ternary winner = game.get_winner();

    if (sound != nullptr)
    {
      Music music = sound->get_music();
      location = music.get_event_song(event, winner);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_music_location_for_event");
  }

  lua_pushstring(ls, location.c_str());
  return 1;
}

int get_music_location_for_map_type(lua_State* ls)
{
  string location;

  if (lua_gettop(ls) == 1 && lua_isnumber(ls, 1))
  {
    MapType mt = static_cast<MapType>(lua_tointeger(ls, 1));
    Game& game = Game::instance();
    SoundPtr sound = game.get_sound();
    ternary winner = ternary::TERNARY_UNDEFINED;

    if (sound != nullptr)
    {
      Music music = sound->get_music();
      location = music.get_song(mt, winner);
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to get_music_location_for_map_type");
  }

  lua_pushstring(ls, location.c_str());
  return 1;
}

int does_item_exist_on_map(lua_State* ls)
{
  bool exists = false;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string item_id = lua_tostring(ls, 1);
    MapPtr map = Game::instance().get_current_map();

    if (map != nullptr)
    {
      const TilesContainer& tiles = map->get_tiles_ref();

      for (const auto& t_pair : tiles)
      {
        TilePtr tile = t_pair.second;

        if (tile != nullptr)
        {
          IInventoryPtr inv = tile->get_items();

          if (inv != nullptr)
          {
            if (inv->has_item(item_id))
            {
              exists = true;
              break;
            }
          }
        }
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to does_item_exist_on_map");
  }

  lua_pushboolean(ls, exists);
  return 1;
}

int set_tile_unprotected_movement_is_death(lua_State* ls)
{
  if (lua_gettop(ls) == 4 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isboolean(ls, 4))
  {
    string map_id = lua_tostring(ls, 1);
    int y = lua_tointeger(ls, 2);
    int x = lua_tointeger(ls, 3);
    bool val = lua_toboolean(ls, 4);

    MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

    if (map != nullptr)
    {
      TilePtr tile = map->at(y, x);

      if (tile != nullptr)
      {
        tile->set_unprotected_movement_is_death(val);
      }
    }
  }
  else
  {
    LuaUtils::log_and_raise(ls, "Invalid arguments to set_tile_unprotected_movement_is_death");
  }

  return 0;
}