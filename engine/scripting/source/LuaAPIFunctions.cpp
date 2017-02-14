#include "LuaAPIFunctions.hpp"
#include "BuySellCalculator.hpp"
#include "ClassManager.hpp"
#include "CombatManager.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureFactory.hpp"
#include "CreatureProperties.hpp"
#include "CreatureUtils.hpp"
#include "EffectFactory.hpp"
#include "ExperienceManager.hpp"
#include "FeatureFactory.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "GeneratorUtils.hpp"
#include "HostilityManager.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "Log.hpp"
#include "LuaItemFilter.hpp"
#include "LuaUtils.hpp"
#include "ItemManager.hpp"
#include "MapExitUtils.hpp"
#include "MapItemGenerator.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "Naming.hpp"
#include "PickupAction.hpp"
#include "RaceManager.hpp"
#include "Quests.hpp"
#include "ReligionManager.hpp"
#include "RNG.hpp"
#include "SkillManager.hpp"
#include "Spellbook.hpp"
#include "SpellcastingAction.hpp"
#include "StatisticsMarker.hpp"
#include "StatisticTextKeys.hpp"
#include "StatusEffectFactory.hpp"
#include "StringTable.hpp"
#include "TextMessages.hpp"
#include "TileGenerator.hpp"
#include "Tool.hpp"

using namespace std;

CreaturePtr local_creature;

