#pragma once
#include <string>
#include "Creature.hpp"

class ScriptEngine;

class TameScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& tame_script, CreaturePtr tamed_creature, CreaturePtr taming_creature, MapPtr current_map);

  protected:
    static const std::string TAME_MODULE_NAME;
    static const std::string TAME_FUNCTION_NAME;
};

