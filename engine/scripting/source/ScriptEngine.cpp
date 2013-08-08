#include "CreatureFactory.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "GameEnvTextKeys.hpp"
#include "ItemManager.hpp"
#include "Log.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "Quests.hpp"
#include "RNG.hpp"
#include "ScriptEngine.hpp"
#include "Serialize.hpp"
#include "StatusEffectFactory.hpp"
#include "StringTable.hpp"

using namespace std;

// Helper functions that can be used by the Lua API.
CreaturePtr local_creature;
void set_local_creature(CreaturePtr creature);
CreaturePtr get_creature(const string& creature_id);

// API prototypes
int add_message_with_pause(lua_State* ls);
int add_message(lua_State* ls);
int add_new_quest(lua_State* ls);
int is_on_quest(lua_State* ls);
int get_num_creature_killed_global(lua_State* ls);
int add_object_to_player_tile(lua_State* ls);
int mark_quest_completed(lua_State* ls);
int remove_active_quest(lua_State* ls);
int is_quest_completed(lua_State* ls);
int player_has_item(lua_State* ls);
int remove_object_from_player(lua_State* ls);
int is_item_generated(lua_State* ls);
int get_num_item_generated(lua_State* ls);
int set_skill_value(lua_State* ls);
int get_skill_value(lua_State* ls);
int RNG_range(lua_State* ls);
int add_spell_castings(lua_State* ls);
int gain_experience(lua_State* ls);
int add_creature_to_map(lua_State* ls);
int add_status_to_creature(lua_State* ls);

// Create a new Lua state object, and open the libraries.
ScriptEngine::ScriptEngine()
{
  initialize_state();
}

// Tear down the Lua state.
ScriptEngine::~ScriptEngine()
{
   lua_close(L);
}

bool ScriptEngine::operator==(const ScriptEngine& se) const
{
  bool result = true;

  result = result && (last_executed == se.last_executed);

  return result;
}

void ScriptEngine::set_creature(CreaturePtr creature)
{
  set_local_creature(creature);
}

bool ScriptEngine::clear_state()
{
  lua_close(L);
  initialize_state();

  return true;
}

void ScriptEngine::initialize_state()
{
   L = lua_open();
   luaL_openlibs(L);
   load_modules();
   register_api_functions();
}

void ScriptEngine::load_modules()
{
  // Update the environment so that the "/script" directory 
  // and certain subdirectories are assumed.
  luaL_dofile(L, "scripts/env.lua");
}

string ScriptEngine::get_table_str(lua_State* ls, const string& key)
{
  string value;
  lua_pushstring(ls, key.c_str());
  lua_gettable(ls, -2); // get table[key]
  
  if (!lua_isstring(ls, -1))
  {
    luaL_error(ls, "invalid key value - expected a string.");
  }

  value = lua_tostring(ls, -1);

  lua_pop(ls, 1); // remove value from stack
  
  return value;
}

// Run a particular script in the scripts folder.
void ScriptEngine::execute(const string& script)
{
  string script_file = "scripts/" + script;
  if (luaL_dofile(L, script_file.c_str()))
  {
    log_error();
  }
}

// Run a user-supplied command within the current Lua state.
void ScriptEngine::run_command(const string& command)
{
  if (luaL_dostring(L, command.c_str()))
  {
    // Error occurred! :(
    log_error();
  }
}

lua_State* ScriptEngine::get_current_state()
{
  return L;
}

// Log the most recently-occurred error.
void ScriptEngine::log_error()
{
  // An error occurred: pop the error off the stack, and log the message.
  Log& log = Log::instance();
  string error(lua_tostring(L, -1));

  log.error("ScriptEngine::log_error - Error in execution: " + error);

  // Add a message to the message manager.
  string ui_error = GameEnvTextKeys::get_lua_error(error);
  IMessageManager& manager = MessageManagerFactory::instance();
  manager.add_new_message(ui_error);
  manager.send();
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
  }

  CreaturePtr null_creature;
  return null_creature;
}

// Register all the functions available to the scripting engine.
void ScriptEngine::register_api_functions()
{
  lua_register(L, "add_message_with_pause", add_message_with_pause);
  lua_register(L, "add_message", add_message);
  lua_register(L, "add_new_quest", add_new_quest);
  lua_register(L, "is_on_quest", is_on_quest);
  lua_register(L, "get_num_creature_killed_global", get_num_creature_killed_global);
  lua_register(L, "add_object_to_player_tile", add_object_to_player_tile);
  lua_register(L, "mark_quest_completed", mark_quest_completed);
  lua_register(L, "remove_active_quest", remove_active_quest);
  lua_register(L, "is_quest_completed", is_quest_completed);
  lua_register(L, "player_has_item", player_has_item);
  lua_register(L, "remove_object_from_player", remove_object_from_player);
  lua_register(L, "is_item_generated", is_item_generated);
  lua_register(L, "get_num_item_generated", get_num_item_generated);
  lua_register(L, "set_skill_value", set_skill_value);
  lua_register(L, "get_skill_value", get_skill_value);
  lua_register(L, "RNG_range", RNG_range);
  lua_register(L, "add_spell_castings", add_spell_castings);
  lua_register(L, "gain_experience", gain_experience);
  lua_register(L, "add_creature_to_map", add_creature_to_map);
  lua_register(L, "add_status_to_creature", add_status_to_creature);
}