void add_seconds_to_calendar(const int seconds, int& add_successful);
bool set_all_eq_to(CreaturePtr creature, const ItemStatus status);

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
    CreatureMap& cmap = Game::instance().get_current_map()->get_creatures_ref();
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
  lua_register(L, "add_object_to_player_tile", add_object_to_player_tile);
  lua_register(L, "add_object_to_tile", add_object_to_tile);
  lua_register(L, "add_key_to_player_tile", add_key_to_player_tile);
  lua_register(L, "add_feature_to_player_tile", add_feature_to_player_tile);
  lua_register(L, "mark_quest_completed", mark_quest_completed);
  lua_register(L, "remove_active_quest", remove_active_quest);
  lua_register(L, "is_quest_completed", is_quest_completed);
  lua_register(L, "player_has_item", player_has_item);
  lua_register(L, "remove_object_from_player", remove_object_from_player);
  lua_register(L, "is_item_generated", is_item_generated);
  lua_register(L, "get_num_item_generated", get_num_item_generated);
  lua_register(L, "set_skill_value", set_skill_value);
  lua_register(L, "get_skill_value", get_skill_value);
  lua_register(L, "check_skill", check_skill);
  lua_register(L, "RNG_range", RNG_range);
  lua_register(L, "RNG_percent_chance", RNG_percent_chance);
  lua_register(L, "add_spell_castings", add_spell_castings);
  lua_register(L, "gain_experience", gain_experience);
  lua_register(L, "get_experience_value", get_experience_value);
  lua_register(L, "add_creature_to_map", add_creature_to_map);
  lua_register(L, "remove_creature_from_map", remove_creature_from_map);
  lua_register(L, "add_status_to_creature", add_status_to_creature);
  lua_register(L, "add_status_to_creature_at", add_status_to_creature_at);
  lua_register(L, "get_creature_statuses", get_creature_statuses);
  lua_register(L, "stop_playing_game", stop_playing_game);
  lua_register(L, "set_creature_base_damage", set_creature_base_damage);
  lua_register(L, "set_creature_speed", set_creature_speed);
  lua_register(L, "get_creature_speed", get_creature_speed);
  lua_register(L, "get_creature_yx", get_creature_yx);
  lua_register(L, "get_creature_id", get_creature_id);
  lua_register(L, "get_current_map_id", get_current_map_id);
  lua_register(L, "gain_level", gain_level);
  lua_register(L, "goto_level", goto_level);
  lua_register(L, "is_player", is_player);
  lua_register(L, "incr_str", incr_str);
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
  lua_register(L, "map_set_additional_property", map_set_additional_property);
  lua_register(L, "map_set_tile_subtype", map_set_tile_subtype);
  lua_register(L, "map_add_location", map_add_location);
  lua_register(L, "map_transform_tile", map_transform_tile);
  lua_register(L, "map_add_tile_exit", map_add_tile_exit);
  lua_register(L, "map_set_explored", map_set_explored);
  lua_register(L, "map_get_name_sid", map_get_name_sid);
  lua_register(L, "log", log);
  lua_register(L, "get_player_title", get_player_title);
  lua_register(L, "set_creature_current_hp", set_creature_current_hp);
  lua_register(L, "set_creature_current_ap", set_creature_current_ap);
  lua_register(L, "set_creature_name", set_creature_name);
  lua_register(L, "get_creature_name", get_creature_name);
  lua_register(L, "destroy_creature_equipment", destroy_creature_equipment);
  lua_register(L, "destroy_creature_inventory", destroy_creature_inventory);
  lua_register(L, "get_deity_summons", get_deity_summons);
  lua_register(L, "summon_monsters_around_creature", summon_monsters_around_creature);
  lua_register(L, "creature_is_class", creature_is_class);
  lua_register(L, "get_item_count", get_item_count);
  lua_register(L, "count_currency", count_currency);
  lua_register(L, "get_unidentified_item_count", get_unidentified_item_count);
  lua_register(L, "is_item_identified", is_item_identified);
  lua_register(L, "get_item_value", get_item_value);
  lua_register(L, "select_item", select_item);
  lua_register(L, "set_hostility", set_hostility);
  lua_register(L, "teleport", teleport);
  lua_register(L, "get_creature_description", get_creature_description);
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
  lua_register(L, "cast_spell", cast_spell);
  lua_register(L, "bless_equipment", bless_equipment);
  lua_register(L, "curse_equipment", curse_equipment);
  lua_register(L, "curse_inventory", curse_inventory);
  lua_register(L, "set_winner", set_winner);
  lua_register(L, "get_creature_colour", get_creature_colour);
  lua_register(L, "set_creature_colour", set_creature_colour);
  lua_register(L, "set_creature_evade", set_creature_evade);
  lua_register(L, "set_trap", set_trap);
  lua_register(L, "get_nearby_hostile_creatures", get_nearby_hostile_creatures);
  lua_register(L, "set_creature_additional_property", set_creature_additional_property);
  lua_register(L, "get_creature_additional_property", get_creature_additional_property);
  lua_register(L, "get_creature_additional_property_csv", get_creature_additional_property_csv);
  lua_register(L, "is_creature_in_view_map", is_creature_in_view_map);
  lua_register(L, "redraw", redraw);
  lua_register(L, "get_race_ids", get_race_ids);
  lua_register(L, "get_unarmed_slays", get_unarmed_slays);
  lua_register(L, "add_unarmed_slay", add_unarmed_slay);
  lua_register(L, "get_race_name", get_race_name);
  lua_register(L, "set_inscription", set_inscription);
  lua_register(L, "get_map_dimensions", get_map_dimensions);
  lua_register(L, "get_coords_with_tile_type_in_range", get_coords_with_tile_type_in_range);
  lua_register(L, "get_custom_map_id", get_custom_map_id);
  lua_register(L, "ranged_attack", ranged_attack);
  lua_register(L, "get_spellbooks", get_spellbooks);
  lua_register(L, "set_shop_shopkeeper_id", set_shop_shopkeeper_id);
  lua_register(L, "repop_shop", repop_shop);
  lua_register(L, "get_unpaid_amount", get_unpaid_amount);
  lua_register(L, "set_items_paid", set_items_paid);
  lua_register(L, "bargain_discount", bargain_discount);
  lua_register(L, "bargain_premium", bargain_premium);
  lua_register(L, "get_item_type", get_item_type);
  lua_register(L, "get_shop_id", get_shop_id);
  lua_register(L, "get_stocked_item_types", get_stocked_item_types);
  lua_register(L, "get_sale_price", get_sale_price);
  lua_register(L, "set_item_unpaid", set_item_unpaid);
  lua_register(L, "is_in_shop", is_in_shop);
  lua_register(L, "is_item_unpaid", is_item_unpaid);
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
      message[0] = toupper(message[0]);
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

    IMessageManager& manager = MM::instance();

    if (clear_buffer)
    {
      manager.clear_if_necessary();
    }

    manager.add_new_message_with_pause(message);
    manager.send();

    // Because this function can only be called in a quest context,
    // where the speaking player is always assumed to be the player,
    // directly getting the player and getting its decision is safe
    // for now.
    Game& game = Game::instance();
    game.get_current_player()->get_decision_strategy()->get_confirmation();
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_message_with_pause");
    lua_error(ls);
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

    IMessageManager& manager = MM::instance();
    manager.clear_if_necessary();
    manager.add_new_message(message);
    manager.send();
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to clear_and_add_message");
    lua_error(ls);
  }

  return 0;
}

