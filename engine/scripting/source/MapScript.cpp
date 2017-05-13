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

const string MapScript::MAP_MODULE_NAME = "custom_map";
const string MapScript::MAP_FUNCTION_NAME = "init_map";

// Return true if the script executed successfully, false otherwise.
bool MapScript::execute(ScriptEngine& se, const string& map_script, MapPtr map)
{
  if (map_script.empty())
  {
    return false;
  }

  bool result = true;

  if (se.execute(map_script, {}))
  {
    string map_id;

    if (map != nullptr)
    {
      map_id = map->get_map_id();
    }

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
      Log::instance().error(error_msg);
      result = false;
    }
  }
  else
  {
    Log::instance().error("MapScript::execute - did not run Lua function due to script failure: " + map_script);
    result = false;
  }

  return result;
}

