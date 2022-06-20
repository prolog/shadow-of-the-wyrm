extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "MapScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string MapScript::MAP_MODULE_NAME = "map_events";
const string MapScript::MAP_FUNCTION_NAME = "init_map";

// Return true if the script executed successfully, false otherwise.
bool MapScript::execute(ScriptEngine& se, const string& map_script, MapPtr map)
{
  Log& log = Log::instance();
  log.trace("MapScript::execute - begin");
  log.debug("Lua stack size: " + to_string(se.get_stack_size()));

  if (map_script.empty())
  {
    return false;
  }

  bool result = true;
  string map_id;

  if (map != nullptr)
  {
    map_id = map->get_map_id();
  }

  if (se.execute(map_script, {{"map_id", map_id}}))
  {
    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, MAP_MODULE_NAME.c_str());
    lua_getfield(L, -1, MAP_FUNCTION_NAME.c_str());
    lua_pushstring(L, map_id.c_str());

    // Do the function call.  The "init_map" function returns nothing.
    if (lua_pcall(L, 1, 0, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "MapScript::execute - error running Lua function `" + MAP_FUNCTION_NAME + "': " + l_err;
      log.error(error_msg);
      lua_pop(L, 1);
      result = false;
    }

    lua_pop(L, 1);
  }
  else
  {
    log.error("MapScript::execute - did not run Lua function due to script failure: " + map_script);
    result = false;
  }

  log.debug("Lua stack size: " + to_string(se.get_stack_size()));
  log.trace("MapScript::execute - exiting");
  return result;
}