// Add a new message.
// Arguments expected: 1-2.
// Argument types: string (resource SID, required), table of strings (opt.)
// Assumption: table of strings is an array.
int add_message(lua_State* ls)
{
  int num_args = lua_gettop(ls);
  if (num_args > 0 && lua_isstring(ls, 1))
  {
    string message = read_sid_and_replace_values(ls);

    IMessageManager& manager = MM::instance();
    manager.add_new_message(message);
    manager.send();
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_message");
    lua_error(ls);
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

    IMessageManager& manager = MM::instance();
    manager.add_new_message(message);
    manager.send();
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_message_direct");
    lua_error(ls);
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

    IMessageManager& manager = MM::instance();
    manager.clear_if_necessary();
    manager.add_new_message(debug);
    manager.send();
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_debug_message");
    lua_error(ls);
  }

  return 0;
}

// Add a message with a confirmation prompt at the end.
// Arguments: message SID.
// Return value: boolean
int add_confirmation_message(lua_State* ls)
{
  bool confirm = false;

  if ((lua_gettop(ls) > 0) && (lua_isstring(ls, 1)))
  {
    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();
    string message = read_sid_and_replace_values(ls);

    IMessageManager& manager = MM::instance();
    manager.add_new_confirmation_message(TextMessages::get_confirmation_message(message));
    confirm = player->get_decision_strategy()->get_confirmation();

    manager.send();
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_confirmation_message");
    lua_error(ls);
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

    IMessageManager& manager = MM::instance();
    manager.clear_if_necessary();
    prompt_val = manager.add_new_message_with_prompt(message);

    manager.send();
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_prompt_message");
    lua_error(ls);
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
    CreaturePtr player = game.get_current_player();
    string message = read_sid_and_replace_values(ls);

    IMessageManager& manager = MM::instance();
    manager.clear_if_necessary();
    manager.add_new_message(message);
    manager.send();

    key_val = static_cast<char>(player->get_decision_strategy()->get_controller()->get_char_as_int());
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_char_message");
    lua_error(ls);
  }

  lua_pushstring(ls, key_val.c_str());
  return 1;
}

int add_fov_message(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args == 3 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isstring(ls, 3))
  {
    string creature_id = lua_tostring(ls, 1);
    string aff_creature_id = lua_tostring(ls, 2);
    string message_sid = lua_tostring(ls, 3);
    CreaturePtr creature = get_creature(creature_id);

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, aff_creature_id == CreatureID::CREATURE_ID_PLAYER);
    manager.add_new_message(StringTable::get(message_sid));
    manager.send();
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_fov_message");
    lua_error(ls);
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
      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature->get_is_player());
      manager.add_new_message(message);
      manager.send();
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_message_for_creature");
    lua_error(ls);
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
    string questmaster_name_sid = se.get_table_str(ls, "questmaster_name_sid");
    string map_name_sid = se.get_table_str(ls, "map_name_sid");
    string quest_description_sid = se.get_table_str(ls, "quest_description_sid");

    Quest new_quest(quest_id, quest_title_sid, questmaster_name_sid, map_name_sid, quest_description_sid);

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
    lua_pushstring(ls, "Incorrect arguments to add_new_quest");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to is_on_quest");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_num_creature_killed_global");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_num_uniques_killed_global");
    lua_error(ls);
  }

  lua_pushinteger(ls, num_killed);
  return 1;
}

