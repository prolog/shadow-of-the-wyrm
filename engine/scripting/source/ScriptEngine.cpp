#include "Conversion.hpp"
#include "GameEnvTextKeys.hpp"
#include "Log.hpp"
#include "LuaAPIFunctions.hpp"
#include "LuaItemFilter.hpp"
#include "MessageManagerFactory.hpp"
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

  lua_exportConst(ls, CITEM_FILTER_NONE);
  lua_exportConst(ls, CITEM_FILTER_UNIDENTIFIED);
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
bool ScriptEngine::execute(const string& script)
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
  IMessageManager& manager = MessageManagerFactory::instance();
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