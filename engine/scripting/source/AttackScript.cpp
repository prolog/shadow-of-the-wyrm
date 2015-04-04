extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "AttackScript.hpp"
#include "Log.hpp"
#include "ScriptEngine.hpp"

using namespace std;

const string AttackScript::ATTACK_MODULE_NAME = "attack";
const string AttackScript::ATTACK_FUNCTION_NAME = "attack";

// Execute an attack script.
// Return true if the script executed successfully, false otherwise.
bool AttackScript::execute(ScriptEngine& se, const string& attack_script, const string& attacking_creature_base_id, const string& attacked_creature_id)
{
  bool result = true;
  se.execute(attack_script);

  // Set up the function call parameters.
  lua_State* L = se.get_current_state();
  lua_getglobal(L, ATTACK_MODULE_NAME.c_str());
  lua_getfield(L, -1, ATTACK_FUNCTION_NAME.c_str());
  lua_pushstring(L, attacking_creature_base_id.c_str());
  lua_pushstring(L, attacked_creature_id.c_str());

  // Do the function call.  The level function returns nothing.
  if (lua_pcall(L, 2, 0, 0) != 0)
  {
    string l_err = lua_tostring(L, -1);
    string error_msg = "AttackScript::execute - error running Lua function `" + ATTACK_FUNCTION_NAME + "': " + l_err;
    Log::instance().error(error_msg);
    result = false;
  }

  return result;
}

