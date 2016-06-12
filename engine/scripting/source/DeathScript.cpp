extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "DeathScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string DeathScript::DEATH_MODULE_NAME = "death";
const string DeathScript::DEATH_FUNCTION_NAME = "die";

// Return true if the script executed successfully, false otherwise.
bool DeathScript::execute(ScriptEngine& se, const string& event_script, CreaturePtr dead_creature, CreaturePtr attacking_creature)
{
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

    if (attacking_creature != nullptr)
    {
      attacking_creature_id = attacking_creature->get_id();
    }

    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, DEATH_MODULE_NAME.c_str());
    lua_getfield(L, -1, DEATH_FUNCTION_NAME.c_str());
    lua_pushstring(L, dead_creature_id.c_str());
    lua_pushstring(L, dead_creature_base_id.c_str());
    lua_pushstring(L, attacking_creature_id.c_str());

    // Do the function call.  The "die" function returns nothing.
    if (lua_pcall(L, 3, 0, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "DeathScript::execute - error running Lua function `" + DEATH_FUNCTION_NAME + "': " + l_err;
      Log::instance().error(error_msg);
      result = false;
    }
  }
  else
  {
    Log::instance().error("DeathScript::execute - did not run Lua function due to script failure: " + event_script);
    result = false;
  }

  return result;
}
