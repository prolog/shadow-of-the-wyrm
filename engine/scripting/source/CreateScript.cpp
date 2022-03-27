extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "CreateScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string CreateScript::CREATE_MODULE_NAME = "create";
const string CreateScript::CREATE_FUNCTION_NAME = "create";

// Return true if the script executed successfully, false otherwise.
bool CreateScript::execute(ScriptEngine& se, const string& create_script, CreaturePtr new_creature, MapPtr map)
{
  if (create_script.empty())
  {
    return false;
  }

  bool result = true;

  if (se.execute(create_script, {}))
  {
    string new_creature_id;
    string new_creature_base_id;
    string map_id;

    if (new_creature != nullptr)
    {
      new_creature_id = new_creature->get_id();
      new_creature_base_id = new_creature->get_original_id();
    }

    if (map != nullptr)
    {
      map_id = map->get_map_id();
    }

    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, CREATE_MODULE_NAME.c_str());
    lua_getfield(L, -1, CREATE_FUNCTION_NAME.c_str());
    lua_pushstring(L, new_creature_id.c_str());
    lua_pushstring(L, new_creature_base_id.c_str());
    lua_pushstring(L, map_id.c_str());

    // Do the function call.  The "create" function returns nothing.
    if (lua_pcall(L, 3, 0, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "CreateScript::execute - error running Lua function `" + CREATE_FUNCTION_NAME + "': " + l_err;
      Log::instance().error(error_msg);
      lua_pop(L, 1);
      result = false;
    }
  }
  else
  {
    Log::instance().error("CreateScript::execute - did not run Lua function due to script failure: " + create_script);
    result = false;
  }

  return result;
}
