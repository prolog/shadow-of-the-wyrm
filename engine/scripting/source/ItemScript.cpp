extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "ItemScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string ItemScript::ITEM_MODULE_NAME = "items";
const string ItemScript::ITEM_FUNCTION_NAME = "item_event_fn";

// Execute an item script.
// Return true if the script executed successfully, false otherwise.
bool ItemScript::execute(ScriptEngine& se, const string& item_script, const string& item_event, const string& base_item_id, const string& original_creature_id, const int row, const int col)
{
  bool result = true;
  se.execute(item_script);

  // Set up the function call parameters.
  lua_State* L = se.get_current_state();
  lua_getglobal(L, ITEM_MODULE_NAME.c_str());
  lua_getfield(L, -1, ITEM_FUNCTION_NAME.c_str());
  lua_pushstring(L, base_item_id.c_str());
  lua_pushstring(L, original_creature_id.c_str());
  lua_pushstring(L, item_event.c_str());
  lua_pushinteger(L, row);
  lua_pushinteger(L, col);

  // Do the function call.  The attack function returns nothing.
  if (lua_pcall(L, 5, 0, 0) != 0)
  {
    string l_err = lua_tostring(L, -1);
    string error_msg = "ItemScript::execute - error running Lua function `" + ITEM_FUNCTION_NAME + "': " + l_err;
    Log::instance().error(error_msg);
    result = false;
  }

  return result;
}

