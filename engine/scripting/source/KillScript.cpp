extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "KillScript.hpp"
#include "ClassManager.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string KillScript::KILL_MODULE_NAME = "kill";
const string KillScript::KILL_FUNCTION_NAME = "kill";

// Return true if the script executed successfully, false otherwise.
bool KillScript::execute(ScriptEngine& se, const string& event_script, CreaturePtr dead_creature, CreaturePtr attacking_creature)
{
  Log& log = Log::instance();
  log.trace("KillScript::execute - begin");
  log.debug("Lua stack size: " + to_string(se.get_stack_size()));

  if (event_script.empty())
  {
    log.trace("KillScript::execute - no script - exiting");
    return false;
  }

  bool result = true;

  if (se.execute(event_script, {}))
  {
    string dead_creature_id;
    string dead_creature_base_id;
    string attacking_creature_id;

    if (dead_creature != nullptr)
    {
      dead_creature_id = dead_creature->get_id();
      dead_creature_base_id = dead_creature->get_original_id();
    }

    string attacking_creature_class_id;

    if (attacking_creature != nullptr)
    {
      attacking_creature_id = attacking_creature->get_id();
      attacking_creature_class_id = attacking_creature->get_class_id();
    }

    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, KILL_MODULE_NAME.c_str());
    lua_getfield(L, -1, KILL_FUNCTION_NAME.c_str());
    lua_pushstring(L, attacking_creature_id.c_str());
    lua_pushstring(L, attacking_creature_class_id.c_str());
    lua_pushstring(L, dead_creature_id.c_str());

    // Do the function call.  The "kill" function returns nothing.
    if (lua_pcall(L, 3, 0, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "KillScript::execute - error running Lua function `" + KILL_FUNCTION_NAME + "': " + l_err;
      log.error(error_msg);
      lua_pop(L, 1);
      result = false;
    }

    lua_pop(L, 1);
  }
  else
  {
    log.error("KillScript::execute - did not run Lua function due to script failure: " + event_script);
    result = false;
  }

  log.debug("Lua stack size: " + to_string(se.get_stack_size()));
  log.trace("KillScript::execute - exiting");
  return result;
}

