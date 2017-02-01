#pragma once
#include <string>
#include "common.hpp"
#include "Creature.hpp"

class ScriptEngine;

// Allows creatures to react to drop events.
class DropScript
{
  public:
    bool execute(ScriptEngine& se, const std::string& drop_script, const std::string& dropping_creature_id, CreaturePtr reacting_creature, const std::string& item_base_id, const Coordinate& drop_location);
  
  protected:
    static const std::string DROP_MODULE_NAME;
    static const std::string DROP_FUNCTION_NAME;
};

