extern "C" 
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "LevelScript.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string LevelScript::LEVEL_FUNCTION_NAME = "level";

// Execute the level script, after setting up the scripting environment
// appropriately with the creature information.
void LevelScript::execute(ScriptEngine& se, const string& script, const string& creature_id, const uint creature_level)
{
  if (!script.empty())
  {
    // Run the script to load its functions, etc.
    se.execute(script);

    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, LEVEL_FUNCTION_NAME.c_str());
    lua_pushstring(L, creature_id.c_str());
    lua_pushnumber(L, creature_level);

    // Do the function call.
    if (lua_pcall(L, 2, 1, 0) != 0)
    {
      string error_msg = "error running fn `level'!";
      lua_pushstring(L, error_msg.c_str());
      lua_error(L);
    }
  }
}
