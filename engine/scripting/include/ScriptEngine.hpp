#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <string>

// Savage Lands' Lua script engine, currently only used for quests.
//
// Each instance creates its own script environment, and tears it down in
// its destructor.
class ScriptEngine
{
  public:
    ScriptEngine();
    ~ScriptEngine();

    void execute(const std::string& script_file);

  protected:
    // Register the list of functions available to the Lua scripting engine.
    void register_api_functions();

    // The current interpreter state.
    lua_State *L;
  
  private:
    ScriptEngine(const ScriptEngine& se); // Do not implement!
    bool operator=(const ScriptEngine& se); // Do not implement!
};

