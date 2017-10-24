#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <string>
#include <vector>

// A collection of Lua-related utility functions.
class LuaUtils
{
  public:
    // Assumes an array (integer indices, no holes).
    static std::vector<std::string> get_string_array_from_table(lua_State* ls, int lua_index);
    
    // Functions for making setting table fields less repititious.
    static void set_field(lua_State* ls, const char* field_name, const bool val);
    static void set_field(lua_State* ls, const char* field_name, const int val);

  protected:
    LuaUtils();
    ~LuaUtils();
};