// Lua API functions:

// Functions callable by Lua that wrap the actual C++ functions for adding
// messages, getting/updating data, etc.

// Clear the message manager, add a new message, and force the user to 
// continue via a "..." type prompt.
static int add_message_with_pause(lua_State* ls)
{
  if(lua_gettop(ls) > 0 && lua_isstring(ls, -1))
	{
    string message_sid = lua_tostring(ls, 1);
    
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.clear_if_necessary();
    manager.add_new_message_with_pause(StringTable::get(message_sid));
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

// Clear the message manager, and add a new message.
// Arguments expected: 1.
// Argument type: string (resource SID)
static int add_message(lua_State* ls)
{
  if(lua_gettop(ls) > 0 && lua_isstring(ls, -1))
	{
		string message_sid = lua_tostring(ls, 1);

    IMessageManager& manager = MessageManagerFactory::instance();
    manager.clear_if_necessary();
    manager.add_new_message(StringTable::get(message_sid));
    manager.send();
	}
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_message");
    lua_error(ls);
  }

  return 0;
}

// Add a quest to the in-progress list.  Arguments are:
// - a string representing the quest ID
// - a table representing the "Quest" lua object.
static int add_new_quest(lua_State* ls)
{
  if ((lua_gettop(ls) == 2) && (lua_istable(ls, -1)) && (lua_isstring(ls, -2)))
  {
    Game& game = Game::instance();
    ScriptEngine& se = game.get_script_engine_ref();

    // JCD FIXME: Move the string values into a lua constants class?

    string quest_id = lua_tostring(ls, 1);
    string quest_title_sid = se.get_table_str(ls, "quest_title_sid");
    string questmaster_name_sid = se.get_table_str(ls, "questmaster_name_sid");
    string quest_description_sid = se.get_table_str(ls, "quest_description_sid");

    Quest new_quest(quest_id, quest_title_sid, questmaster_name_sid, quest_description_sid);

    game.get_quests_ref().add_new_quest(quest_id, new_quest);
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

// Add an object to the player's tile.
// Argument is the base item ID.
int add_object_to_player_tile(lua_State* ls)
{
  string object_base_id;
  uint quantity = 1;
  bool args_ok = false;

  if (lua_gettop(ls) >= 1)
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    CreaturePtr player = game.get_current_player();
    TilePtr player_tile = MapUtils::get_tile_for_creature(map, player); 
    string base_item_id = lua_tostring(ls, 1);
    uint quantity = static_cast<uint>(lua_tointeger(ls, 2));
    if (quantity == 0) ++quantity;

    ItemManager::create_item_with_probability(100, 100, player_tile->get_items(), base_item_id, quantity);
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_object_to_player_tile");
    lua_error(ls);
  }

  return 0;
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
  bool quest_removed = false;

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
  if ((lua_gettop(ls) == 1) && (lua_isstring(ls, -1)))
  {
    string object_base_id = lua_tostring(ls, 1);

    Game& game = Game::instance();
    CreaturePtr player = game.get_current_player();

    ItemManager im;
    im.remove_item_from_eq_or_inv(player, object_base_id);
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
    SpellKnowledge& sk = creature->get_spell_knowledge_ref();

    IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell_id);
    uint new_castings = isk.get_castings() + addl_castings;
    isk.set_castings(new_castings);
    sk.set_spell_knowledge(spell_id, isk);
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

    ExperienceManager em;
    em.gain_experience(creature, experience);
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to gain_experience");
    lua_error(ls);
  }

  return 0;
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

// Add a particular status to a particular creature for a particular duration
// in minutes.
//
// Returns true if the status was added, false in all other cases.
int add_status_to_creature(lua_State* ls)
{
  if ((lua_gettop(ls) == 2) && (lua_isstring(ls, 1) && (lua_isstring(ls, 2))))
  {
    Game& game = Game::instance();

    string creature_id = lua_tostring(ls, 1);
    string status_id = lua_tostring(ls, 2);
    CreaturePtr creature = get_creature(creature_id);

    if (creature && !creature->has_status(status_id))
    {
      StatusEffectPtr se = StatusEffectFactory::create_status_effect(status_id);
      se->apply_change(creature);

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

// Set the last executed command
void ScriptEngine::set_last_executed(const string& new_last_executed)
{
  last_executed = new_last_executed;
}

string ScriptEngine::get_last_executed() const
{
  return last_executed;
}

bool ScriptEngine::serialize(ostream& stream)
{
  Serialize::write_string(stream, last_executed);

  return true;
}

bool ScriptEngine::deserialize(istream& stream)
{
  Serialize::read_string(stream, last_executed);

  return true;
}

ClassIdentifier ScriptEngine::internal_class_identifier() const
{
  return CLASS_ID_SCRIPT_ENGINE;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScriptEngine_test.cpp"
#endif