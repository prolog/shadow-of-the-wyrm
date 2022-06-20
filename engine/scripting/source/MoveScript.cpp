extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "MoveScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string MoveScript::MOVE_MODULE_NAME = "move";
const string MoveScript::MOVE_FUNCTION_NAME = "enter_tile";

// Return true if the script executed successfully, false otherwise.
bool MoveScript::execute(ScriptEngine& se, const string& event_script, CreaturePtr moving_creature, const string& map_id, const Coordinate& new_coords)
{
  Log& log = Log::instance();
  log.trace("MoveScript::execute - begin");
  log.debug("Lua stack size: " + to_string(se.get_stack_size()));

  if (event_script.empty() || moving_creature == nullptr)
  {
    return false;
  }

  bool result = true;
  map<string, string> args = {{"moving_creature_id", moving_creature->get_id()}};

  if (se.execute(event_script, args))
  {
    string moving_creature_id = moving_creature->get_id();

    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, MOVE_MODULE_NAME.c_str());
    lua_getfield(L, -1, MOVE_FUNCTION_NAME.c_str());
    lua_pushstring(L, moving_creature_id.c_str());
    lua_pushstring(L, map_id.c_str());
    lua_pushinteger(L, new_coords.first);
    lua_pushinteger(L, new_coords.second);

    // Do the function call.  The "move" function returns nothing.
    if (lua_pcall(L, 4, 0, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "MoveScript::execute - error running Lua function `" + MOVE_FUNCTION_NAME + "': " + l_err;
      log.error(error_msg);
      lua_pop(L, 1);
      result = false;
    }

    lua_pop(L, 1);
  }
  else
  {
    log.error("MoveScript::execute - did not run Lua function due to script failure: " + event_script);
    result = false;
  }

  log.debug("Lua stack size: " + to_string(se.get_stack_size()));
  log.trace("MoveScript::execute - exiting");
  return result;
}

