#pragma once
#include <string>
#include "Creature.hpp"

class ScriptEngine;

class KillScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& kill_script, CreaturePtr dead_creature, CreaturePtr attacking_creature);

  protected:
    static const std::string KILL_MODULE_NAME;
    static const std::string KILL_FUNCTION_NAME;
};

