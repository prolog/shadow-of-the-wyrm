#pragma once
#include <string>
#include "Creature.hpp"

class ScriptEngine;

class DeathScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& death_script, CreaturePtr dead_creature, CreaturePtr attacking_creature, MapPtr current_map);

  protected:
    static const std::string DEATH_MODULE_NAME;
    static const std::string DEATH_FUNCTION_NAME;
};

