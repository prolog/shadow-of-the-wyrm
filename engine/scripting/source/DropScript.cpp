extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "DropScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string DropScript::DROP_MODULE_NAME = "drop";
const string DropScript::DROP_FUNCTION_NAME = "drop";

// Execute a drop script.
// Return true if the script executed successfully, false otherwise.
bool DropScript::execute(ScriptEngine& se, const string& drop_script, const string& dropping_creature_id, CreaturePtr reacting_creature, ItemPtr item, const Coordinate& drop_coords)
{
  if (drop_script.empty())
  {
    return false;
  }

  bool result = true;

  if (se.execute(drop_script, {}))
  {
    string reacting_creature_base_id;
    string reacting_creature_id;
    string item_id;
    string item_base_id;

    if (reacting_creature != nullptr)
    {
      reacting_creature_base_id = reacting_creature->get_original_id();
      reacting_creature_id = reacting_creature->get_id();
    }

    if (item != nullptr)
    {
      item_id = item->get_id();
      item_base_id = item->get_base_id();
    }

    if (reacting_creature_base_id.empty() || reacting_creature_id.empty() || (item == nullptr))
    {
      return false;
    }

    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, DROP_MODULE_NAME.c_str());
    lua_getfield(L, -1, DROP_FUNCTION_NAME.c_str());
    lua_pushstring(L, dropping_creature_id.c_str());
    lua_pushstring(L, reacting_creature_id.c_str());
    lua_pushstring(L, reacting_creature_base_id.c_str());
    lua_pushstring(L, item_id.c_str());
    lua_pushstring(L, item_base_id.c_str());
    lua_pushinteger(L, drop_coords.first);
    lua_pushinteger(L, drop_coords.second);

    // Do the function call.  The drop function returns nothing.
    if (lua_pcall(L, 7, 0, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "DropScript::execute - error running Lua function `" + DROP_FUNCTION_NAME + "': " + l_err;
      Log::instance().error(error_msg);
      result = false;
    }
  }
  else
  {
    Log::instance().error("DropScript::execute - did not run Lua function due to script failure: " + drop_script);
    result = false;
  }


  return result;
}

