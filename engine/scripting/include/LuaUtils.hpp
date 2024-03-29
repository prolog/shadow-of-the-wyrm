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
    static void create_return_table_from_string_vector(lua_State* ls, const std::vector<std::string>& str_vec);
    static void create_return_table_from_int_vector(lua_State* ls, const std::vector<int>& int_vec);

    // Functions for making setting table fields less repititious.
    static void set_field(lua_State* ls, const char* field_name, const bool val);
    static void set_field(lua_State* ls, const char* field_name, const int val);

    static void log_and_raise(lua_State* ls, const std::string& error_message);
    static std::string get_traceback(lua_State* ls);
    static std::string get_stack_dump(lua_State* ls);

  protected:
    LuaUtils();
    ~LuaUtils();
};

