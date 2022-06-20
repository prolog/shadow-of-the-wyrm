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
bool AttackScript::execute(ScriptEngine& se, const string& attack_script, CreaturePtr attacking_creature, const string& attacked_creature_id, const bool creatures_adjacent)
{
  Log& log = Log::instance();
  log.trace("AttackScript::execute - begin");
  log.debug("Lua stack size: " + to_string(se.get_stack_size()));

  if (attack_script.empty())
  {
    return false;
  }

  bool result = true;

  if (se.execute(attack_script, {}))
  {
    string attacking_creature_base_id;
    string attacking_creature_id;

    if (attacking_creature != nullptr)
    {
      attacking_creature_base_id = attacking_creature->get_original_id();
      attacking_creature_id = attacking_creature->get_id();
    }

    // Set up the function call parameters.
    lua_State* L = se.get_current_state();
    lua_getglobal(L, ATTACK_MODULE_NAME.c_str());
    lua_getfield(L, -1, ATTACK_FUNCTION_NAME.c_str());
    lua_pushstring(L, attacking_creature_base_id.c_str());
    lua_pushstring(L, attacking_creature_id.c_str());
    lua_pushstring(L, attacked_creature_id.c_str());
    lua_pushboolean(L, creatures_adjacent);

    // Do the function call.  The attack function returns nothing.
    if (lua_pcall(L, 4, 0, 0) != 0)
    {
      string l_err = lua_tostring(L, -1);
      string error_msg = "AttackScript::execute - error running Lua function `" + ATTACK_FUNCTION_NAME + "': " + l_err;
      log.error(error_msg);
      lua_pop(L, 1);
      result = false;
    }
  }
  else
  {
    log.error("AttackScript::execute - did not run Lua function due to script failure: " + attack_script);
    result = false;
  }

  log.debug("Lua stack size: " + to_string(se.get_stack_size()));
  log.trace("AttackScript::execute - exiting");
  return result;
}

