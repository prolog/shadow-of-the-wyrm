#pragma once
#include <string>
#include "Creature.hpp"

class ScriptEngine;

class DeathScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& death_script, CreaturePtr creature);

  protected:
    static const std::string DEATH_MODULE_NAME;
    static const std::string DEATH_FUNCTION_NAME;
};

