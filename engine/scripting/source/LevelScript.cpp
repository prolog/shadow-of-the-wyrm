extern "C" 
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "LevelScript.hpp"
#include "Log.hpp"
#include "LuaUtils.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string LevelScript::LEVEL_MODULE_NAME = "level";
const string LevelScript::LEVEL_FUNCTION_NAME = "level";

// Execute the level script, after setting up the scripting environment
// appropriately with the creature information.
void LevelScript::execute(ScriptEngine& se, const vector<string>& setup_scripts, CreaturePtr creature)
{
  Log& log = Log::instance();
  log.trace("LevelScript::execute - begin");
  log.debug("Lua stack size: " + to_string(se.get_stack_size()));

  if (!setup_scripts.empty())
  {
    string race_id  = creature->get_race_id();
    string class_id = creature->get_class_id();
    string creature_id = creature->get_id();
    uint creature_level = creature->get_level().get_current();

    bool execution_result = true;

    // Run each script to load its functions, etc.
    for (const string& script : setup_scripts)
    {
      if (!se.execute(script, {}))
      {
        execution_result = false;
      }
    }

    if (execution_result == true)
    {
      // Set up the function call parameters.
      lua_State* L = se.get_current_state();
      lua_getglobal(L, LEVEL_MODULE_NAME.c_str());
      lua_getfield(L, -1, LEVEL_FUNCTION_NAME.c_str());
      lua_pushstring(L, race_id.c_str());
      lua_pushstring(L, class_id.c_str());
      lua_pushstring(L, creature_id.c_str());
      lua_pushnumber(L, creature_level);

      log.trace("LevelScript::execute - params for call: " + race_id + ", " + class_id + ", " + creature_id + ", " + to_string(creature_level));
      log.debug("Lua stack size before level script run: " + to_string(se.get_stack_size()));

      // Do the function call.  The level function returns nothing.
      if (lua_pcall(L, 4, 0, 0) != 0)
      {
        string l_err = lua_tostring(L, -1);
        string error_msg = "LevelScript::execute - error running Lua function `" + LEVEL_FUNCTION_NAME + "': " + l_err;
        log.error(error_msg);
        lua_pop(L, 1);
      }

      lua_pop(L, 1);
      log.debug("Lua stack size after level script run: " + to_string(se.get_stack_size()));
      log.debug("Stack contents: " + LuaUtils::get_stack_dump(L));
    }
    else
    {
      log.error("LevelScript::execute - Did not run level function due to failure in level setup scripts.");
    }
  }

  log.debug("Lua stack size: " + to_string(se.get_stack_size()));
  log.trace("LevelScript::execute - exiting");
}
