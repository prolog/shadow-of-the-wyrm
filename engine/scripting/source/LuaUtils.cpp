#include "Log.hpp"
#include "LuaUtils.hpp"

using namespace std;

LuaUtils::LuaUtils()
{
}

LuaUtils::~LuaUtils()
{
}

vector<string> LuaUtils::get_string_array_from_table(lua_State* ls, int lua_index)
{
  vector<string> str_array;

  size_t sid_size = lua_objlen(ls, lua_index);

  for (size_t i = 1; i <= sid_size; i++)
  {
    // Get the value with key i, and put it on the stack.
    // Lua arrays start at 1.
    lua_pushnumber(ls, i);
    lua_gettable(ls, lua_index);

    if (!lua_isstring(ls, -1))
    {
      string msg = "Invalid string found in array!";
      lua_pushstring(ls, msg.c_str());
      lua_error(ls);

      Log::instance().error(msg);
    }
    else
    {
      string value = lua_tostring(ls, -1);
      str_array.push_back(value);
    }

    // Remove the value we just retrieved from the stack.
    lua_pop(ls, 1);
  }

  return str_array;
}