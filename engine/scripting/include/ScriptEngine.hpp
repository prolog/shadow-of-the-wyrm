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
    void run_command(const std::string& script_command);
    bool clear_state();

    // Get a given table value
    std::string get_table_str(lua_State* ls, const std::string& key);

  protected:
    // Set up the Lua state
    void initialize_state();

    // Preload all the appropriate modules
    void load_modules();

    // Register the list of functions available to the Lua scripting engine.
    void register_api_functions();

    // Log an error that occurred during execution.
    void log_error();

    // The current interpreter state.
    lua_State *L;
  
  private:
    ScriptEngine(const ScriptEngine& se); // Do not implement!
    bool operator=(const ScriptEngine& se); // Do not implement!
};

