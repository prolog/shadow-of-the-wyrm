#pragma once
#include <string>
#include "Creature.hpp"

class ScriptEngine;

class CreateScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& create_script, CreaturePtr new_creature, MapPtr current_map);

  protected:
    static const std::string CREATE_MODULE_NAME;
    static const std::string CREATE_FUNCTION_NAME;
};