// Add an object to the player's tile.
// Arguments:
// - 1: base item ID
// - 2: quantity (optional, 1 is assumed)
//
// Return value: true if added, false otherwise.
int add_object_to_player_tile(lua_State* ls)
{
  bool added = false;
  int num_args = lua_gettop(ls);

  if (lua_isstring(ls, 1) && (num_args == 1 || (num_args == 2 && lua_isnumber(ls, 2))))
  {
    string base_item_id;
    uint quantity = 1;

    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    if (map && map->get_map_type() != MapType::MAP_TYPE_WORLD)
    {
      CreaturePtr player = game.get_current_player();
      TilePtr player_tile = MapUtils::get_tile_for_creature(map, player);

      base_item_id = lua_tostring(ls, 1);

      // Set the quantity if it was specified.    
      if (num_args == 2)
      {
        quantity = static_cast<uint>(lua_tointeger(ls, 2));
      }

      added = ItemManager::create_item_with_probability(100, 100, player_tile->get_items(), base_item_id, quantity);
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_object_to_player_tile");
    lua_error(ls);
  }

  lua_pushboolean(ls, added);
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
    lua_pushstring(ls, "Incorrect arguments to add_object_to_tile");
    lua_error(ls);
  }

  lua_pushboolean(ls, result);
  return 1;
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
    lua_pushstring(ls, "Incorrect arguments to add_key_to_player_tile");
    lua_error(ls);
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
      FeaturePtr feature = FeatureFactory::create_feature(class_id);

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
    lua_pushstring(ls, "Incorrect arguments to add_feature_to_player_tile!");
    lua_error(ls);
  }
  
  lua_pushboolean(ls, added);
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
    lua_pushstring(ls, "Incorrect arguments to mark_quest_completed");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to remove_active_quest");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to is_quest_completed");
    lua_error(ls);
  }

  lua_pushboolean(ls, quest_completed);
  return 1;
}

// Check to see if the player has an item.
// Argument is the object's base ID.
int player_has_item(lua_State* ls)
{
  bool has_item = false;

  if ((lua_gettop(ls) == 1) && (lua_isstring(ls, -1)))
  {
    string base_item_id = lua_tostring(ls, 1);
    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();

    has_item = ItemManager::has_item(player, base_item_id);
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to player_has_item");
    lua_error(ls);
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

  if ((num_args >= 1) && (lua_isstring(ls, 1)))
  {
    string object_base_id = lua_tostring(ls, 1);

    if ((num_args == 2) && (lua_isnumber(ls, 2)))
    {
      quantity = lua_tointeger(ls, 2);
    }

    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();

    ItemManager im;
    im.remove_item_from_eq_or_inv(player, object_base_id, quantity);
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to remove_object_from_player");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_num_item_generated");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to set_skill_value");
    lua_error(ls);
  }


  return 0;
}

// Get a skill value for a particular creature.
// Three arguments are expected:
// - creature_id of a creature on the current map
// - skill enumeration value
// Return value is hte current value (int) for that skill.
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
    lua_pushstring(ls, "Incorrect arguments to get_skill_value");
    lua_error(ls);
  }

  lua_pushnumber(ls, skill_value);
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
    lua_pushstring(ls, "Incorrect arguments to check_skill");
    lua_error(ls);
  }

  lua_pushboolean(ls, check_value);
  return 1;
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
    lua_pushstring(ls, "Incorrect arguments to RNG_range");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to RNG_range");
    lua_error(ls);
  }

  lua_pushboolean(ls, rng_val);
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
      SpellKnowledge& sk = creature->get_spell_knowledge_ref();

      IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell_id);
      uint new_castings = isk.get_castings() + addl_castings;
      isk.set_castings(new_castings);
      sk.set_spell_knowledge(spell_id, isk);
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_spell_castings");
    lua_error(ls);
  }

  return 0;
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
    lua_pushstring(ls, "Incorrect arguments to gain_experience");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_experience_value");
    lua_error(ls);
  }

  lua_pushinteger(ls, xp_val);
  return 1;
}

// Add a creature to the map at a particular (y, x) coordinate
int add_creature_to_map(lua_State* ls)
{
  if ((lua_gettop(ls) == 3) && (lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3)))
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    string creature_id = lua_tostring(ls, 1);

    CreatureFactory cf;
    CreaturePtr creature = cf.create_by_creature_id(game.get_action_manager_ref(), creature_id);
    Coordinate coords(lua_tointeger(ls, 2), lua_tointeger(ls, 3));

    if (creature && MapUtils::are_coordinates_within_dimensions(coords, map->size()))
    {
      GameUtils::add_new_creature_to_map(game, creature, map, coords);
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_creature_to_map");
    lua_error(ls);
  }

  return 0;
}

