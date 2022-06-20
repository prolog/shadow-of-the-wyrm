extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "Conversion.hpp"
#include "ItemScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string ItemScript::ITEM_MODULE_NAME = "items";
const string ItemScript::ITEM_FUNCTION_NAME = "item_event_fn";
const string ItemScript::GET_TREASURE_ITEMS_FUNCTION_NAME = "get_treasure_items";

// Execute an item script.
// Return true if the script executed successfully, false otherwise.
bool ItemScript::execute(ScriptEngine& se, const string& item_script, const string& item_event, const string& base_item_id, const map<string, string>& properties, const string& original_creature_id, const int row, const int col)
{
  bool result = true;
  
  if (se.execute(item_script, {}))
  {
    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, ITEM_MODULE_NAME.c_str());
    lua_getfield(L, -1, ITEM_FUNCTION_NAME.c_str());
    lua_pushstring(L, base_item_id.c_str());
    lua_pushstring(L, String::create_csv_from_string_map(properties).c_str());
    lua_pushstring(L, original_creature_id.c_str());
    lua_pushstring(L, item_event.c_str());
    lua_pushinteger(L, row);
    lua_pushinteger(L, col);

    // Do the function call.  The item function returns nothing.
    if (lua_pcall(L, 6, 0, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "ItemScript::execute - error running Lua function `" + ITEM_FUNCTION_NAME + "': " + l_err;
      Log::instance().error(error_msg);
      lua_pop(L, 1);
      result = false;
    }
  }
  else
  {
    Log::instance().error("ItemScript::execute - did not run Lua function due to errors in the item script: " + item_script);
  }

  return result;
}

vector<string> ItemScript::execute_get_treasure_items(ScriptEngine& se)
{
  vector<string> item_ids;

  if (se.execute("items/treasure.lua", {}))
  {
    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, GET_TREASURE_ITEMS_FUNCTION_NAME.c_str());

    // Do the function call.  get_treasure_items returns nothing.
    if (lua_pcall(L, 0, 1, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "ItemScript::execute_get_treasure_items - error running Lua function `" + GET_TREASURE_ITEMS_FUNCTION_NAME + "': " + l_err;
      Log::instance().error(error_msg);
      lua_pop(L, 1);
    }
    else
    {
      string item_ids_s;
      
      int st_size = lua_gettop(L);

      if (lua_isstring(L, -1))
      {
        item_ids_s = lua_tostring(L, -1);
      } 

      item_ids = String::create_string_vector_from_csv_string(item_ids_s);
      lua_pop(L, 1);
    }
  }

  return item_ids;
}
