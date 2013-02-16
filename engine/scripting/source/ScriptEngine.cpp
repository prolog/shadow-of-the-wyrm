#include "Game.hpp"
#include "MessageManager.hpp"
#include "Quests.hpp"
#include "ScriptEngine.hpp"
#include "StringTable.hpp"

using namespace std;

// API prototypes
int add_message(lua_State* ls);
int add_new_quest(lua_State* ls);

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

string ScriptEngine::get_table_str(lua_State* ls, const string& key)
{
  string value;
  lua_pushstring(ls, key.c_str());
  lua_gettable(ls, -2); // get table[key]
  
  if (!lua_isstring(ls, -1))
  {
    luaL_error(ls, "invalid key value - expected a string.");
  }

  value = lua_tostring(ls, -1);

  lua_pop(ls, 1); // remove value from stack
  
  return value;
}

// Run a particular script in the scripts folder.
void ScriptEngine::execute(const string& script)
{
  string script_file = "scripts/" + script;
  luaL_dofile(L, script_file.c_str());
}

// Register all the functions available to the scripting engine.
void ScriptEngine::register_api_functions()
{
  lua_register(L, "add_message", add_message);
  lua_register(L, "add_new_quest", add_new_quest);
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

// Add a quest to the in-progress list.  Arguments are:
// - a string representing the quest ID
// - a table representing the "Quest" lua object.
static int add_new_quest(lua_State* ls)
{
  if ((lua_gettop(ls) == 2) && (lua_istable(ls, -1)) && (lua_isstring(ls, -2)))
  {
    Game& game = Game::instance();
    ScriptEngine& se = game.get_script_engine_ref();

    // JCD FIXME: Move the string values into a lua constants class?

    string quest_id = lua_tostring(ls, 1);
    string quest_title_sid = se.get_table_str(ls, "quest_title_sid");
    string questmaster_name_sid = se.get_table_str(ls, "questmaster_name_sid");
    string quest_description_sid = se.get_table_str(ls, "quest_description_sid");

    Quest new_quest(quest_id, quest_title_sid, questmaster_name_sid, quest_description_sid);

    game.get_quests_ref().add_new_quest(quest_id, new_quest);
  }
  else
  {
    lua_pushstring(ls, "Incorrect arguments to add_new_quest");
    lua_error(ls);
  }

  // Return nothing.
  return 0;
}