// Returns a boolean - true if a creature was removed, false otherwise.
int remove_creature_from_map(lua_State* ls)
{
  bool creature_removed = false;

  if ((lua_gettop(ls) == 1) && (lua_isstring(ls, 1)))
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

    string creature_id_or_base = lua_tostring(ls, 1);
    const CreatureMap& creatures = map->get_creatures();

    for (const auto creature_pair : creatures)
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
  else
  {
    lua_pushstring(ls, "Incorrect arguments to remove_creature_from_map");
    lua_error(ls);
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
      StatusEffectPtr se = StatusEffectFactory::create_status_effect(status_id);
      se->apply_change(creature, danger_level);

      lua_pushboolean(ls, true);
      return 1;
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_status_to_creature");
    lua_error(ls);
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

        StatusEffectPtr se = StatusEffectFactory::create_status_effect(status_id);
        se->apply_change(creature, danger_level);

        added_status = true;
      }
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_status_to_creature_at");
    lua_error(ls);
  }

  lua_pushboolean(ls, added_status);
  return 1;
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
        if (csm_pair.second.first == true)
        {
          statuses.push_back(csm_pair.first);
        }
      }
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to get_statuses");
    lua_error(ls);
  }

  for (const string& status : statuses)
  {
    lua_pushstring(ls, status.c_str());
  }

  return static_cast<int>(statuses.size());
}

// Set a creature's base (bare-handed) damage.
int set_creature_base_damage(lua_State* ls)
{
  if ((lua_gettop(ls) == 3) && (lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3)))
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

      creature->set_base_damage(damage);
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to set_creature_base_damage");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to set_creature_speed");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_creature_speed");
    lua_error(ls);
  }

  lua_pushnumber(ls, speed);
  return 1;
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
    lua_pushstring(ls, "Incorrect arguments to get_creature_yx");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_creature_id");
    lua_error(ls);
  }

  lua_pushstring(ls, creature_id.c_str());
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
    lua_pushstring(ls, "Incorrect arguments to get_current_map_id");
    lua_error(ls);
  }

  lua_pushstring(ls, map_id.c_str());
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
    lua_pushstring(ls, "Incorrect arguments to gain_level");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to goto_level");
    lua_error(ls);
  }

  return 0;
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
    lua_pushstring(ls, "Incorrect arguments supplied to is_player");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to incr_str");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to incr_dex");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to incr_agi");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to incr_hea");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to incr_int");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to incr_wil");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to incr_cha");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to mark_stat");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to mark_str");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to mark_dex");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to mark_agi");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to mark_hea");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to mark_int");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to mark_wil");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to mark_cha");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to is_stat_max_marked");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to map_set_custom_map_id");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to map_set_edesc");
    lua_error(ls);
  }

  return 0;
}

// Set an additional property (k,v pair) into the given map id at the given
// row and column.
int map_set_additional_property(lua_State* ls)
{
  if (lua_gettop(ls) == 5 && lua_isstring(ls, 1) && lua_isnumber(ls, 2) && lua_isnumber(ls, 3) && lua_isstring(ls, 4) && lua_isstring(ls, 5))
  {
    string map_id = lua_tostring(ls, 1);
    Coordinate c(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    string k = lua_tostring(ls, 4);
    string v = lua_tostring(ls, 5);
    TilePtr tile = get_tile(map_id, c);

    if (tile)
    {
      tile->set_additional_property(k, v);
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to map_set_additional_property");
    lua_error(ls);
  }

  return 0;
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
    lua_pushstring(ls, "Incorrect arguments to map_set_tile_subtype");
    lua_error(ls);
  }

  return 0;
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
    lua_pushstring(ls, "Incorrect arguments to map_add_location");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to map_transform_tile");
    lua_error(ls);
  }

  lua_pushboolean(ls, result);
  return 1;
}

// Returns true if the given exit was added to the given tile, false otherwise.
int map_add_tile_exit(lua_State* ls)
{
  int result = false;

  if (lua_gettop(ls) == 5
    && lua_isstring(ls, 1)
    && lua_isnumber(ls, 2)
    && lua_isnumber(ls, 3)
    && lua_isnumber(ls, 4)
    && lua_isstring(ls, 5))
  {
    string map_id = lua_tostring(ls, 1);
    Coordinate c(lua_tointeger(ls, 2), lua_tointeger(ls, 3));
    int lua_direction = lua_tointeger(ls, 4);
    string exit_map_id = lua_tostring(ls, 5);

    if (lua_direction >= CDIRECTION_SOUTH_WEST && lua_direction <= CDIRECTION_DOWN)
    {
      MapPtr map = Game::instance().get_map_registry_ref().get_map(map_id);

      if (map != nullptr)
      {
        MapExitUtils::add_exit_to_tile(map, c, static_cast<Direction>(lua_direction), exit_map_id);
      }
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to map_transform_tile");
    lua_error(ls);
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
      TilesContainer tiles = cur_map->get_tiles();

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
    lua_pushstring(ls, "Incorrect arguments to map_set_explored");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to map_get_name_sid");
    lua_error(ls);
  }

  lua_pushstring(ls, map_name_sid.c_str());
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
    lua_pushstring(ls, "Incorrect arguments to log");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to set_creature_current_hp");
    lua_error(ls);
  }

  return 0;
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
    lua_pushstring(ls, "Incorrect arguments to set_creature_current_ap");
    lua_error(ls);
  }

  return 0;
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
    lua_pushstring(ls, "Incorrect arguments to set_creature_name");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to destroy_creature_equipment");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to destroy_creature_inventory");
    lua_error(ls);
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
    DeityPtr deity = rm.get_deity(deity_id);

    if (deity)
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
    lua_pushstring(ls, "Incorrect arguments to get_deity_summons");
    lua_error(ls);
  }

  return num_return_vals;
}

