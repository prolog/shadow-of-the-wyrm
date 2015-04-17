#pragma once
#include <string>
#include "Creature.hpp"

class ScriptEngine;

// Encapsulates a call to the generic "decide" function.  Returns true
// if the creature executed an action, false otherwise.
//
// Running the decision_script parameter typically updates Lua's table of
// per-creature functions, and then execute calls the main "decide"
// function.
class DecisionScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& decision_script, CreaturePtr deciding_creature);

  protected:
    static const std::string DECIDE_MODULE_NAME;
    static const std::string DECIDE_FUNCTION_NAME;
};

