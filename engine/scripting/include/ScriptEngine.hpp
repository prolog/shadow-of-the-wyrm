#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <map>
#include <string>
#include "Creature.hpp"
#include "ISerializable.hpp"

// Shadow of the Wyrm's Lua script engine, currently only used for quests.
//
// Each instance creates its own script environment, and tears it down in
// its destructor.
class ScriptEngine : public ISerializable
{
  public:
    ScriptEngine();
    ~ScriptEngine();
    bool operator==(const ScriptEngine& se) const;

    bool execute(const std::string& script_file, const std::map<std::string, std::string>& args);
    void run_command(const std::string& script_command);
    void call_function(const std::string& fn_name, const std::vector<std::string>& param_types, const std::vector<std::string>& param_values, const int n_return_vals);

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
    int get_stack_size() const;

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

    // Helper function to handle arguments when calling a Lua function.
    void process_function_arguments(const std::vector<std::string>& param_types, const std::vector<std::string>& param_values);

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