int summon_monsters_around_creature(lua_State* ls)
{
  if (lua_gettop(ls) == 4 && lua_istable(ls, 1) && lua_isstring(ls, 2) && lua_isnumber(ls, 3))
  {
    vector<string> monsters = LuaUtils::get_string_array_from_table(ls, 1);
    string creature_id = lua_tostring(ls, 2);
    int num_to_summon = lua_tointeger(ls, 3);
    bool override_hostility = lua_toboolean(ls, 4) != 0;

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
          CreaturePtr creature = cf.create_by_creature_id(game.get_action_manager_ref(), summon_id);

          if (override_hostility)
          {
            HostilityManager hm;
            hm.set_hostility_to_player(creature);
          }

          GameUtils::add_new_creature_to_map(game, creature, current_map, c);

          cnt++;
        }
      }
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to summon_monsters_around_creature");
    lua_error(ls);
  }

  return 0;
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
    lua_pushstring(ls, "Incorrect arguments to creature_is_class");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_item_count");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to count_currency");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_unidentified_item_count");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to is_item_identified");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_item_value");
    lua_error(ls);
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
      ItemPtr item = game.get_action_manager_ref().inventory(creature, creature->get_inventory(), selected_filter, {}, false);

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
    lua_pushstring(ls, "Incorrect arguments to select_item");
    lua_error(ls);
  }

  lua_pushboolean(ls, selected_item);
  lua_pushstring(ls, item_id.c_str());
  lua_pushstring(ls, item_base_id.c_str());

  return 3;
}

// Set a creature hostile towards another.
// Argument 1: Creature to set the hostility on.
// Argument 2: Creature to be hostile towards.
// Argument 3 (opt): hostility level.
int set_hostility(lua_State* ls)
{
  int num_args = lua_gettop(ls);

  if (num_args == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string hostile_creature_id = lua_tostring(ls, 1);
    string hostile_towards_id = lua_tostring(ls, 2);

    CreaturePtr creature = get_creature(hostile_creature_id);
    
    if (creature != nullptr)
    {
      HostilityManager hm;
      hm.set_hostility_to_creature(creature, hostile_towards_id);
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to set_hostility");
    lua_error(ls);
  }

  return 0;
}

int teleport(lua_State* ls)
{
  if (lua_gettop(ls) >= 1 && lua_isstring(ls, 1))
  {
    Game& game = Game::instance();
    ActionManager& am = game.get_action_manager_ref();

    string creature_id = lua_tostring(ls, 1);
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
        MapUtils::add_or_update_location(map, creature, make_pair(y, x), MapUtils::get_tile_for_creature(map, creature));
      }
      else
      {
        EffectPtr teleport_effect = EffectFactory::create_effect(EffectType::EFFECT_TYPE_TELEPORT);
        teleport_effect->effect(creature, &am, ItemStatus::ITEM_STATUS_BLESSED);
      }
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to teleport");
    lua_error(ls);
  }

  return 0;
}

