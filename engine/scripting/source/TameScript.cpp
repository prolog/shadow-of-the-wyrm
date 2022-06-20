extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "TameScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string TameScript::TAME_MODULE_NAME = "tame";
const string TameScript::TAME_FUNCTION_NAME = "tame";

// Return true if the script executed successfully, false otherwise.
bool TameScript::execute(ScriptEngine& se, const string& event_script, CreaturePtr tamed_creature, CreaturePtr taming_creature, MapPtr map)
{
  Log& log = Log::instance();
  log.trace("TameScript::execute - begin");
  log.debug("Lua stack size: " + to_string(se.get_stack_size()));

  if (event_script.empty())
  {
    return false;
  }

  bool result = true;
  std::map<string, string> args = { { "tamed_creature_id", tamed_creature ? tamed_creature->get_id() : "" } };

  if (se.execute(event_script, args))
  {
    string tamed_creature_id;
    string tamed_creature_base_id;
    string taming_creature_id;
    string map_id;

    if (tamed_creature != nullptr)
    {
      tamed_creature_id = tamed_creature->get_id();
      tamed_creature_base_id = tamed_creature->get_original_id();
    }

    if (taming_creature != nullptr)
    {
      taming_creature_id = taming_creature->get_id();
    }

    if (map != nullptr)
    {
      map_id = map->get_map_id();
    }

    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, TAME_MODULE_NAME.c_str());
    lua_getfield(L, -1, TAME_FUNCTION_NAME.c_str());
    lua_pushstring(L, tamed_creature_id.c_str());
    lua_pushstring(L, tamed_creature_base_id.c_str());
    lua_pushstring(L, taming_creature_id.c_str());
    lua_pushstring(L, map_id.c_str());

    // Do the function call.  The "die" function returns nothing.
    if (lua_pcall(L, 4, 0, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "TameScript::execute - error running Lua function `" + TAME_FUNCTION_NAME + "': " + l_err;
      log.error(error_msg);
      lua_pop(L, 1);
      result = false;
    }

    lua_pop(L, 1);
  }
  else
  {
    log.error("TameScript::execute - did not run Lua function due to script failure: " + event_script);
    result = false;
  }

  log.debug("Lua stack size: " + to_string(se.get_stack_size()));
  log.trace("TameScript::execute - exiting");
  return result;
}
