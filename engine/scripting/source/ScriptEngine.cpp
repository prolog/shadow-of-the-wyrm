#include "ScriptEngine.hpp"

// Create a new Lua state object, and open the libraries.
ScriptEngine::ScriptEngine()
{
   L = lua_open();
   luaL_openlibs( L );
}

// Tear down the Lua state.
ScriptEngine::~ScriptEngine()
{
   lua_close( L );
}

