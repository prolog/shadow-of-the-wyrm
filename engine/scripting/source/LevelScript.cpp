extern "C" 
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "LevelScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string LevelScript::LEVEL_MODULE_NAME = "class_level";
const string LevelScript::LEVEL_FUNCTION_NAME = "level";

// Execute the level script, after setting up the scripting environment
// appropriately with the creature information.
void LevelScript::execute(ScriptEngine& se, const string& script, CreaturePtr creature)
{
  if (!script.empty())
  {
    string class_id = creature->get_class_id();
    string creature_id = creature->get_id();
    uint creature_level = creature->get_level().get_current();

    // Run the script to load its functions, etc.
    se.execute(script);

    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, LEVEL_MODULE_NAME.c_str());
    lua_getfield(L, -1, LEVEL_FUNCTION_NAME.c_str());
    lua_pushstring(L, class_id.c_str());
    lua_pushstring(L, creature_id.c_str());
    lua_pushnumber(L, creature_level);

    // Do the function call.  The level function returns nothing.
    if (lua_pcall(L, 3, 0, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "error running Lua function `" + LEVEL_FUNCTION_NAME  + "': " + l_err;
      Log::instance().error(error_msg);
    }
  }
}
