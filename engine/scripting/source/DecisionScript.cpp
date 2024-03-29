extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "DecisionScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string DecisionScript::DECIDE_MODULE_NAME = "decide";
const string DecisionScript::DECIDE_FUNCTION_NAME = "decide";

// Execute the decide script.
// Return true if the script executed successfully and returns true;
// false otherwise.
int DecisionScript::execute(ScriptEngine& se, const string& decision_script, CreaturePtr creature)
{
  Log& log = Log::instance();
  log.trace("DecisionScript::execute - begin");

  // By default, the return value will be false.
  // It only gets set to true if the script execution returns true.
  int acv = 0;

  // Set up the decision script - the creature's decision script will, as a
  // part of its execution, set up all the values required for the 
  // decide function to run successfully.
  se.execute(decision_script, {});

  string creature_base_id;
  string creature_id;

  if (creature != nullptr)
  {
    creature_base_id = creature->get_original_id();
    creature_id = creature->get_id();
  }

  // Set up the function call parameters.
  lua_State* L = se.get_current_state();
  lua_getglobal(L, DECIDE_MODULE_NAME.c_str());
  lua_getfield(L, -1, DECIDE_FUNCTION_NAME.c_str());
  lua_pushstring(L, creature_base_id.c_str());
  lua_pushstring(L, creature_id.c_str());

  // Do the function call.  The attack function returns a boolean
  // value.
  if (lua_pcall(L, 2, 1, 0) != 0)
  {
    string l_err = lua_tostring(L, -1);
    string error_msg = "DecisionScript::execute - could not run Lua function `" + DECIDE_FUNCTION_NAME + "': " + l_err;
    log.error(error_msg);
    lua_pop(L, 1);
  }
  else
  {
    // Parse the integer return value.
    if (!lua_isnumber(L, -1))
    {
      log.error("Return value from call to Lua function " + DECIDE_FUNCTION_NAME + " is not an action cost value!");
    }
    else
    {
      acv = (lua_tointeger(L, -1) != 0);
    }

    lua_pop(L, 1);
  }

  lua_pop(L, 1);

  log.trace("DecisionScript::execute - exiting");
  return acv;
}