// Get the appropriate creature description, based on whether the viewing
// creature can actually see or not.
int get_creature_description(lua_State* ls)
{
  string creature_desc;

  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isstring(ls, 2))
  {
    string viewing_creature_id = lua_tostring(ls, 1);
    string creature_id = lua_tostring(ls, 2);

    CreaturePtr viewing_creature = get_creature(viewing_creature_id);
    CreaturePtr creature = get_creature(creature_id);

    CreatureDescriber cd(viewing_creature, creature);
    creature_desc = cd.describe();
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to get_creature_description");
    lua_error(ls);
  }

  lua_pushstring(ls, creature_desc.c_str());
  return 1;
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
      pair<bool, vector<ItemPtr>> items = im.remove_item_from_eq_or_inv(transfer_from_creature, item_base_id, quantity);

      IInventoryPtr inv = transfer_to_creature->get_inventory();

      for (ItemPtr item : items.second)
      {
        inv->add(item);
      }

      item_transferred = items.first;
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to transfer_item");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to creature_tile_has_item");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to pick_up_item");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to identify_item");
    lua_error(ls);
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
    ItemType item_type = static_cast<ItemType>(lua_tointeger(ls, 2));
    CreaturePtr creature = get_creature(creature_id);

    Game& game = Game::instance();
    const map<string, ItemPtr>& items = game.get_items_ref();

    for (const pair<string, ItemPtr>& item_pair : items)
    {
      ItemIdentifier iid;
      ItemPtr item = item_pair.second;

      if ((item->get_type() == item_type) && (!iid.get_item_identified(item, true)))
      {
        iid.set_item_identified(creature, item, item->get_base_id(), true);
        num_identified++;
      }
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to identify_item_type");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to calendar_add_seconds");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to calendar_add_minutes");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to calendar_add_hours");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to calendar_add_days");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to calendar_add_years");
    lua_error(ls);
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
      Mortuary& mort = creature->get_mortuary_ref();

      for (int i = 0; i < quantity; i++)
      {
        mort.add_creature_kill(killed_id);
      }

      Game& game = game.instance();
      Mortuary& global_mort = game.get_mortuary_ref();

      for (int i = 0; i < quantity; i++)
      {
        global_mort.add_creature_kill(killed_id);
      }
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_kill_to_creature_mortuary");
    lua_error(ls);
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

      IMessageManager& manager = MM::instance();
      manager.clear_if_necessary();
      manager.add_new_message(msg.str());
      manager.send();
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to report_coords");
    lua_error(ls);
  }

  return 0;
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
    lua_pushstring(ls, "Incorrect arguments to cast_spell");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to bless_equipment");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to curse_equipment");
    lua_error(ls);
  }

  lua_pushboolean(ls, cursed_eq);
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
      IInventoryPtr inv = creature->get_inventory();

      if (inv != nullptr)
      {
        list<ItemPtr> items = inv->get_items_ref();

        for (ItemPtr item : items)
        {
          if (item != nullptr)
          {
            item->set_status(ItemStatus::ITEM_STATUS_CURSED);
            cursed_inv = true;
          }
        }
      }
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to curse_inventory");
    lua_error(ls);
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

    CreatureWin win_type = CreatureWin::CREATURE_WIN_REGULAR;

    if (num_args == 2 && lua_isnumber(ls, 2))
    {
      win_type = static_cast<CreatureWin>(lua_tointeger(ls, 2));
    }

    if (creature != nullptr)
    {
      creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_WINNER, to_string(static_cast<int>(win_type)));
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to set_winner");
    lua_error(ls);
  }

  return 0;
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
      colour = static_cast<int>(creature->get_colour());
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to get_creature_colour");
    lua_error(ls);
  }

  lua_pushinteger(ls, colour);
  return 1;
}

int set_creature_colour(lua_State* ls)
{
  if (lua_gettop(ls) == 2 && lua_isstring(ls, 1) && lua_isnumber(ls, 2))
  {
    string creature_id = lua_tostring(ls, 1);
    CreaturePtr creature = get_creature(creature_id);
    Colour new_colour = static_cast<Colour>(lua_tointeger(ls, 2));

    if (creature != nullptr)
    {
      creature->set_colour(new_colour);
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to set_creature_colour");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to set_creature_evade");
    lua_error(ls);
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

    if (num_args == 4 && lua_isstring(ls, 4))
    {
      trap_id = lua_tostring(ls, 4);
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
    lua_pushstring(ls, "Incorrect arguments to set_trap");
    lua_error(ls);
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

    for (const auto creature_pair : creatures)
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
    lua_pushstring(ls, "Incorrect arguments to get_nearby_hostile_creatures");
    lua_error(ls);
  }

  return num_hostiles;
}

int set_creature_additional_property(lua_State* ls)
{
  if (lua_gettop(ls) == 3 && lua_isstring(ls, 1) && lua_isstring(ls, 2) && lua_isstring(ls, 3))
  {
    string creature_id = lua_tostring(ls, 1);
    string prop_name = lua_tostring(ls, 2);
    string prop_value = lua_tostring(ls, 3);

    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr)
    {
      creature->set_additional_property(prop_name, prop_value);
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to set_creature_additional_property");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_creature_additional_property");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_creature_additional_property_csv");
    lua_error(ls);
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

      for (const auto c_pair : creatures)
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
    lua_pushstring(ls, "Incorrect arguments to is_creature_in_view_map");
    lua_error(ls);
  }

  lua_pushboolean(ls, creature_in_map);
  return 1;
}

