#include "Conversion.hpp"
#include "CitySectorTypes.hpp"
#include "GameEnvTextKeys.hpp"
#include "Log.hpp"
#include "LuaAPIFunctions.hpp"
#include "LuaItemFilter.hpp"
#include "MessageManagerFactory.hpp"
#include "ReligionConstants.hpp"
#include "ScriptEngine.hpp"
#include "Serialize.hpp"

using namespace std;

#define lua_exportConst(ls, name) { lua_pushnumber(ls, name); lua_setglobal(ls, #name); }

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
   luaopen_base(L);
   
   set_constants(L);
   load_modules();
   register_api_functions();
}

void ScriptEngine::load_modules()
{
  // Update the environment so that the "/script" directory 
  // and certain subdirectories are assumed.
  if (luaL_loadfile(L, "scripts/env.lua") || lua_pcall(L, 0, 0, 0))
  {
    log_error();
  }
}

void ScriptEngine::set_constants(lua_State* ls)
{
  lua_exportConst(ls, CLOG_TRACE);
  lua_exportConst(ls, CLOG_DEBUG);
  lua_exportConst(ls, CLOG_INFO);
  lua_exportConst(ls, CLOG_ERROR);

  lua_exportConst(ls, CPIETY_CROWNING);

  lua_exportConst(ls, CDIRECTION_SOUTH_WEST);
  lua_exportConst(ls, CDIRECTION_SOUTH);
  lua_exportConst(ls, CDIRECTION_SOUTH_EAST);
  lua_exportConst(ls, CDIRECTION_WEST);
  lua_exportConst(ls, CDIRECTION_NULL);
  lua_exportConst(ls, CDIRECTION_EAST);
  lua_exportConst(ls, CDIRECTION_NORTH_WEST);
  lua_exportConst(ls, CDIRECTION_NORTH);
  lua_exportConst(ls, CDIRECTION_NORTH_EAST);
  lua_exportConst(ls, CDIRECTION_UP);
  lua_exportConst(ls, CDIRECTION_DOWN);

  lua_exportConst(ls, CITEM_TYPE_POTION);
  lua_exportConst(ls, CITEM_TYPE_WAND);
  lua_exportConst(ls, CITEM_TYPE_SCROLL);
  lua_exportConst(ls, CITEM_TYPE_SPELLBOOK);
  lua_exportConst(ls, CITEM_TYPE_RING);
  lua_exportConst(ls, CITEM_TYPE_AMULET);

  lua_exportConst(ls, CTILE_TYPE_UNDEFINED);
  lua_exportConst(ls, CTILE_TYPE_FIRST);
  lua_exportConst(ls, CTILE_TYPE_FIELD);
  lua_exportConst(ls, CTILE_TYPE_SCRUB);
  lua_exportConst(ls, CTILE_TYPE_WHEAT);
  lua_exportConst(ls, CTILE_TYPE_CAIRN);
  lua_exportConst(ls, CTILE_TYPE_TREE);
  lua_exportConst(ls, CTILE_TYPE_DESERT);
  lua_exportConst(ls, CTILE_TYPE_ROAD);
  lua_exportConst(ls, CTILE_TYPE_RIVER);
  lua_exportConst(ls, CTILE_TYPE_SEA);
  lua_exportConst(ls, CTILE_TYPE_SHOALS);
  lua_exportConst(ls, CTILE_TYPE_DUNGEON);
  lua_exportConst(ls, CTILE_TYPE_ROCK);
  lua_exportConst(ls, CTILE_TYPE_GRAVE);
  lua_exportConst(ls, CTILE_TYPE_MARSH);
  lua_exportConst(ls, CTILE_TYPE_REEDS);
  lua_exportConst(ls, CTILE_TYPE_HILLS);
  lua_exportConst(ls, CTILE_TYPE_MOUNTAINS);
  lua_exportConst(ls, CTILE_TYPE_BEACH);
  lua_exportConst(ls, CTILE_TYPE_BUSH);
  lua_exportConst(ls, CTILE_TYPE_WEEDS);
  lua_exportConst(ls, CTILE_TYPE_SPRINGS);
  lua_exportConst(ls, CTILE_TYPE_FOREST);
  lua_exportConst(ls, CTILE_TYPE_UP_STAIRCASE);
  lua_exportConst(ls, CTILE_TYPE_DOWN_STAIRCASE);
  lua_exportConst(ls, CTILE_TYPE_CAVERN);
  lua_exportConst(ls, CTILE_TYPE_VILLAGE);
  lua_exportConst(ls, CTILE_TYPE_DUNGEON_COMPLEX);
  lua_exportConst(ls, CTILE_TYPE_BARRACKS);
  lua_exportConst(ls, CTILE_TYPE_CASTLE);
  lua_exportConst(ls, CTILE_TYPE_KEEP);
  lua_exportConst(ls, CTILE_TYPE_GRAVEYARD);
  lua_exportConst(ls, CTILE_TYPE_CHURCH);
  lua_exportConst(ls, CTILE_TYPE_LIBRARY);
  lua_exportConst(ls, CTILE_TYPE_SITE_OF_DEATH);
  lua_exportConst(ls, CTILE_TYPE_TEMPLE);
  lua_exportConst(ls, CTILE_TYPE_DAIS);
  lua_exportConst(ls, CTILE_TYPE_PIER);
  lua_exportConst(ls, CTILE_TYPE_BARROW);
  lua_exportConst(ls, CTILE_TYPE_WILD_ORCHARD);
  lua_exportConst(ls, CTILE_TYPE_FRUIT_TREE);
  lua_exportConst(ls, CTILE_TYPE_EVERGREEN_TREE);
  lua_exportConst(ls, CTILE_TYPE_ROCKY_EARTH);
  lua_exportConst(ls, CTILE_TYPE_MINE);
  lua_exportConst(ls, CTILE_TYPE_WELL);
  lua_exportConst(ls, CTILE_TYPE_CRYPT);
  lua_exportConst(ls, CTILE_TYPE_AIR);
  lua_exportConst(ls, CTILE_TYPE_EARTH);
  lua_exportConst(ls, CTILE_TYPE_SEWER_COMPLEX);
  lua_exportConst(ls, CTILE_TYPE_SEWER);
  lua_exportConst(ls, CTILE_TYPE_SHRINE);
  lua_exportConst(ls, CTILE_TYPE_SEABED);
  lua_exportConst(ls, CTILE_TYPE_AQUATIC_VEGETATION);
  lua_exportConst(ls, CTILE_TYPE_FLOATING_TOWER);
  lua_exportConst(ls, CTILE_TYPE_VOID);
  lua_exportConst(ls, CTILE_TYPE_MAGICAL_TREE);

  static_assert(TileType::TILE_TYPE_LAST == TileType(55), "Unrecognized TILE_TYPE_LAST");

  lua_exportConst(ls, CITEM_FILTER_NONE);
  lua_exportConst(ls, CITEM_FILTER_UNIDENTIFIED);
  lua_exportConst(ls, CITEM_FILTER_ARTIFACT);

  lua_exportConst(ls, CSKILL_GENERAL_ARCHERY);
  lua_exportConst(ls, CSKILL_GENERAL_AWARENESS);
  lua_exportConst(ls, CSKILL_GENERAL_BARGAINING);
  lua_exportConst(ls, CSKILL_GENERAL_BEASTMASTERY);
  lua_exportConst(ls, CSKILL_GENERAL_BLIND_FIGHTING);
  lua_exportConst(ls, CSKILL_GENERAL_BOATING);
  lua_exportConst(ls, CSKILL_GENERAL_BOWYER);
  lua_exportConst(ls, CSKILL_GENERAL_BREWING);
  lua_exportConst(ls, CSKILL_GENERAL_CARRYING);
  lua_exportConst(ls, CSKILL_GENERAL_COMBAT);
  lua_exportConst(ls, CSKILL_GENERAL_CRAFTING);
  lua_exportConst(ls, CSKILL_GENERAL_DESERT_LORE);
  lua_exportConst(ls, CSKILL_GENERAL_DETECTION);
  lua_exportConst(ls, CSKILL_GENERAL_DISARM_TRAPS);
  lua_exportConst(ls, CSKILL_GENERAL_DUAL_WIELD);
  lua_exportConst(ls, CSKILL_GENERAL_DUNGEONEERING);
  lua_exportConst(ls, CSKILL_GENERAL_ESCAPE);
  lua_exportConst(ls, CSKILL_GENERAL_FISHING);
  lua_exportConst(ls, CSKILL_GENERAL_FLETCHERY);
  lua_exportConst(ls, CSKILL_GENERAL_FORAGING);
  lua_exportConst(ls, CSKILL_GENERAL_FOREST_LORE);
  lua_exportConst(ls, CSKILL_GENERAL_HERBALISM);
  lua_exportConst(ls, CSKILL_GENERAL_HIDING);
  lua_exportConst(ls, CSKILL_GENERAL_HUNTING);
  lua_exportConst(ls, CSKILL_GENERAL_INTIMIDATION);
  lua_exportConst(ls, CSKILL_GENERAL_JEWELER);
  lua_exportConst(ls, CSKILL_GENERAL_JUMPING);
  lua_exportConst(ls, CSKILL_GENERAL_LEADERSHIP);
  lua_exportConst(ls, CSKILL_GENERAL_LITERACY);
  lua_exportConst(ls, CSKILL_GENERAL_LORE);
  lua_exportConst(ls, CSKILL_GENERAL_MAGIC);
  lua_exportConst(ls, CSKILL_GENERAL_MARSH_LORE);
  lua_exportConst(ls, CSKILL_GENERAL_MEDICINE);
  lua_exportConst(ls, CSKILL_GENERAL_MOUNTAINEERING);
  lua_exportConst(ls, CSKILL_GENERAL_MOUNTAIN_LORE);
  lua_exportConst(ls, CSKILL_GENERAL_MUSIC);
  lua_exportConst(ls, CSKILL_GENERAL_NIGHT_SIGHT);
  lua_exportConst(ls, CSKILL_GENERAL_OCEANOGRAPHY);
  lua_exportConst(ls, CSKILL_GENERAL_PAPERCRAFT);
  lua_exportConst(ls, CSKILL_GENERAL_RELIGION);
  lua_exportConst(ls, CSKILL_GENERAL_SCRIBING);
  lua_exportConst(ls, CSKILL_GENERAL_SKINNING);
  lua_exportConst(ls, CSKILL_GENERAL_SMITHING);
  lua_exportConst(ls, CSKILL_GENERAL_SPELUNKING);
  lua_exportConst(ls, CSKILL_GENERAL_STEALTH);
  lua_exportConst(ls, CSKILL_GENERAL_SWIMMING);
  lua_exportConst(ls, CSKILL_GENERAL_TANNING);
  lua_exportConst(ls, CSKILL_GENERAL_THIEVERY);
  lua_exportConst(ls, CSKILL_GENERAL_WANDCRAFT);
  lua_exportConst(ls, CSKILL_GENERAL_WEAVING);

  lua_exportConst(ls, CSKILL_MELEE_AXES);
  lua_exportConst(ls, CSKILL_MELEE_BLUDGEONS);
  lua_exportConst(ls, CSKILL_MELEE_DAGGERS);
  lua_exportConst(ls, CSKILL_MELEE_EXOTIC);
  lua_exportConst(ls, CSKILL_MELEE_LONG_BLADES);
  lua_exportConst(ls, CSKILL_MELEE_RODS_AND_STAVES);
  lua_exportConst(ls, CSKILL_MELEE_SHORT_BLADES);
  lua_exportConst(ls, CSKILL_MELEE_SPEARS);
  lua_exportConst(ls, CSKILL_MELEE_UNARMED);
  lua_exportConst(ls, CSKILL_MELEE_WHIPS);

  lua_exportConst(ls, CSKILL_RANGED_AXES);
  lua_exportConst(ls, CSKILL_RANGED_BLADES);
  lua_exportConst(ls, CSKILL_RANGED_BLUDGEONS);
  lua_exportConst(ls, CSKILL_RANGED_BOWS);
  lua_exportConst(ls, CSKILL_RANGED_CROSSBOWS);
  lua_exportConst(ls, CSKILL_RANGED_DAGGERS);
  lua_exportConst(ls, CSKILL_RANGED_EXOTIC);
  lua_exportConst(ls, CSKILL_RANGED_ROCKS);
  lua_exportConst(ls, CSKILL_RANGED_SLINGS);
  lua_exportConst(ls, CSKILL_RANGED_SPEARS);

  lua_exportConst(ls, CSKILL_MAGIC_ARCANE);
  lua_exportConst(ls, CSKILL_MAGIC_CANTRIPS);
  lua_exportConst(ls, CSKILL_MAGIC_DIVINE);
  lua_exportConst(ls, CSKILL_MAGIC_MYSTIC);
  lua_exportConst(ls, CSKILL_MAGIC_PRIMORDIAL);

  lua_exportConst(ls, CCREATURE_WIN_REGULAR);
  lua_exportConst(ls, CCREATURE_WIN_EVIL);
  lua_exportConst(ls, CCREATURE_WIN_GODSLAYER);

  lua_exportConst(ls, CCLASS_ID_KING_DECORATIVE_STATUE);
  lua_exportConst(ls, CCLASS_ID_QUEEN_DECORATIVE_STATUE);
  lua_exportConst(ls, CCLASS_ID_WARLORD_DECORATIVE_STATUE);
  lua_exportConst(ls, CCLASS_ID_KNIGHT_DECORATIVE_STATUE);
  lua_exportConst(ls, CCLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE);
  lua_exportConst(ls, CCLASS_ID_SORCEROR_DECORATIVE_STATUE);
  lua_exportConst(ls, CCLASS_ID_FIRE_PILLAR);
  lua_exportConst(ls, CCLASS_ID_FOUNTAIN);
  lua_exportConst(ls, CCLASS_ID_FORGE);
  lua_exportConst(ls, CCLASS_ID_TANNERY);
  lua_exportConst(ls, CCLASS_ID_JEWELER_WORKBENCH);
  lua_exportConst(ls, CCLASS_ID_WHEEL_AND_LOOM);

  lua_exportConst(ls, CCITY_SECTOR_PUBLIC_AREA);
  lua_exportConst(ls, CCITY_SECTOR_LOW_INCOME_RESIDENTIAL);
  lua_exportConst(ls, CCITY_SECTOR_RESIDENTIAL);
  lua_exportConst(ls, CCITY_SECTOR_RELIGIOUS_COMMERCIAL);
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
// As we're just running a script, pass any desired arguments as a table.
bool ScriptEngine::execute(const string& script, const map<string, string>& script_args)
{
  bool ret_val = false;

  try
  {
    if (script.empty())
    {
      lua_pushstring(L, "Could not run script (no script provided)");
      log_error();
    }
    else
    {
      string script_file = "scripts/" + script;

      // Init the table
      lua_newtable(L);

      // Set the table values
      for (const auto &sa_pair : script_args)
      {
        lua_pushstring(L, sa_pair.first.c_str());
        lua_pushstring(L, sa_pair.second.c_str());
        lua_rawset(L, -3);
      }

      // Set table size
      lua_pushliteral(L, "n");
      lua_pushnumber(L, script_args.size());
      lua_rawset(L, -3);

      // Expose to the script
      lua_setglobal(L, "args");

      if (luaL_loadfile(L, script_file.c_str()) || lua_pcall(L, 0, 0, 0))
      {
        log_error();
      }
      else
      {
        ret_val = true;
      }
    }
  }
  catch (...)
  {
    lua_pushstring(L, "Exception while trying to run script.");
    log_error();
  }

  return ret_val;
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

// Call a function in the Lua environment.
void ScriptEngine::call_function(const string& fn_name, const vector<string>& param_types, const vector<string>& param_values, const int n_return_vals)
{
  if (param_types.size() != param_values.size())
  {
    return;
  }

  lua_getglobal(L, fn_name.c_str());

  process_function_arguments(param_types, param_values);

  lua_pcall(L, param_types.size(), n_return_vals, 0);

  // JCD FIXME: update this whenever I need to actually use return values.
  lua_pop(L, n_return_vals);
}

// Handle arguments to a Lua function.
void ScriptEngine::process_function_arguments(const vector<string>& param_types, const vector<string>& param_values)
{
  for (uint i = 0; i < param_types.size(); i++)
  {
    string param_type = param_types.at(i);
    string param_value = param_values.at(i);

    if (param_type == "string")
    {
      lua_pushstring(L, param_value.c_str());
    }
    else if (param_type == "number")
    {
      lua_pushnumber(L, String::to_float(param_value));
    }
    else if (param_type == "integer")
    {
      lua_pushinteger(L, String::to_int(param_value));
    }
    else
    {
      Log& log = Log::instance();

      log.error("ScriptEngine::process_function_arguments - Unrecognized type \"" + param_type + "\" with value \"" + param_value + "\"");
    }
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
  IMessageManager& manager = MM::instance();
  manager.add_new_message(ui_error);
  manager.send();
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

bool ScriptEngine::serialize(ostream& stream) const
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
  return ClassIdentifier::CLASS_ID_SCRIPT_ENGINE;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScriptEngine_test.cpp"
#endif