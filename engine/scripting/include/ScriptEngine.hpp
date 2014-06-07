#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <string>
#include "Creature.hpp"
#include "ISerializable.hpp"

// Savage Lands' Lua script engine, currently only used for quests.
//
// Each instance creates its own script environment, and tears it down in
// its destructor.
class ScriptEngine : public ISerializable
{
  public:
    ScriptEngine();
    ~ScriptEngine();
    bool operator==(const ScriptEngine& se) const;

    void execute(const std::string& script_file);
    void run_command(const std::string& script_command);
    bool clear_state();

    // Get a given table value
    std::string get_table_str(lua_State* ls, const std::string& key);

    // Get the current state.  Used by level scripts (and in future, maybe
    // others) to set particular values on the stack prior to making a call.
    lua_State* get_current_state();

    // Set the current creature.  Typically only used by functions before certain
    // maps exist - the Lua functions need a way to operate on the creature.
    void set_creature(CreaturePtr creature);

    void set_last_executed(const std::string& new_last_executed);
    std::string get_last_executed() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    // Set up the Lua state
    void initialize_state();

    // Export any defines to Lua
    void set_constants(lua_State* ls);

    // Preload all the appropriate modules
    void load_modules();

    // Register the list of functions available to the Lua scripting engine.
    void register_api_functions();

    // Log an error that occurred during execution.
    void log_error();

    // The current interpreter state.
    lua_State* L;

    // The last command executed
    std::string last_executed;
  
  private:
    ScriptEngine(const ScriptEngine& se); // Do not implement!
    bool operator=(const ScriptEngine& se); // Do not implement!

    ClassIdentifier internal_class_identifier() const override;
};

