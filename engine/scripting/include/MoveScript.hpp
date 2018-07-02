#pragma once
#include <string>
#include "Creature.hpp"

class ScriptEngine;

class MoveScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& kill_script, CreaturePtr moving_creature, const std::string& map_id, const Coordinate& new_coords);

  protected:
    static const std::string MOVE_MODULE_NAME;
    static const std::string MOVE_FUNCTION_NAME;
};

