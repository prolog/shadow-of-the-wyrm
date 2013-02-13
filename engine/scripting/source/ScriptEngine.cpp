#include "MessageManager.hpp"
#include "ScriptEngine.hpp"
#include "StringTable.hpp"

using namespace std;

// API prototypes
int add_message(lua_State* ls);

// Create a new Lua state object, and open the libraries.
ScriptEngine::ScriptEngine()
{
   L = lua_open();
   luaL_openlibs( L );
   load_modules();
   register_api_functions();
}

// Tear down the Lua state.
ScriptEngine::~ScriptEngine()
{
   lua_close( L );
}

void ScriptEngine::load_modules()
{
  // Update the environment so that the "/script" directory is assumed.
  luaL_dofile(L, "scripts/env.lua");
}

// Run a particular script in the scripts folder.
void ScriptEngine::execute(const string& script_file)
{
   string script = "scripts/" + script_file;
   luaL_dofile(L, script.c_str());
}

// Register all the functions available to the scripting engine.
void ScriptEngine::register_api_functions()
{
  lua_register(L, "add_message", add_message);
}

// Lua API functions:

// Functions callable by Lua that wrap the actual C++ functions for adding
// messages, getting/updating data, etc.

// Add a message to the message manager.
// Arguments expected: 1.
// Argument type: string (resource SID)
static int add_message(lua_State* ls)
{
  string message_sid;

  if(lua_gettop(ls) > 0 && lua_isstring(ls, -1))
	{
		message_sid = lua_tostring(ls, 1);

    MessageManager& manager = MessageManager::instance();
    manager.add_new_message(StringTable::get(message_sid));
    manager.send();
	}

  return 0;
}