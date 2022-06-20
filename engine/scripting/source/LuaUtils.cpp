#include "Game.hpp"
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
  Log& log = Log::instance();
  log.trace("LuaUtils::get_string_array_from_table - starting");
  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));

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
      string msg = "LuaUtils::get_string_array_from_table - Invalid string found in array!";
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

  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));
  log.trace("LuaUtils::get_string_array_from_table - exiting");
  return str_array;
}

void LuaUtils::create_return_table_from_string_vector(lua_State* ls, const vector<string>& str_vec)
{
  Log& log = Log::instance();
  log.trace("LuaUtils::create_return_table_from_string_vector - starting");

  lua_newtable(ls);
  size_t str_vec_size = str_vec.size();

  lua_createtable(ls, static_cast<int>(str_vec_size), 0);

  for (unsigned int i = 0; i < str_vec_size; i++)
  {
    string cur_item = str_vec.at(i);

    lua_pushstring(ls, cur_item.c_str());
    lua_rawseti(ls, -2, i + 1);
  }

  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));
  log.trace("LuaUtils::create_return_table_from_string_vector - exiting");
}

void LuaUtils::create_return_table_from_int_vector(lua_State* ls, const vector<int>& int_vec)
{
  Log& log = Log::instance();
  log.trace("LuaUtils::create_return_table_from_int_vector - starting");
  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));

  lua_newtable(ls);
  size_t int_vec_size = int_vec.size();

  lua_createtable(ls, static_cast<int>(int_vec_size), 0);

  for (unsigned int i = 0; i < int_vec_size; i++)
  {
    int cur_item = int_vec.at(i);

    lua_pushinteger(ls, cur_item);
    lua_rawseti(ls, -2, i + 1);
  }

  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));
  log.trace("LuaUtils::create_return_table_from_int_vector - exiting");
}

void LuaUtils::set_field(lua_State* ls, const char* name, const bool val)
{
  Log& log = Log::instance();
  log.trace("LuaUtils::set_field - starting");
  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));

  if (ls != nullptr)
  {
    lua_pushstring(ls, name);
    lua_pushboolean(ls, val);
    lua_settable(ls, -3);
  }

  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));
  log.trace("LuaUtils::set_field - exiting");
}

void LuaUtils::set_field(lua_State* ls, const char* name, const int val)
{
  Log& log = Log::instance();
  log.trace("LuaUtils::set_field - starting");
  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));

  if (ls != nullptr)
  {
    lua_pushstring(ls, name);
    lua_pushinteger(ls, val);
    lua_settable(ls, -3);
  }

  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));
  log.trace("LuaUtils::set_field - exiting");
}

void LuaUtils::log_and_raise(lua_State* ls, const string& error_message)
{
  Log& log = Log::instance();
  log.trace("LuaUtils::log_and_raise - starting");
  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));

  log.error(error_message);
  
  string traceback = get_traceback(ls);
  log.error("Traceback: " + traceback);

  // Push the error
  lua_pushstring(ls, error_message.c_str());
  lua_error(ls);

  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));
  log.trace("LuaUtils::log_and_raise - exiting");
}

// Get the result of calling Lua's debug.traceback() - useful for debugging
// purposes.
string LuaUtils::get_traceback(lua_State* ls)
{
  Log& log = Log::instance();
  log.trace("LuaUtils::get_traceback - starting");
  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));

  string debug_module = "debug";
  string traceback_fn = "traceback";
  string traceback;

  // pcall
  lua_State* L = Game::instance().get_script_engine_ref().get_current_state();
  lua_getglobal(L, debug_module.c_str());
  lua_getfield(L, -1, traceback_fn.c_str());

  if (lua_pcall(L, 0, 1, 0) != 0)
  {
    string l_err = lua_tostring(L, -1);
    string error_msg = "LuaUtils::log_and_raise - error running Lua function debug.traceback(): " + l_err;
    Log::instance().error(error_msg);
  }
  else
  {
    traceback = lua_tostring(ls, -1);
    Log::instance().error("Traceback: " + traceback);
  }

  lua_pop(ls, 1);

  log.debug("Lua stack size: " + to_string(Game::instance().get_script_engine_ref().get_stack_size()));
  log.trace("LuaUtils::get_traceback - exiting");

  return traceback;
}