int redraw(lua_State* ls)
{
  if (lua_gettop(ls) == 0)
  {
    string creature_id = CreatureID::CREATURE_ID_PLAYER;
    Game& game = Game::instance();
    MapPtr cur_map = game.get_current_map();
    CreaturePtr creature = get_creature(creature_id);

    if (creature != nullptr && cur_map != nullptr)
    {
      MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();

      // Force a hard redraw.
      game.update_display(creature, cur_map, fov_map, true);
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to redraw");
    lua_error(ls);
  }

  return 0;
}

int get_race_ids(lua_State* ls)
{
  int race_cnt = 0;

  if (lua_gettop(ls) <= 1)
  {
    bool include_user_playable = false;

    if (lua_gettop(ls) == 1 && lua_isboolean(ls, 1))
    {
      include_user_playable = (lua_toboolean(ls, 2) != 0);
    }

    Game& game = Game::instance();
    const RaceMap& rm = game.instance().get_races_ref();

    for (const auto& race_pair : rm)
    {
      RacePtr race = race_pair.second;

      if (race != nullptr && !race_pair.first.empty() && (include_user_playable || !race->get_user_playable()))
      {
        lua_pushstring(ls, race_pair.first.c_str());
        race_cnt++;
      }
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to get_race_ids");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_unarmed_slays");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to add_unarmed_slay");
    lua_error(ls);
  }

  return 0;
}

int get_race_name(lua_State* ls)
{
  string race_name;

  if (lua_gettop(ls) == 1 && lua_isstring(ls, 1))
  {
    string race_id = lua_tostring(ls, 1);
    RaceManager rm;
    RacePtr race = rm.get_race(race_id);

    if (race != nullptr)
    {
      race_name = StringTable::get(race->get_race_name_sid());
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to get_race_name");
    lua_error(ls);
  }

  lua_pushstring(ls, race_name.c_str());
  return 1;
}

int set_inscription(lua_State* ls)
{
  if (lua_gettop(ls) == 3 && lua_isnumber(ls, 1) && lua_isnumber(ls, 2) && lua_isstring(ls, 3))
  {
    int row = lua_tointeger(ls, 1);
    int col = lua_tointeger(ls, 2);
    string inscription = lua_tostring(ls, 3);

    Game& game = Game::instance();
    MapPtr map = game.get_current_map();

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
    lua_pushstring(ls, "Incorrect arguments to set_inscription");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_map_dimensions");
    lua_error(ls);
  }

  lua_pushnumber(ls, rows);
  lua_pushnumber(ls, cols);

  return 2;
}

int get_coords_with_tile_type_in_range(lua_State* ls)
{
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
    lua_pushstring(ls, "Incorrect arguments to get_coords_with_tile_type_in_range");
    lua_error(ls);
  }

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
    lua_pushstring(ls, "Incorrect arguments to get_custom_map_id");
    lua_error(ls);
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
    cm.attack(attacking_creature, attacked_creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY, false, damage);
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to ranged_attack");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_spellbooks");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to set_shop_shopkeeper_id");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to repop_shop");
    lua_error(ls);
  }

  lua_pushboolean(ls, repopped);
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
    lua_pushstring(ls, "Incorrect arguments to get_unpaid_amount");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to set_items_paid");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to bargain_discount");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to bargain_premium");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_item_type");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_shop_id");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_stocked_item_types");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to get_sale_price");
    lua_error(ls);
  }

  lua_pushinteger(ls, sale_price);
  return 1;
}

int set_item_unpaid(lua_State* ls)
{
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
          item->set_unpaid(true);
        }
      }
    }
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to set_item_unpaid");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to is_in_shop");
    lua_error(ls);
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
    lua_pushstring(ls, "Incorrect arguments to is_item_unpaid");
    lua_error(ls);
  }

  lua_pushboolean(ls, is_unpaid);
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
    lua_pushstring(ls, "Incorrect arguments to stop_playing_game");
    lua_error(ls);
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
